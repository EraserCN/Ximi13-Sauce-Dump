/*
 * Copyright (C) 2018 The Android Open Source Project
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

#pragma once

#include <sys/types.h>

#include <array>
#include <functional>
#include <initializer_list>
#include <map>
#include <string>
#include <string_view>
#include <unordered_map>

namespace android {
namespace meminfo {

static constexpr const char kDmabufHeapRoot[] = "/dev/dma_heap";

class SysMemInfo final {
    // System or Global memory accounting
  public:
    static constexpr const char kMemTotal[] = "MemTotal:";
    static constexpr const char kMemFree[] = "MemFree:";
    static constexpr const char kMemBuffers[] = "Buffers:";
    static constexpr const char kMemCached[] = "Cached:";
    static constexpr const char kMemShmem[] = "Shmem:";
    static constexpr const char kMemSlab[] = "Slab:";
    static constexpr const char kMemSReclaim[] = "SReclaimable:";
    static constexpr const char kMemSUnreclaim[] = "SUnreclaim:";
    static constexpr const char kMemSwapTotal[] = "SwapTotal:";
    static constexpr const char kMemSwapFree[] = "SwapFree:";
    static constexpr const char kMemMapped[] = "Mapped:";
    static constexpr const char kMemVmallocUsed[] = "VmallocUsed:";
    static constexpr const char kMemPageTables[] = "PageTables:";
    static constexpr const char kMemKernelStack[] = "KernelStack:";
    static constexpr const char kMemKReclaimable[] = "KReclaimable:";
    static constexpr const char kMemActive[] = "Active:";
    static constexpr const char kMemInactive[] = "Inactive:";
    static constexpr const char kMemUnevictable[] = "Unevictable:";


    static constexpr std::initializer_list<std::string_view> kDefaultSysMemInfoTags = {
            SysMemInfo::kMemTotal,      SysMemInfo::kMemFree,        SysMemInfo::kMemBuffers,
            SysMemInfo::kMemCached,     SysMemInfo::kMemShmem,       SysMemInfo::kMemSlab,
            SysMemInfo::kMemSReclaim,   SysMemInfo::kMemSUnreclaim,  SysMemInfo::kMemSwapTotal,
            SysMemInfo::kMemSwapFree,   SysMemInfo::kMemMapped,      SysMemInfo::kMemVmallocUsed,
            SysMemInfo::kMemPageTables, SysMemInfo::kMemKernelStack, SysMemInfo::kMemKReclaimable,
            SysMemInfo::kMemActive,     SysMemInfo::kMemInactive,    SysMemInfo::kMemUnevictable,
    };

    SysMemInfo() = default;

    // Parse /proc/meminfo and read values that are needed
    bool ReadMemInfo(const char* path = "/proc/meminfo");
    bool ReadMemInfo(size_t ntags, const std::string_view* tags, uint64_t* out,
                     const char* path = "/proc/meminfo");
    bool ReadMemInfo(std::vector<uint64_t>* out, const char* path = "/proc/meminfo");

    // Parse /proc/vmallocinfo and return total physical memory mapped
    // in vmalloc area by the kernel.
    // Note that this deliberately ignores binder buffers. They are _always_
    // mapped in a process and are counted for in each process.
    uint64_t ReadVmallocInfo();

    // getters
    uint64_t mem_total_kb() { return mem_in_kb_[kMemTotal]; }
    uint64_t mem_free_kb() { return mem_in_kb_[kMemFree]; }
    uint64_t mem_buffers_kb() { return mem_in_kb_[kMemBuffers]; }
    uint64_t mem_cached_kb() { return mem_in_kb_[kMemCached]; }
    uint64_t mem_shmem_kb() { return mem_in_kb_[kMemShmem]; }
    uint64_t mem_slab_kb() { return mem_in_kb_[kMemSlab]; }
    uint64_t mem_slab_reclaimable_kb() { return mem_in_kb_[kMemSReclaim]; }
    uint64_t mem_slab_unreclaimable_kb() { return mem_in_kb_[kMemSUnreclaim]; }
    uint64_t mem_swap_kb() { return mem_in_kb_[kMemSwapTotal]; }
    uint64_t mem_swap_free_kb() { return mem_in_kb_[kMemSwapFree]; }
    uint64_t mem_mapped_kb() { return mem_in_kb_[kMemMapped]; }
    uint64_t mem_vmalloc_used_kb() { return mem_in_kb_[kMemVmallocUsed]; }
    uint64_t mem_page_tables_kb() { return mem_in_kb_[kMemPageTables]; }
    uint64_t mem_kernel_stack_kb() { return mem_in_kb_[kMemKernelStack]; }
    uint64_t mem_kreclaimable_kb() { return mem_in_kb_[kMemKReclaimable]; }
    uint64_t mem_active_kb() { return mem_in_kb_[kMemActive]; }
    uint64_t mem_inactive_kb() { return mem_in_kb_[kMemInactive]; }
    uint64_t mem_unevictable_kb() { return mem_in_kb_[kMemUnevictable]; }
    uint64_t mem_zram_kb(const char* zram_dev = nullptr);

  private:
    std::map<std::string_view, uint64_t> mem_in_kb_;
    bool MemZramDevice(const char* zram_dev, uint64_t* mem_zram_dev);
    bool ReadMemInfo(const char* path, size_t ntags, const std::string_view* tags,
                     std::function<void(std::string_view, uint64_t)> store_val);
};

// Parse /proc/vmallocinfo and return total physical memory mapped
// in vmalloc area by the kernel. Note that this deliberately ignores binder buffers. They are
// _always_ mapped in a process and are counted for in each process.
uint64_t ReadVmallocInfo(const char* path = "/proc/vmallocinfo");

// Read ION heaps allocation size in kb
bool ReadIonHeapsSizeKb(
    uint64_t* size, const std::string& path = "/sys/kernel/ion/total_heaps_kb");

// Read ION pools allocation size in kb
bool ReadIonPoolsSizeKb(
    uint64_t* size, const std::string& path = "/sys/kernel/ion/total_pools_kb");

// Read DMA-BUF heap pools allocation size in kb
bool ReadDmabufHeapPoolsSizeKb(uint64_t* size,
                            const std::string& path = "/sys/kernel/dma_heap/total_pools_kb");

// Read per-process GPU memory usage. Returns a map of pid -> GPU Mem in kilobytes.
bool ReadPerProcessGpuMem(std::unordered_map<uint32_t, uint64_t>* out);

// Read GPU usage of the specified process in kb.
bool ReadProcessGpuUsageKb(uint32_t pid, uint32_t gpu_id, uint64_t* size);

// Read GPU total usage size in kb
bool ReadGpuTotalUsageKb(uint64_t* size);

// Read total size of DMA-BUFs exported from the DMA-BUF heap framework in kb
bool ReadDmabufHeapTotalExportedKb(
        uint64_t* size, const std::string& dma_heap_root = kDmabufHeapRoot,
        const std::string& dma_buf_sysfs_path = "/sys/kernel/dmabuf/buffers");

}  // namespace meminfo
}  // namespace android
