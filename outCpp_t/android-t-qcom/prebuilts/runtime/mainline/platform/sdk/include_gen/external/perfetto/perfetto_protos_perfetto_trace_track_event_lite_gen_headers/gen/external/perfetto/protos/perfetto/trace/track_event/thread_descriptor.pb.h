// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/track_event/thread_descriptor.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fthread_5fdescriptor_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fthread_5fdescriptor_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_util.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fthread_5fdescriptor_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fthread_5fdescriptor_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
namespace perfetto {
namespace protos {
class ThreadDescriptor;
class ThreadDescriptorDefaultTypeInternal;
extern ThreadDescriptorDefaultTypeInternal _ThreadDescriptor_default_instance_;
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> ::perfetto::protos::ThreadDescriptor* Arena::CreateMaybeMessage<::perfetto::protos::ThreadDescriptor>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace perfetto {
namespace protos {

enum ThreadDescriptor_ChromeThreadType : int {
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_UNSPECIFIED = 0,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_MAIN = 1,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_IO = 2,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_POOL_BG_WORKER = 3,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_POOL_FG_WORKER = 4,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_POOL_FB_BLOCKING = 5,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_POOL_BG_BLOCKING = 6,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_POOL_SERVICE = 7,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_COMPOSITOR = 8,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_VIZ_COMPOSITOR = 9,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_COMPOSITOR_WORKER = 10,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_SERVICE_WORKER = 11,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_MEMORY_INFRA = 50,
  ThreadDescriptor_ChromeThreadType_CHROME_THREAD_SAMPLING_PROFILER = 51
};
bool ThreadDescriptor_ChromeThreadType_IsValid(int value);
constexpr ThreadDescriptor_ChromeThreadType ThreadDescriptor_ChromeThreadType_ChromeThreadType_MIN = ThreadDescriptor_ChromeThreadType_CHROME_THREAD_UNSPECIFIED;
constexpr ThreadDescriptor_ChromeThreadType ThreadDescriptor_ChromeThreadType_ChromeThreadType_MAX = ThreadDescriptor_ChromeThreadType_CHROME_THREAD_SAMPLING_PROFILER;
constexpr int ThreadDescriptor_ChromeThreadType_ChromeThreadType_ARRAYSIZE = ThreadDescriptor_ChromeThreadType_ChromeThreadType_MAX + 1;

const std::string& ThreadDescriptor_ChromeThreadType_Name(ThreadDescriptor_ChromeThreadType value);
template<typename T>
inline const std::string& ThreadDescriptor_ChromeThreadType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ThreadDescriptor_ChromeThreadType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ThreadDescriptor_ChromeThreadType_Name.");
  return ThreadDescriptor_ChromeThreadType_Name(static_cast<ThreadDescriptor_ChromeThreadType>(enum_t_value));
}
bool ThreadDescriptor_ChromeThreadType_Parse(
    const std::string& name, ThreadDescriptor_ChromeThreadType* value);
// ===================================================================

class ThreadDescriptor :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:perfetto.protos.ThreadDescriptor) */ {
 public:
  ThreadDescriptor();
  virtual ~ThreadDescriptor();

  ThreadDescriptor(const ThreadDescriptor& from);
  ThreadDescriptor(ThreadDescriptor&& from) noexcept
    : ThreadDescriptor() {
    *this = ::std::move(from);
  }

