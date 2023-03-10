// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/track_event/chrome_frame_reporter.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fframe_5freporter_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fframe_5freporter_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fframe_5freporter_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fframe_5freporter_2eproto {
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
class ChromeFrameReporter;
class ChromeFrameReporterDefaultTypeInternal;
extern ChromeFrameReporterDefaultTypeInternal _ChromeFrameReporter_default_instance_;
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> ::perfetto::protos::ChromeFrameReporter* Arena::CreateMaybeMessage<::perfetto::protos::ChromeFrameReporter>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace perfetto {
namespace protos {

enum ChromeFrameReporter_State : int {
  ChromeFrameReporter_State_STATE_NO_UPDATE_DESIRED = 0,
  ChromeFrameReporter_State_STATE_PRESENTED_ALL = 1,
  ChromeFrameReporter_State_STATE_PRESENTED_PARTIAL = 2,
  ChromeFrameReporter_State_STATE_DROPPED = 3
};
bool ChromeFrameReporter_State_IsValid(int value);
constexpr ChromeFrameReporter_State ChromeFrameReporter_State_State_MIN = ChromeFrameReporter_State_STATE_NO_UPDATE_DESIRED;
constexpr ChromeFrameReporter_State ChromeFrameReporter_State_State_MAX = ChromeFrameReporter_State_STATE_DROPPED;
constexpr int ChromeFrameReporter_State_State_ARRAYSIZE = ChromeFrameReporter_State_State_MAX + 1;

const std::string& ChromeFrameReporter_State_Name(ChromeFrameReporter_State value);
template<typename T>
inline const std::string& ChromeFrameReporter_State_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ChromeFrameReporter_State>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ChromeFrameReporter_State_Name.");
  return ChromeFrameReporter_State_Name(static_cast<ChromeFrameReporter_State>(enum_t_value));
}
bool ChromeFrameReporter_State_Parse(
    const std::string& name, ChromeFrameReporter_State* value);
enum ChromeFrameReporter_FrameDropReason : int {
  ChromeFrameReporter_FrameDropReason_REASON_UNSPECIFIED = 0,
  ChromeFrameReporter_FrameDropReason_REASON_DISPLAY_COMPOSITOR = 1,
  ChromeFrameReporter_FrameDropReason_REASON_MAIN_THREAD = 2,
  ChromeFrameReporter_FrameDropReason_REASON_CLIENT_COMPOSITOR = 3
};
bool ChromeFrameReporter_FrameDropReason_IsValid(int value);
constexpr ChromeFrameReporter_FrameDropReason ChromeFrameReporter_FrameDropReason_FrameDropReason_MIN = ChromeFrameReporter_FrameDropReason_REASON_UNSPECIFIED;
constexpr ChromeFrameReporter_FrameDropReason ChromeFrameReporter_FrameDropReason_FrameDropReason_MAX = ChromeFrameReporter_FrameDropReason_REASON_CLIENT_COMPOSITOR;
constexpr int ChromeFrameReporter_FrameDropReason_FrameDropReason_ARRAYSIZE = ChromeFrameReporter_FrameDropReason_FrameDropReason_MAX + 1;

const std::string& ChromeFrameReporter_FrameDropReason_Name(ChromeFrameReporter_FrameDropReason value);
template<typename T>
inline const std::string& ChromeFrameReporter_FrameDropReason_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ChromeFrameReporter_FrameDropReason>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ChromeFrameReporter_FrameDropReason_Name.");
  return ChromeFrameReporter_FrameDropReason_Name(static_cast<ChromeFrameReporter_FrameDropReason>(enum_t_value));
}
bool ChromeFrameReporter_FrameDropReason_Parse(
    const std::string& name, ChromeFrameReporter_FrameDropReason* value);
enum ChromeFrameReporter_ScrollState : int {
  ChromeFrameReporter_ScrollState_SCROLL_NONE = 0,
  ChromeFrameReporter_ScrollState_SCROLL_MAIN_THREAD = 1,
  ChromeFrameReporter_ScrollState_SCROLL_COMPOSITOR_THREAD = 2,
  ChromeFrameReporter_ScrollState_SCROLL_UNKNOWN = 3
};
bool ChromeFrameReporter_ScrollState_IsValid(int value);
constexpr ChromeFrameReporter_ScrollState ChromeFrameReporter_ScrollState_ScrollState_MIN = ChromeFrameReporter_ScrollState_SCROLL_NONE;
constexpr ChromeFrameReporter_ScrollState ChromeFrameReporter_ScrollState_ScrollState_MAX = ChromeFrameReporter_ScrollState_SCROLL_UNKNOWN;
constexpr int ChromeFrameReporter_ScrollState_ScrollState_ARRAYSIZE = ChromeFrameReporter_ScrollState_ScrollState_MAX + 1;

