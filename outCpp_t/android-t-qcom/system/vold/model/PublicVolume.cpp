/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "PublicVolume.h"

#include "AppFuseUtil.h"
#include "Utils.h"
#include "VolumeManager.h"
#include "fs/Exfat.h"
#include "fs/Ext4.h"
#include "fs/F2fs.h"
#include "fs/Ntfs.h"
#include "fs/Vfat.h"

#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/stringprintf.h>
#include <cutils/fs.h>
#include <private/android_filesystem_config.h>
#include <utils/Timers.h>

#include <fcntl.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/wait.h>

// MIUI ADD: START
#include <future>
#include <chrono>
using std::chrono::steady_clock;
// END

using android::base::GetBoolProperty;
using android::base::StringPrintf;

namespace android {
namespace vold {

// MIUI ADD: START
static status_t readMetadataUntrustedWithTimeout(const std::string& id, const std::string& path,
                                                 std::string* fsType, std::string* fsUuid,
                                                 std::string* fsLabel);

static status_t mountVolumeWithTimeout(const steady_clock::time_point& startTime,
                                       const std::string& id, const std::string& fsLabel,
                                       const std::string& fsType, const std::string& devPath,
                                       const std::string& rawPath, bool isVisible);
// END

static const char* kSdcardFsPath = "/system/bin/sdcard";

static const char* kAsecPath = "/mnt/secure/asec";

PublicVolume::PublicVolume(dev_t device) : VolumeBase(Type::kPublic), mDevice(device) {
    setId(StringPrintf("public:%u,%u", major(device), minor(device)));
    mDevPath = StringPrintf("/dev/block/vold/%s", getId().c_str());
    mFuseMounted = false;
    mUseSdcardFs = IsSdcardfsUsed();
}

PublicVolume::~PublicVolume() {}

status_t PublicVolume::readMetadata() {
    // MIUI MOD:
    // status_t res = ReadMetadataUntrusted(mDevPath, &mFsType, &mFsUuid, &mFsLabel);
    auto res = readMetadataUntrustedWithTimeout(getId(), mDevPath, &mFsType, &mFsUuid, &mFsLabel);

    auto listener = getListener();
    if (listener) listener->onVolumeMetadataChanged(getId(), mFsType, mFsUuid, mFsLabel);

    return res;
}

status_t PublicVolume::initAsecStage() {
    std::string legacyPath(mRawPath + "/android_secure");
    std::string securePath(mRawPath + "/.android_secure");

    // Recover legacy secure path
    if (!access(legacyPath.c_str(), R_OK | X_OK) && access(securePath.c_str(), R_OK | X_OK)) {
        if (rename(legacyPath.c_str(), securePath.c_str())) {
            PLOG(WARNING) << getId() << " failed to rename legacy ASEC dir";
        }
    }

    if (TEMP_FAILURE_RETRY(mkdir(securePath.c_str(), 0700))) {
        if (errno != EEXIST) {
            PLOG(WARNING) << getId() << " creating ASEC stage failed";
            return -errno;
        }
    }

    BindMount(securePath, kAsecPath);

    return OK;
}

status_t PublicVolume::doCreate() {
    return CreateDeviceNode(mDevPath, mDevice);
}

status_t PublicVolume::doDestroy() {
    return DestroyDeviceNode(mDevPath);
}

status_t PublicVolume::doMount() {
    bool isVisible = isVisibleForWrite();
    // MIUI MOD: START
    // readMetadata();
    auto startTime = steady_clock::now();
    auto ret = readMetadata();
    if (ret != OK) {
        return ret;
    }
    // END

    // Use UUID as stable name, if available
    std::string stableName = getId();
    if (!mFsUuid.empty()) {
        stableName = mFsUuid;
    }

    mRawPath = StringPrintf("/mnt/media_rw/%s", stableName.c_str());

    mSdcardFsDefault = StringPrintf("/mnt/runtime/default/%s", stableName.c_str());
    mSdcardFsRead = StringPrintf("/mnt/runtime/read/%s", stableName.c_str());
    mSdcardFsWrite = StringPrintf("/mnt/runtime/write/%s", stableName.c_str());
    mSdcardFsFull = StringPrintf("/mnt/runtime/full/%s", stableName.c_str());

    setInternalPath(mRawPath);
    if (isVisible) {
        setPath(StringPrintf("/storage/%s", stableName.c_str()));
    } else {
        setPath(mRawPath);
    }

    if (fs_prepare_dir(mRawPath.c_str(), 0700, AID_ROOT, AID_ROOT)) {
        PLOG(ERROR) << getId() << " failed to create mount points";
        return -errno;
    }

    // MIUI MOD: START
    // if (mFsType == "vfat" && vfat::IsSupported()) {
    //     if (vfat::Check(mDevPath)) {
    //         LOG(ERROR) << getId() << " failed filesystem check";
    //         return -EIO;
    //     }
    // } else if (mFsType == "exfat" && exfat::IsSupported()) {
    //     if (exfat::Check(mDevPath)) {
    //         LOG(ERROR) << getId() << " failed filesystem check";
    //         return -EIO;
    //     }
    // } else if (mFsType == "ntfs" && ntfs::IsSupported()){
    //     if (ntfs::Check(mDevPath)) {
    //         LOG(ERROR) << getId() << " failed filesystem check";
    //         return -EIO;
    //     }
    // } else if(mFsType == "ext4" && ext4::IsSupported()){
    //     if (ext4::Check(mDevPath,mRawPath)) {
    //         LOG(ERROR) << getId() << " failed filesystem check";
    //         return -EIO;
    //    }
    // } else if(mFsType == "f2fs" && f2fs::IsSupported()){
    //     if (f2fs::Check(mDevPath)) {
    //         LOG(ERROR) << getId() << " failed filesystem check";
    //         return -EIO;
    //    }
    // } else {
    //     LOG(ERROR) << getId() << " unsupported filesystem " << mFsType;
    //     return -EIO;
    // }

    // if (mFsType == "vfat") {
    //     if (vfat::Mount(mDevPath, mRawPath, false, false, false, AID_ROOT,
    //                     (isVisible ? AID_MEDIA_RW : AID_EXTERNAL_STORAGE), 0007, true)) {
    //         PLOG(ERROR) << getId() << " failed to mount " << mDevPath;
    //         return -EIO;
    //     }
    // } else if (mFsType == "exfat") {
    //     if (exfat::Mount(mDevPath, mRawPath, AID_ROOT,
    //                      (isVisible ? AID_MEDIA_RW : AID_EXTERNAL_STORAGE), 0007)) {
    //         PLOG(ERROR) << getId() << " failed to mount " << mDevPath;
    //         return -EIO;
    //     }
    // } else if(mFsType == "ntfs"){
    //     if (ntfs::Mount(mDevPath, mRawPath, AID_ROOT,
    //                      (isVisible ? AID_MEDIA_RW : AID_EXTERNAL_STORAGE), 0007)) {
    //         PLOG(ERROR) << getId() << " failed to mount " << mDevPath;
    //         return -EIO;
    //     }
    // } else if(mFsType == "ext4"){
    //      auto mountData = android::base::StringPrintf("uid=%d,gid=%d,fmask=%o,dmask=%o", AID_ROOT,
    //                                              (isVisible ? AID_MEDIA_RW : AID_EXTERNAL_STORAGE), 0007, 0007);
    //      if (ext4::Mount(mDevPath, mRawPath, false, false, true,mountData)){
    //         PLOG(ERROR) << getId() << " failed to mount " << mDevPath;
    //         return -EIO;
    //     }
    // } else if(mFsType == "f2fs"){
    //      auto mountData = android::base::StringPrintf("uid=%d,gid=%d,fmask=%o,dmask=%o", AID_ROOT,
    //                                              (isVisible ? AID_MEDIA_RW : AID_EXTERNAL_STORAGE), 0007, 0007);
    //      if(f2fs::Mount(mDevPath, mRawPath, mountData)){
    //         PLOG(ERROR) << getId() << " failed to mount " << mDevPath;
    //         return -EIO;
    //     }
    // }
    ret = mountVolumeWithTimeout(startTime, getId(), mFsLabel, mFsType, mDevPath, mRawPath,
                                 isVisible);
    if (ret != OK) {
        return ret;
    }
    // END

    if (getMountFlags() & MountFlags::kPrimary) {
        initAsecStage();
    }

    if (!isVisible) {
        // Not visible to apps, so no need to spin up sdcardfs or FUSE
        return OK;
    }

    if (mUseSdcardFs) {
        if (fs_prepare_dir(mSdcardFsDefault.c_str(), 0700, AID_ROOT, AID_ROOT) ||
            fs_prepare_dir(mSdcardFsRead.c_str(), 0700, AID_ROOT, AID_ROOT) ||
            fs_prepare_dir(mSdcardFsWrite.c_str(), 0700, AID_ROOT, AID_ROOT) ||
            fs_prepare_dir(mSdcardFsFull.c_str(), 0700, AID_ROOT, AID_ROOT)) {
            PLOG(ERROR) << getId() << " failed to create sdcardfs mount points";
            return -errno;
        }

        dev_t before = GetDevice(mSdcardFsFull);

        int sdcardFsPid;
        if (!(sdcardFsPid = fork())) {
            if (getMountFlags() & MountFlags::kPrimary) {
                // clang-format off
                if (execl(kSdcardFsPath, kSdcardFsPath,
                        "-u", "1023", // AID_MEDIA_RW
                        "-g", "1023", // AID_MEDIA_RW
                        "-U", std::to_string(getMountUserId()).c_str(),
                        "-w",
                        mRawPath.c_str(),
                        stableName.c_str(),
                        NULL)) {
                    // clang-format on
                    PLOG(ERROR) << "Failed to exec";
                }
            } else {
                // clang-format off
                if (execl(kSdcardFsPath, kSdcardFsPath,
                        "-u", "1023", // AID_MEDIA_RW
                        "-g", "1023", // AID_MEDIA_RW
                        "-U", std::to_string(getMountUserId()).c_str(),
                        mRawPath.c_str(),
                        stableName.c_str(),
                        NULL)) {
                    // clang-format on
                    PLOG(ERROR) << "Failed to exec";
                }
            }

            LOG(ERROR) << "sdcardfs exiting";
            _exit(1);
        }

        if (sdcardFsPid == -1) {
            PLOG(ERROR) << getId() << " failed to fork";
            return -errno;
        }

        nsecs_t start = systemTime(SYSTEM_TIME_BOOTTIME);
        while (before == GetDevice(mSdcardFsFull)) {
            LOG(DEBUG) << "Waiting for sdcardfs to spin up...";
            usleep(50000);  // 50ms

            nsecs_t now = systemTime(SYSTEM_TIME_BOOTTIME);
            if (nanoseconds_to_milliseconds(now - start) > 5000) {
                LOG(WARNING) << "Timed out while waiting for sdcardfs to spin up";
                return -ETIMEDOUT;
            }
        }
        /* sdcardfs will have exited already. The filesystem will still be running */
        TEMP_FAILURE_RETRY(waitpid(sdcardFsPid, nullptr, 0));
    }

    // We need to mount FUSE *after* sdcardfs, since the FUSE daemon may depend
    // on sdcardfs being up.
    LOG(INFO) << "Mounting public fuse volume";
    android::base::unique_fd fd;
    int user_id = getMountUserId();
    int result = MountUserFuse(user_id, getInternalPath(), stableName, &fd);

    if (result != 0) {
        LOG(ERROR) << "Failed to mount public fuse volume";
        doUnmount();
        return -result;
    }

    mFuseMounted = true;
    auto callback = getMountCallback();
    if (callback) {
        bool is_ready = false;
        callback->onVolumeChecking(std::move(fd), getPath(), getInternalPath(), &is_ready);
        if (!is_ready) {
            LOG(ERROR) << "Failed to complete public volume mount";
            doUnmount();
            return -EIO;
        }
    }

    ConfigureReadAheadForFuse(GetFuseMountPathForUser(user_id, stableName), 256u);

    // See comment in model/EmulatedVolume.cpp
    ConfigureMaxDirtyRatioForFuse(GetFuseMountPathForUser(user_id, stableName), 40u);

    return OK;
}

status_t PublicVolume::doUnmount() {
    // Unmount the storage before we kill the FUSE process. If we kill
    // the FUSE process first, most file system operations will return
    // ENOTCONN until the unmount completes. This is an exotic and unusual
    // error code and might cause broken behaviour in applications.
    KillProcessesUsingPath(getPath());

    if (mFuseMounted) {
        // Use UUID as stable name, if available
        std::string stableName = getId();
        if (!mFsUuid.empty()) {
            stableName = mFsUuid;
        }

        if (UnmountUserFuse(getMountUserId(), getInternalPath(), stableName) != OK) {
            PLOG(INFO) << "UnmountUserFuse failed on public fuse volume";
            return -errno;
        }

        mFuseMounted = false;
    }

    ForceUnmount(kAsecPath);

    if (mUseSdcardFs) {
        ForceUnmount(mSdcardFsDefault);
        ForceUnmount(mSdcardFsRead);
        ForceUnmount(mSdcardFsWrite);
        ForceUnmount(mSdcardFsFull);

        rmdir(mSdcardFsDefault.c_str());
        rmdir(mSdcardFsRead.c_str());
        rmdir(mSdcardFsWrite.c_str());
        rmdir(mSdcardFsFull.c_str());

        mSdcardFsDefault.clear();
        mSdcardFsRead.clear();
        mSdcardFsWrite.clear();
        mSdcardFsFull.clear();
    }
    ForceUnmount(mRawPath);
    rmdir(mRawPath.c_str());
    mRawPath.clear();

    return OK;
}

// MIUI MOD: START
// status_t PublicVolume::doFormat(const std::string& fsType) {
static status_t doFormatInternal(const std::string& fsType, const std::string& mDevPath,
                                 const std::string& mRawPath,
                                 const std::function<std::string()> getId) {
// END
    bool useVfat = vfat::IsSupported();
    bool useExfat = exfat::IsSupported();
    status_t res = OK;

    // Resolve the target filesystem type
    if (fsType == "auto" && useVfat && useExfat) {
        uint64_t size = 0;

        res = GetBlockDevSize(mDevPath, &size);
        if (res != OK) {
            LOG(ERROR) << "Couldn't get device size " << mDevPath;
            return res;
        }

        // If both vfat & exfat are supported use exfat for SDXC (>~32GiB) cards
        if (size > 32896LL * 1024 * 1024) {
            useVfat = false;
        } else {
            useExfat = false;
        }
    } else if (fsType == "vfat") {
        useExfat = false;
    } else if (fsType == "exfat") {
        useVfat = false;
    }

    if (IsFilesystemSupported(fsType) && !useVfat && !useExfat) {
        LOG(ERROR) << "Unsupported filesystem " << fsType;
        return -EINVAL;
    }

    if (WipeBlockDevice(mDevPath) != OK) {
        LOG(WARNING) << getId() << " failed to wipe";
    }

    if (useVfat) {
        res = vfat::Format(mDevPath, 0);
    } else if (useExfat) {
        res = exfat::Format(mDevPath);
    } else if (fsType == "ext4") {
        res = ext4::Format(mDevPath, 0, mRawPath);
    } else if (fsType == "f2fs") {
        res = f2fs::Format(mDevPath);
    } else if (fsType == "ntfs") {
        res = ntfs::Format(mDevPath);
    } else {
        LOG(ERROR) << getId() << " unrecognized filesystem " << fsType;
        res = -1;
        errno = EIO;
    }

    if (res != OK) {
        LOG(ERROR) << getId() << " failed to format";
        res = -errno;
    }

    return res;
}

// MIUI ADD: START
static inline std::chrono::seconds getAvailableDuration(const steady_clock::time_point& startTime) {
    // Make sure the whole mount operation finishes in 60s, or system_server would restart
    const auto TOTAL_TIME = std::chrono::seconds(50);
    auto usedTime =
            std::chrono::duration_cast<std::chrono::seconds>(steady_clock::now() - startTime);
    return std::max(std::chrono::seconds(3), TOTAL_TIME - usedTime);
}

static status_t getResultWithTimeout(std::future<status_t>& future, const char* action,
                                     const steady_clock::time_point& startTime,
                                     const std::string& id, const std::string& label,
                                     const std::string& type) {
    auto status = future.wait_for(getAvailableDuration(startTime));
    std::string volumeInfo;
    if (status == std::future_status::timeout) {
        volumeInfo = StringPrintf("id=%s, label=%s, type=%s", id.c_str(), label.c_str(), type.c_str());
        LOG(ERROR) << action << " timeout: " << volumeInfo;
        return -ETIMEDOUT;
    }
    // Should not happen
    if (status != std::future_status::ready) {
        volumeInfo = StringPrintf("id=%s, label=%s, type=%s", id.c_str(), label.c_str(), type.c_str());
        LOG(ERROR) << action << " failed: unexpected status=" << (int)status << ", " << volumeInfo;
        return -ETIMEDOUT;
    }
    auto ret = future.get();
    volumeInfo =
            StringPrintf("id=%s, label=%s, type=%s", id.c_str(), label.c_str(), type.c_str());
    LOG(INFO) << action << ": ret=" << ret << ", " << volumeInfo;
    return ret;
}

static status_t doMountVolume(std::string& mFsType, std::string& mDevPath, std::string& mRawPath,
                              bool isVisible, std::function<std::string()> getId) {
    // Keep updated with AOSP!!!
    if (mFsType == "vfat" && vfat::IsSupported()) {
        if (vfat::Check(mDevPath)) {
            LOG(ERROR) << getId() << " failed filesystem check";
            return -EIO;
        }
    } else if (mFsType == "exfat" && exfat::IsSupported()) {
        if (exfat::Check(mDevPath)) {
            LOG(ERROR) << getId() << " failed filesystem check";
            return -EIO;
        }
    } else if (mFsType == "ntfs" && ntfs::IsSupported()){
        if (ntfs::Check(mDevPath)) {
            LOG(ERROR) << getId() << " failed filesystem check";
            return -EIO;
        }
    } else if(mFsType == "ext4" && ext4::IsSupported()){
        if (ext4::Check(mDevPath,mRawPath)) {
            LOG(ERROR) << getId() << " failed filesystem check";
            return -EIO;
       }
    } else if(mFsType == "f2fs" && f2fs::IsSupported()){
        if (f2fs::Check(mDevPath)) {
            LOG(ERROR) << getId() << " failed filesystem check";
            return -EIO;
       }
    } else {
        LOG(ERROR) << getId() << " unsupported filesystem " << mFsType;
        return -EIO;
    }

    if (mFsType == "vfat") {
        if (vfat::Mount(mDevPath, mRawPath, false, false, false, AID_ROOT,
                        (isVisible ? AID_MEDIA_RW : AID_EXTERNAL_STORAGE), 0007, true)) {
            PLOG(ERROR) << getId() << " failed to mount " << mDevPath;
            return -EIO;
        }
    } else if (mFsType == "exfat") {
        if (exfat::Mount(mDevPath, mRawPath, AID_ROOT,
                         (isVisible ? AID_MEDIA_RW : AID_EXTERNAL_STORAGE), 0007)) {
            PLOG(ERROR) << getId() << " failed to mount " << mDevPath;
            return -EIO;
        }
    } else if(mFsType == "ntfs"){
        if (ntfs::Mount(mDevPath, mRawPath, AID_ROOT,
                         (isVisible ? AID_MEDIA_RW : AID_EXTERNAL_STORAGE), 0007)) {
            PLOG(ERROR) << getId() << " failed to mount " << mDevPath;
            return -EIO;
        }
    } else if(mFsType == "ext4"){
         auto mountData = android::base::StringPrintf("uid=%d,gid=%d,fmask=%o,dmask=%o", AID_ROOT,
                                                 (isVisible ? AID_MEDIA_RW : AID_EXTERNAL_STORAGE), 0007, 0007);
         if (ext4::Mount(mDevPath, mRawPath, false, false, true,mountData)){
            PLOG(ERROR) << getId() << " failed to mount " << mDevPath;
            return -EIO;
        }
    } else if(mFsType == "f2fs"){
         auto mountData = android::base::StringPrintf("uid=%d,gid=%d,fmask=%o,dmask=%o", AID_ROOT,
                                                 (isVisible ? AID_MEDIA_RW : AID_EXTERNAL_STORAGE), 0007, 0007);
         if(f2fs::Mount(mDevPath, mRawPath, mountData)){
            PLOG(ERROR) << getId() << " failed to mount " << mDevPath;
            return -EIO;
        }
    }
    return OK;
}

static void wrapMountVolume(std::string fsType, std::string devPath, std::string rawPath,
                            bool isVisible, std::function<std::string()> getId,
                            std::promise<status_t> promise) {
    auto ret = doMountVolume(fsType, devPath, rawPath, isVisible, getId);
    promise.set_value(ret);
}

static void wrapReadMetadataUntrusted(std::string path, std::shared_ptr<std::string> fsType,
                                      std::shared_ptr<std::string> fsUuid,
                                      std::shared_ptr<std::string> fsLabel,
                                      std::promise<status_t> promise) {
    auto ret = ReadMetadataUntrusted(path, fsType.get(), fsUuid.get(), fsLabel.get());
    promise.set_value(ret);
}

static void wrapFormatVolume(std::string fsType, std::string devPath, std::string rawPath,
                             std::function<std::string()> getId, std::promise<status_t> promise) {
    auto ret = doFormatInternal(fsType, devPath, rawPath, getId);
    promise.set_value(ret);
}

status_t readMetadataUntrustedWithTimeout(const std::string& id, const std::string& path,
                                          std::string* fsType, std::string* fsUuid,
                                          std::string* fsLabel) {
    auto startTime = steady_clock::now();
    std::shared_ptr<std::string> tmpFsType = std::make_shared<std::string>();
    std::shared_ptr<std::string> tmpFsUuid = std::make_shared<std::string>();
    std::shared_ptr<std::string> tmpFsLabel = std::make_shared<std::string>();
    auto promise = std::promise<status_t>();
    auto future = promise.get_future();
    std::thread worker(wrapReadMetadataUntrusted, path, tmpFsType, tmpFsUuid, tmpFsLabel,
                       std::move(promise));
    worker.detach();
    auto ret = getResultWithTimeout(future, "Read metadata", startTime, id, *tmpFsLabel, *tmpFsType);
    if (ret == OK) {
        std::swap(*tmpFsType, *fsType);
        std::swap(*tmpFsUuid, *fsUuid);
        std::swap(*tmpFsLabel, *fsLabel);
    }
    return ret;
}

status_t mountVolumeWithTimeout(const steady_clock::time_point& startTime, const std::string& id,
                                const std::string& fsLabel, const std::string& fsType,
                                const std::string& devPath, const std::string& rawPath,
                                bool isVisible) {
    auto promise = std::promise<status_t>();
    auto future = promise.get_future();
    std::thread worker(
            wrapMountVolume, fsType, devPath, rawPath, isVisible, [=] { return id; },
            std::move(promise));
    worker.detach();
    return getResultWithTimeout(future, "Mount", startTime, id, fsLabel, fsType);
}

status_t PublicVolume::doFormat(const std::string& fsType) {
    auto startTime = steady_clock::now();
    const std::string id = getId();
    auto promise = std::promise<status_t>();
    auto future = promise.get_future();
    std::thread worker(
            wrapFormatVolume, fsType, mDevPath, mRawPath, [=] { return id; }, std::move(promise));
    worker.detach();
    return getResultWithTimeout(future, "Format", startTime, id, mFsLabel, fsType);
}
// END

}  // namespace vold
}  // namespace android