  inline ThreadDescriptor& operator=(const ThreadDescriptor& from) {
    CopyFrom(from);
    return *this;
  }
  inline ThreadDescriptor& operator=(ThreadDescriptor&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const std::string& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline std::string* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ThreadDescriptor& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ThreadDescriptor* internal_default_instance() {
    return reinterpret_cast<const ThreadDescriptor*>(
               &_ThreadDescriptor_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ThreadDescriptor& a, ThreadDescriptor& b) {
    a.Swap(&b);
  }
  inline void Swap(ThreadDescriptor* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ThreadDescriptor* New() const final {
    return CreateMaybeMessage<ThreadDescriptor>(nullptr);
  }

  ThreadDescriptor* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ThreadDescriptor>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const ThreadDescriptor& from);
  void MergeFrom(const ThreadDescriptor& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  void DiscardUnknownFields();
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(ThreadDescriptor* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "perfetto.protos.ThreadDescriptor";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  typedef ThreadDescriptor_ChromeThreadType ChromeThreadType;
  static constexpr ChromeThreadType CHROME_THREAD_UNSPECIFIED =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_UNSPECIFIED;
  static constexpr ChromeThreadType CHROME_THREAD_MAIN =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_MAIN;
  static constexpr ChromeThreadType CHROME_THREAD_IO =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_IO;
  static constexpr ChromeThreadType CHROME_THREAD_POOL_BG_WORKER =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_POOL_BG_WORKER;
  static constexpr ChromeThreadType CHROME_THREAD_POOL_FG_WORKER =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_POOL_FG_WORKER;
  static constexpr ChromeThreadType CHROME_THREAD_POOL_FB_BLOCKING =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_POOL_FB_BLOCKING;
  static constexpr ChromeThreadType CHROME_THREAD_POOL_BG_BLOCKING =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_POOL_BG_BLOCKING;
  static constexpr ChromeThreadType CHROME_THREAD_POOL_SERVICE =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_POOL_SERVICE;
  static constexpr ChromeThreadType CHROME_THREAD_COMPOSITOR =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_COMPOSITOR;
  static constexpr ChromeThreadType CHROME_THREAD_VIZ_COMPOSITOR =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_VIZ_COMPOSITOR;
  static constexpr ChromeThreadType CHROME_THREAD_COMPOSITOR_WORKER =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_COMPOSITOR_WORKER;
  static constexpr ChromeThreadType CHROME_THREAD_SERVICE_WORKER =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_SERVICE_WORKER;
  static constexpr ChromeThreadType CHROME_THREAD_MEMORY_INFRA =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_MEMORY_INFRA;
  static constexpr ChromeThreadType CHROME_THREAD_SAMPLING_PROFILER =
    ThreadDescriptor_ChromeThreadType_CHROME_THREAD_SAMPLING_PROFILER;
  static inline bool ChromeThreadType_IsValid(int value) {
    return ThreadDescriptor_ChromeThreadType_IsValid(value);
  }
  static constexpr ChromeThreadType ChromeThreadType_MIN =
    ThreadDescriptor_ChromeThreadType_ChromeThreadType_MIN;
  static constexpr ChromeThreadType ChromeThreadType_MAX =
    ThreadDescriptor_ChromeThreadType_ChromeThreadType_MAX;
  static constexpr int ChromeThreadType_ARRAYSIZE =
    ThreadDescriptor_ChromeThreadType_ChromeThreadType_ARRAYSIZE;
  template<typename T>
  static inline const std::string& ChromeThreadType_Name(T enum_t_value) {
    static_assert(::std::is_same<T, ChromeThreadType>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function ChromeThreadType_Name.");
    return ThreadDescriptor_ChromeThreadType_Name(enum_t_value);
  }
  static inline bool ChromeThreadType_Parse(const std::string& name,
      ChromeThreadType* value) {
    return ThreadDescriptor_ChromeThreadType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kThreadNameFieldNumber = 5,
    kPidFieldNumber = 1,
    kTidFieldNumber = 2,
    kLegacySortIndexFieldNumber = 3,
    kChromeThreadTypeFieldNumber = 4,
    kReferenceTimestampUsFieldNumber = 6,
    kReferenceThreadTimeUsFieldNumber = 7,
    kReferenceThreadInstructionCountFieldNumber = 8,
  };
  // optional string thread_name = 5;
  bool has_thread_name() const;
  void clear_thread_name();
  const std::string& thread_name() const;
  void set_thread_name(const std::string& value);
  void set_thread_name(std::string&& value);
  void set_thread_name(const char* value);
  void set_thread_name(const char* value, size_t size);
  std::string* mutable_thread_name();
  std::string* release_thread_name();
  void set_allocated_thread_name(std::string* thread_name);

  // optional int32 pid = 1;
  bool has_pid() const;
  void clear_pid();
  ::PROTOBUF_NAMESPACE_ID::int32 pid() const;
  void set_pid(::PROTOBUF_NAMESPACE_ID::int32 value);

  // optional int32 tid = 2;
  bool has_tid() const;
  void clear_tid();
  ::PROTOBUF_NAMESPACE_ID::int32 tid() const;
  void set_tid(::PROTOBUF_NAMESPACE_ID::int32 value);

  // optional int32 legacy_sort_index = 3;
  bool has_legacy_sort_index() const;
  void clear_legacy_sort_index();
  ::PROTOBUF_NAMESPACE_ID::int32 legacy_sort_index() const;
  void set_legacy_sort_index(::PROTOBUF_NAMESPACE_ID::int32 value);

  // optional .perfetto.protos.ThreadDescriptor.ChromeThreadType chrome_thread_type = 4;
  bool has_chrome_thread_type() const;
  void clear_chrome_thread_type();
  ::perfetto::protos::ThreadDescriptor_ChromeThreadType chrome_thread_type() const;
  void set_chrome_thread_type(::perfetto::protos::ThreadDescriptor_ChromeThreadType value);

  // optional int64 reference_timestamp_us = 6;
  bool has_reference_timestamp_us() const;
  void clear_reference_timestamp_us();
  ::PROTOBUF_NAMESPACE_ID::int64 reference_timestamp_us() const;
  void set_reference_timestamp_us(::PROTOBUF_NAMESPACE_ID::int64 value);

  // optional int64 reference_thread_time_us = 7;
  bool has_reference_thread_time_us() const;
  void clear_reference_thread_time_us();
  ::PROTOBUF_NAMESPACE_ID::int64 reference_thread_time_us() const;
  void set_reference_thread_time_us(::PROTOBUF_NAMESPACE_ID::int64 value);

  // optional int64 reference_thread_instruction_count = 8;
  bool has_reference_thread_instruction_count() const;
  void clear_reference_thread_instruction_count();
  ::PROTOBUF_NAMESPACE_ID::int64 reference_thread_instruction_count() const;
  void set_reference_thread_instruction_count(::PROTOBUF_NAMESPACE_ID::int64 value);

  // @@protoc_insertion_point(class_scope:perfetto.protos.ThreadDescriptor)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr thread_name_;
  ::PROTOBUF_NAMESPACE_ID::int32 pid_;
  ::PROTOBUF_NAMESPACE_ID::int32 tid_;
  ::PROTOBUF_NAMESPACE_ID::int32 legacy_sort_index_;
  int chrome_thread_type_;
  ::PROTOBUF_NAMESPACE_ID::int64 reference_timestamp_us_;
  ::PROTOBUF_NAMESPACE_ID::int64 reference_thread_time_us_;
  ::PROTOBUF_NAMESPACE_ID::int64 reference_thread_instruction_count_;
  friend struct ::TableStruct_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fthread_5fdescriptor_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ThreadDescriptor

// optional int32 pid = 1;
inline bool ThreadDescriptor::has_pid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ThreadDescriptor::clear_pid() {
  pid_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ThreadDescriptor::pid() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ThreadDescriptor.pid)
  return pid_;
}
inline void ThreadDescriptor::set_pid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  pid_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ThreadDescriptor.pid)
}

// optional int32 tid = 2;
inline bool ThreadDescriptor::has_tid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ThreadDescriptor::clear_tid() {
  tid_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ThreadDescriptor::tid() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ThreadDescriptor.tid)
  return tid_;
}
inline void ThreadDescriptor::set_tid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000004u;
  tid_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ThreadDescriptor.tid)
}

// optional string thread_name = 5;
inline bool ThreadDescriptor::has_thread_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ThreadDescriptor::clear_thread_name() {
  thread_name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& ThreadDescriptor::thread_name() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ThreadDescriptor.thread_name)
  return thread_name_.GetNoArena();
}
inline void ThreadDescriptor::set_thread_name(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  thread_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:perfetto.protos.ThreadDescriptor.thread_name)
}
inline void ThreadDescriptor::set_thread_name(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  thread_name_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:perfetto.protos.ThreadDescriptor.thread_name)
}
inline void ThreadDescriptor::set_thread_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  thread_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:perfetto.protos.ThreadDescriptor.thread_name)
}
inline void ThreadDescriptor::set_thread_name(const char* value, size_t size) {
  _has_bits_[0] |= 0x00000001u;
  thread_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:perfetto.protos.ThreadDescriptor.thread_name)
}
inline std::string* ThreadDescriptor::mutable_thread_name() {
  _has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_mutable:perfetto.protos.ThreadDescriptor.thread_name)
  return thread_name_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* ThreadDescriptor::release_thread_name() {
  // @@protoc_insertion_point(field_release:perfetto.protos.ThreadDescriptor.thread_name)
  if (!has_thread_name()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return thread_name_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void ThreadDescriptor::set_allocated_thread_name(std::string* thread_name) {
  if (thread_name != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  thread_name_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), thread_name);
  // @@protoc_insertion_point(field_set_allocated:perfetto.protos.ThreadDescriptor.thread_name)
}

// optional .perfetto.protos.ThreadDescriptor.ChromeThreadType chrome_thread_type = 4;
inline bool ThreadDescriptor::has_chrome_thread_type() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ThreadDescriptor::clear_chrome_thread_type() {
  chrome_thread_type_ = 0;
  _has_bits_[0] &= ~0x00000010u;
}
inline ::perfetto::protos::ThreadDescriptor_ChromeThreadType ThreadDescriptor::chrome_thread_type() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ThreadDescriptor.chrome_thread_type)
  return static_cast< ::perfetto::protos::ThreadDescriptor_ChromeThreadType >(chrome_thread_type_);
}
inline void ThreadDescriptor::set_chrome_thread_type(::perfetto::protos::ThreadDescriptor_ChromeThreadType value) {
  assert(::perfetto::protos::ThreadDescriptor_ChromeThreadType_IsValid(value));
  _has_bits_[0] |= 0x00000010u;
  chrome_thread_type_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ThreadDescriptor.chrome_thread_type)
}