const std::string& ChromeFrameReporter_ScrollState_Name(ChromeFrameReporter_ScrollState value);
template<typename T>
inline const std::string& ChromeFrameReporter_ScrollState_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ChromeFrameReporter_ScrollState>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ChromeFrameReporter_ScrollState_Name.");
  return ChromeFrameReporter_ScrollState_Name(static_cast<ChromeFrameReporter_ScrollState>(enum_t_value));
}
bool ChromeFrameReporter_ScrollState_Parse(
    const std::string& name, ChromeFrameReporter_ScrollState* value);
// ===================================================================

class ChromeFrameReporter :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:perfetto.protos.ChromeFrameReporter) */ {
 public:
  ChromeFrameReporter();
  virtual ~ChromeFrameReporter();

  ChromeFrameReporter(const ChromeFrameReporter& from);
  ChromeFrameReporter(ChromeFrameReporter&& from) noexcept
    : ChromeFrameReporter() {
    *this = ::std::move(from);
  }

  inline ChromeFrameReporter& operator=(const ChromeFrameReporter& from) {
    CopyFrom(from);
    return *this;
  }
  inline ChromeFrameReporter& operator=(ChromeFrameReporter&& from) noexcept {
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

  static const ChromeFrameReporter& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ChromeFrameReporter* internal_default_instance() {
    return reinterpret_cast<const ChromeFrameReporter*>(
               &_ChromeFrameReporter_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ChromeFrameReporter& a, ChromeFrameReporter& b) {
    a.Swap(&b);
  }
  inline void Swap(ChromeFrameReporter* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ChromeFrameReporter* New() const final {
    return CreateMaybeMessage<ChromeFrameReporter>(nullptr);
  }

  ChromeFrameReporter* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ChromeFrameReporter>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const ChromeFrameReporter& from);
  void MergeFrom(const ChromeFrameReporter& from);
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
  void InternalSwap(ChromeFrameReporter* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "perfetto.protos.ChromeFrameReporter";
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

  typedef ChromeFrameReporter_State State;
  static constexpr State STATE_NO_UPDATE_DESIRED =
    ChromeFrameReporter_State_STATE_NO_UPDATE_DESIRED;
  static constexpr State STATE_PRESENTED_ALL =
    ChromeFrameReporter_State_STATE_PRESENTED_ALL;
  static constexpr State STATE_PRESENTED_PARTIAL =
    ChromeFrameReporter_State_STATE_PRESENTED_PARTIAL;
  static constexpr State STATE_DROPPED =
    ChromeFrameReporter_State_STATE_DROPPED;
  static inline bool State_IsValid(int value) {
    return ChromeFrameReporter_State_IsValid(value);
  }
  static constexpr State State_MIN =
    ChromeFrameReporter_State_State_MIN;
  static constexpr State State_MAX =
    ChromeFrameReporter_State_State_MAX;
  static constexpr int State_ARRAYSIZE =
    ChromeFrameReporter_State_State_ARRAYSIZE;
  template<typename T>
  static inline const std::string& State_Name(T enum_t_value) {
    static_assert(::std::is_same<T, State>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function State_Name.");
    return ChromeFrameReporter_State_Name(enum_t_value);
  }
  static inline bool State_Parse(const std::string& name,
      State* value) {
    return ChromeFrameReporter_State_Parse(name, value);
  }

  typedef ChromeFrameReporter_FrameDropReason FrameDropReason;
  static constexpr FrameDropReason REASON_UNSPECIFIED =
    ChromeFrameReporter_FrameDropReason_REASON_UNSPECIFIED;
  static constexpr FrameDropReason REASON_DISPLAY_COMPOSITOR =
    ChromeFrameReporter_FrameDropReason_REASON_DISPLAY_COMPOSITOR;
  static constexpr FrameDropReason REASON_MAIN_THREAD =
    ChromeFrameReporter_FrameDropReason_REASON_MAIN_THREAD;
  static constexpr FrameDropReason REASON_CLIENT_COMPOSITOR =
    ChromeFrameReporter_FrameDropReason_REASON_CLIENT_COMPOSITOR;
  static inline bool FrameDropReason_IsValid(int value) {
    return ChromeFrameReporter_FrameDropReason_IsValid(value);
  }
  static constexpr FrameDropReason FrameDropReason_MIN =
    ChromeFrameReporter_FrameDropReason_FrameDropReason_MIN;
  static constexpr FrameDropReason FrameDropReason_MAX =
    ChromeFrameReporter_FrameDropReason_FrameDropReason_MAX;
  static constexpr int FrameDropReason_ARRAYSIZE =
    ChromeFrameReporter_FrameDropReason_FrameDropReason_ARRAYSIZE;
  template<typename T>
  static inline const std::string& FrameDropReason_Name(T enum_t_value) {
    static_assert(::std::is_same<T, FrameDropReason>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function FrameDropReason_Name.");
    return ChromeFrameReporter_FrameDropReason_Name(enum_t_value);
  }
  static inline bool FrameDropReason_Parse(const std::string& name,
      FrameDropReason* value) {
    return ChromeFrameReporter_FrameDropReason_Parse(name, value);
  }

  typedef ChromeFrameReporter_ScrollState ScrollState;
  static constexpr ScrollState SCROLL_NONE =
    ChromeFrameReporter_ScrollState_SCROLL_NONE;
  static constexpr ScrollState SCROLL_MAIN_THREAD =
    ChromeFrameReporter_ScrollState_SCROLL_MAIN_THREAD;
  static constexpr ScrollState SCROLL_COMPOSITOR_THREAD =
    ChromeFrameReporter_ScrollState_SCROLL_COMPOSITOR_THREAD;
  static constexpr ScrollState SCROLL_UNKNOWN =
    ChromeFrameReporter_ScrollState_SCROLL_UNKNOWN;
  static inline bool ScrollState_IsValid(int value) {
    return ChromeFrameReporter_ScrollState_IsValid(value);
  }
  static constexpr ScrollState ScrollState_MIN =
    ChromeFrameReporter_ScrollState_ScrollState_MIN;
  static constexpr ScrollState ScrollState_MAX =
    ChromeFrameReporter_ScrollState_ScrollState_MAX;
  static constexpr int ScrollState_ARRAYSIZE =
    ChromeFrameReporter_ScrollState_ScrollState_ARRAYSIZE;
  template<typename T>
  static inline const std::string& ScrollState_Name(T enum_t_value) {
    static_assert(::std::is_same<T, ScrollState>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function ScrollState_Name.");
    return ChromeFrameReporter_ScrollState_Name(enum_t_value);
  }
  static inline bool ScrollState_Parse(const std::string& name,
      ScrollState* value) {
    return ChromeFrameReporter_ScrollState_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kStateFieldNumber = 1,
    kReasonFieldNumber = 2,
    kFrameSourceFieldNumber = 3,
    kFrameSequenceFieldNumber = 4,
    kScrollStateFieldNumber = 6,
    kAffectsSmoothnessFieldNumber = 5,
    kHasMainAnimationFieldNumber = 7,
    kHasCompositorAnimationFieldNumber = 8,
    kHasSmoothInputMainFieldNumber = 9,
    kLayerTreeHostIdFieldNumber = 11,
    kHasMissingContentFieldNumber = 10,
  };
  // optional .perfetto.protos.ChromeFrameReporter.State state = 1;
  bool has_state() const;
  void clear_state();
  ::perfetto::protos::ChromeFrameReporter_State state() const;
  void set_state(::perfetto::protos::ChromeFrameReporter_State value);

  // optional .perfetto.protos.ChromeFrameReporter.FrameDropReason reason = 2;
  bool has_reason() const;
  void clear_reason();
  ::perfetto::protos::ChromeFrameReporter_FrameDropReason reason() const;
  void set_reason(::perfetto::protos::ChromeFrameReporter_FrameDropReason value);

  // optional uint64 frame_source = 3;
  bool has_frame_source() const;
  void clear_frame_source();
  ::PROTOBUF_NAMESPACE_ID::uint64 frame_source() const;
  void set_frame_source(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional uint64 frame_sequence = 4;
  bool has_frame_sequence() const;
  void clear_frame_sequence();
  ::PROTOBUF_NAMESPACE_ID::uint64 frame_sequence() const;
  void set_frame_sequence(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional .perfetto.protos.ChromeFrameReporter.ScrollState scroll_state = 6;
  bool has_scroll_state() const;
  void clear_scroll_state();
  ::perfetto::protos::ChromeFrameReporter_ScrollState scroll_state() const;
  void set_scroll_state(::perfetto::protos::ChromeFrameReporter_ScrollState value);

  // optional bool affects_smoothness = 5;
  bool has_affects_smoothness() const;
  void clear_affects_smoothness();
  bool affects_smoothness() const;
  void set_affects_smoothness(bool value);

  // optional bool has_main_animation = 7;
  bool has_has_main_animation() const;
  void clear_has_main_animation();
  bool has_main_animation() const;
  void set_has_main_animation(bool value);

  // optional bool has_compositor_animation = 8;
  bool has_has_compositor_animation() const;
  void clear_has_compositor_animation();
  bool has_compositor_animation() const;
  void set_has_compositor_animation(bool value);

  // optional bool has_smooth_input_main = 9;
  bool has_has_smooth_input_main() const;
  void clear_has_smooth_input_main();
  bool has_smooth_input_main() const;
  void set_has_smooth_input_main(bool value);

  // optional uint64 layer_tree_host_id = 11;
  bool has_layer_tree_host_id() const;
  void clear_layer_tree_host_id();
  ::PROTOBUF_NAMESPACE_ID::uint64 layer_tree_host_id() const;
  void set_layer_tree_host_id(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional bool has_missing_content = 10;
  bool has_has_missing_content() const;
  void clear_has_missing_content();
  bool has_missing_content() const;
  void set_has_missing_content(bool value);

  // @@protoc_insertion_point(class_scope:perfetto.protos.ChromeFrameReporter)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  int state_;
  int reason_;
  ::PROTOBUF_NAMESPACE_ID::uint64 frame_source_;
  ::PROTOBUF_NAMESPACE_ID::uint64 frame_sequence_;
  int scroll_state_;
  bool affects_smoothness_;
  bool has_main_animation_;
  bool has_compositor_animation_;
  bool has_smooth_input_main_;
  ::PROTOBUF_NAMESPACE_ID::uint64 layer_tree_host_id_;
  bool has_missing_content_;
  friend struct ::TableStruct_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fframe_5freporter_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ChromeFrameReporter

// optional .perfetto.protos.ChromeFrameReporter.State state = 1;
inline bool ChromeFrameReporter::has_state() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ChromeFrameReporter::clear_state() {
  state_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::perfetto::protos::ChromeFrameReporter_State ChromeFrameReporter::state() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.state)
  return static_cast< ::perfetto::protos::ChromeFrameReporter_State >(state_);
}
inline void ChromeFrameReporter::set_state(::perfetto::protos::ChromeFrameReporter_State value) {
  assert(::perfetto::protos::ChromeFrameReporter_State_IsValid(value));
  _has_bits_[0] |= 0x00000001u;
  state_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.state)
}

// optional .perfetto.protos.ChromeFrameReporter.FrameDropReason reason = 2;
inline bool ChromeFrameReporter::has_reason() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ChromeFrameReporter::clear_reason() {
  reason_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::perfetto::protos::ChromeFrameReporter_FrameDropReason ChromeFrameReporter::reason() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.reason)
  return static_cast< ::perfetto::protos::ChromeFrameReporter_FrameDropReason >(reason_);
}
inline void ChromeFrameReporter::set_reason(::perfetto::protos::ChromeFrameReporter_FrameDropReason value) {
  assert(::perfetto::protos::ChromeFrameReporter_FrameDropReason_IsValid(value));
  _has_bits_[0] |= 0x00000002u;
  reason_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.reason)
}

// optional uint64 frame_source = 3;
inline bool ChromeFrameReporter::has_frame_source() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ChromeFrameReporter::clear_frame_source() {
  frame_source_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 ChromeFrameReporter::frame_source() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.frame_source)
  return frame_source_;
}
inline void ChromeFrameReporter::set_frame_source(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000004u;
  frame_source_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.frame_source)
}

// optional uint64 frame_sequence = 4;
inline bool ChromeFrameReporter::has_frame_sequence() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ChromeFrameReporter::clear_frame_sequence() {
  frame_sequence_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000008u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 ChromeFrameReporter::frame_sequence() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.frame_sequence)
  return frame_sequence_;
}
inline void ChromeFrameReporter::set_frame_sequence(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000008u;
  frame_sequence_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.frame_sequence)
}

// optional bool affects_smoothness = 5;
inline bool ChromeFrameReporter::has_affects_smoothness() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ChromeFrameReporter::clear_affects_smoothness() {
  affects_smoothness_ = false;
  _has_bits_[0] &= ~0x00000020u;
}
inline bool ChromeFrameReporter::affects_smoothness() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.affects_smoothness)
  return affects_smoothness_;
}
inline void ChromeFrameReporter::set_affects_smoothness(bool value) {
  _has_bits_[0] |= 0x00000020u;
  affects_smoothness_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.affects_smoothness)
}

