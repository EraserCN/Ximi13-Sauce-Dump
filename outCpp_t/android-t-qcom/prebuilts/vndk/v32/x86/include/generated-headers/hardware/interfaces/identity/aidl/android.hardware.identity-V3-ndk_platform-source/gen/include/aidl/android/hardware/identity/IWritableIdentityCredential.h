#pragma once

#include <android/binder_interface_utils.h>

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT
#include <aidl/android/hardware/identity/Certificate.h>
#include <aidl/android/hardware/identity/SecureAccessControlProfile.h>

namespace aidl {
namespace android {
namespace hardware {
namespace identity {
class IWritableIdentityCredential : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IWritableIdentityCredential();
  virtual ~IWritableIdentityCredential();

  static const int32_t version = 3;
  static inline const std::string hash = "1b6d65bb827aecd66860e06a8806dc77a8d3382b";
  static constexpr uint32_t TRANSACTION_getAttestationCertificate = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_startPersonalization = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_addAccessControlProfile = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_beginAddEntry = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_addEntryValue = FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_finishAddingEntries = FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_setExpectedProofOfProvisioningSize = FIRST_CALL_TRANSACTION + 6;

  static std::shared_ptr<IWritableIdentityCredential> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IWritableIdentityCredential>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IWritableIdentityCredential>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IWritableIdentityCredential>& impl);
  static const std::shared_ptr<IWritableIdentityCredential>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus getAttestationCertificate(const std::vector<uint8_t>& in_attestationApplicationId, const std::vector<uint8_t>& in_attestationChallenge, std::vector<::aidl::android::hardware::identity::Certificate>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus startPersonalization(int32_t in_accessControlProfileCount, const std::vector<int32_t>& in_entryCounts) = 0;
  virtual ::ndk::ScopedAStatus addAccessControlProfile(int32_t in_id, const ::aidl::android::hardware::identity::Certificate& in_readerCertificate, bool in_userAuthenticationRequired, int64_t in_timeoutMillis, int64_t in_secureUserId, ::aidl::android::hardware::identity::SecureAccessControlProfile* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus beginAddEntry(const std::vector<int32_t>& in_accessControlProfileIds, const std::string& in_nameSpace, const std::string& in_name, int32_t in_entrySize) = 0;
  virtual ::ndk::ScopedAStatus addEntryValue(const std::vector<uint8_t>& in_content, std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus finishAddingEntries(std::vector<uint8_t>* out_credentialData, std::vector<uint8_t>* out_proofOfProvisioningSignature) = 0;
  virtual ::ndk::ScopedAStatus setExpectedProofOfProvisioningSize(int32_t in_expectedProofOfProvisioningSize) = 0;
  virtual ::ndk::ScopedAStatus getInterfaceVersion(int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getInterfaceHash(std::string* _aidl_return) = 0;
private:
  static std::shared_ptr<IWritableIdentityCredential> default_impl;
};
class IWritableIdentityCredentialDefault : public IWritableIdentityCredential {
public:
  ::ndk::ScopedAStatus getAttestationCertificate(const std::vector<uint8_t>& in_attestationApplicationId, const std::vector<uint8_t>& in_attestationChallenge, std::vector<::aidl::android::hardware::identity::Certificate>* _aidl_return) override;
  ::ndk::ScopedAStatus startPersonalization(int32_t in_accessControlProfileCount, const std::vector<int32_t>& in_entryCounts) override;
  ::ndk::ScopedAStatus addAccessControlProfile(int32_t in_id, const ::aidl::android::hardware::identity::Certificate& in_readerCertificate, bool in_userAuthenticationRequired, int64_t in_timeoutMillis, int64_t in_secureUserId, ::aidl::android::hardware::identity::SecureAccessControlProfile* _aidl_return) override;
  ::ndk::ScopedAStatus beginAddEntry(const std::vector<int32_t>& in_accessControlProfileIds, const std::string& in_nameSpace, const std::string& in_name, int32_t in_entrySize) override;
  ::ndk::ScopedAStatus addEntryValue(const std::vector<uint8_t>& in_content, std::vector<uint8_t>* _aidl_return) override;
  ::ndk::ScopedAStatus finishAddingEntries(std::vector<uint8_t>* out_credentialData, std::vector<uint8_t>* out_proofOfProvisioningSignature) override;
  ::ndk::ScopedAStatus setExpectedProofOfProvisioningSize(int32_t in_expectedProofOfProvisioningSize) override;
  ::ndk::ScopedAStatus getInterfaceVersion(int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus getInterfaceHash(std::string* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace identity
}  // namespace hardware
}  // namespace android
}  // namespace aidl