// optional int64 reference_timestamp_us = 6;
inline bool ThreadDescriptor::has_reference_timestamp_us() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ThreadDescriptor::clear_reference_timestamp_us() {
  reference_timestamp_us_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000020u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 ThreadDescriptor::reference_timestamp_us() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ThreadDescriptor.reference_timestamp_us)
  return reference_timestamp_us_;
}
inline void ThreadDescriptor::set_reference_timestamp_us(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000020u;
  reference_timestamp_us_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ThreadDescriptor.reference_timestamp_us)
}

// optional int64 reference_thread_time_us = 7;
inline bool ThreadDescriptor::has_reference_thread_time_us() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void ThreadDescriptor::clear_reference_thread_time_us() {
  reference_thread_time_us_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000040u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 ThreadDescriptor::reference_thread_time_us() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ThreadDescriptor.reference_thread_time_us)
  return reference_thread_time_us_;
}
inline void ThreadDescriptor::set_reference_thread_time_us(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000040u;
  reference_thread_time_us_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ThreadDescriptor.reference_thread_time_us)
}

// optional int64 reference_thread_instruction_count = 8;
inline bool ThreadDescriptor::has_reference_thread_instruction_count() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void ThreadDescriptor::clear_reference_thread_instruction_count() {
  reference_thread_instruction_count_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000080u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 ThreadDescriptor::reference_thread_instruction_count() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ThreadDescriptor.reference_thread_instruction_count)
  return reference_thread_instruction_count_;
}
inline void ThreadDescriptor::set_reference_thread_instruction_count(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000080u;
  reference_thread_instruction_count_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ThreadDescriptor.reference_thread_instruction_count)
}

// optional int32 legacy_sort_index = 3;
inline bool ThreadDescriptor::has_legacy_sort_index() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ThreadDescriptor::clear_legacy_sort_index() {
  legacy_sort_index_ = 0;
  _has_bits_[0] &= ~0x00000008u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ThreadDescriptor::legacy_sort_index() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ThreadDescriptor.legacy_sort_index)
  return legacy_sort_index_;
}
inline void ThreadDescriptor::set_legacy_sort_index(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000008u;
  legacy_sort_index_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ThreadDescriptor.legacy_sort_index)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protos
}  // namespace perfetto

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::perfetto::protos::ThreadDescriptor_ChromeThreadType> : ::std::true_type {};

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fthread_5fdescriptor_2eproto