// optional .perfetto.protos.ChromeFrameReporter.ScrollState scroll_state = 6;
inline bool ChromeFrameReporter::has_scroll_state() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ChromeFrameReporter::clear_scroll_state() {
  scroll_state_ = 0;
  _has_bits_[0] &= ~0x00000010u;
}
inline ::perfetto::protos::ChromeFrameReporter_ScrollState ChromeFrameReporter::scroll_state() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.scroll_state)
  return static_cast< ::perfetto::protos::ChromeFrameReporter_ScrollState >(scroll_state_);
}
inline void ChromeFrameReporter::set_scroll_state(::perfetto::protos::ChromeFrameReporter_ScrollState value) {
  assert(::perfetto::protos::ChromeFrameReporter_ScrollState_IsValid(value));
  _has_bits_[0] |= 0x00000010u;
  scroll_state_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.scroll_state)
}

// optional bool has_main_animation = 7;
inline bool ChromeFrameReporter::has_has_main_animation() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void ChromeFrameReporter::clear_has_main_animation() {
  has_main_animation_ = false;
  _has_bits_[0] &= ~0x00000040u;
}
inline bool ChromeFrameReporter::has_main_animation() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.has_main_animation)
  return has_main_animation_;
}
inline void ChromeFrameReporter::set_has_main_animation(bool value) {
  _has_bits_[0] |= 0x00000040u;
  has_main_animation_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.has_main_animation)
}

// optional bool has_compositor_animation = 8;
inline bool ChromeFrameReporter::has_has_compositor_animation() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void ChromeFrameReporter::clear_has_compositor_animation() {
  has_compositor_animation_ = false;
  _has_bits_[0] &= ~0x00000080u;
}
inline bool ChromeFrameReporter::has_compositor_animation() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.has_compositor_animation)
  return has_compositor_animation_;
}
inline void ChromeFrameReporter::set_has_compositor_animation(bool value) {
  _has_bits_[0] |= 0x00000080u;
  has_compositor_animation_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.has_compositor_animation)
}

// optional bool has_smooth_input_main = 9;
inline bool ChromeFrameReporter::has_has_smooth_input_main() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void ChromeFrameReporter::clear_has_smooth_input_main() {
  has_smooth_input_main_ = false;
  _has_bits_[0] &= ~0x00000100u;
}
inline bool ChromeFrameReporter::has_smooth_input_main() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.has_smooth_input_main)
  return has_smooth_input_main_;
}
inline void ChromeFrameReporter::set_has_smooth_input_main(bool value) {
  _has_bits_[0] |= 0x00000100u;
  has_smooth_input_main_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.has_smooth_input_main)
}

// optional bool has_missing_content = 10;
inline bool ChromeFrameReporter::has_has_missing_content() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void ChromeFrameReporter::clear_has_missing_content() {
  has_missing_content_ = false;
  _has_bits_[0] &= ~0x00000400u;
}
inline bool ChromeFrameReporter::has_missing_content() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.has_missing_content)
  return has_missing_content_;
}
inline void ChromeFrameReporter::set_has_missing_content(bool value) {
  _has_bits_[0] |= 0x00000400u;
  has_missing_content_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.has_missing_content)
}

// optional uint64 layer_tree_host_id = 11;
inline bool ChromeFrameReporter::has_layer_tree_host_id() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void ChromeFrameReporter::clear_layer_tree_host_id() {
  layer_tree_host_id_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000200u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 ChromeFrameReporter::layer_tree_host_id() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ChromeFrameReporter.layer_tree_host_id)
  return layer_tree_host_id_;
}
inline void ChromeFrameReporter::set_layer_tree_host_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000200u;
  layer_tree_host_id_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ChromeFrameReporter.layer_tree_host_id)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protos
}  // namespace perfetto

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::perfetto::protos::ChromeFrameReporter_State> : ::std::true_type {};
template <> struct is_proto_enum< ::perfetto::protos::ChromeFrameReporter_FrameDropReason> : ::std::true_type {};
template <> struct is_proto_enum< ::perfetto::protos::ChromeFrameReporter_ScrollState> : ::std::true_type {};

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fframe_5freporter_2eproto
