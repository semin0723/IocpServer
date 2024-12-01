// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: testPacket.proto
// Protobuf C++ Version: 5.28.3

#ifndef GOOGLE_PROTOBUF_INCLUDED_testPacket_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_testPacket_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5028003
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_testPacket_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_testPacket_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_testPacket_2eproto;
namespace sample {
class TestReq;
struct TestReqDefaultTypeInternal;
extern TestReqDefaultTypeInternal _TestReq_default_instance_;
class TestResult;
struct TestResultDefaultTypeInternal;
extern TestResultDefaultTypeInternal _TestResult_default_instance_;
}  // namespace sample
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace sample {

// ===================================================================


// -------------------------------------------------------------------

class TestResult final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:sample.TestResult) */ {
 public:
  inline TestResult() : TestResult(nullptr) {}
  ~TestResult() PROTOBUF_FINAL;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR TestResult(
      ::google::protobuf::internal::ConstantInitialized);

  inline TestResult(const TestResult& from) : TestResult(nullptr, from) {}
  inline TestResult(TestResult&& from) noexcept
      : TestResult(nullptr, std::move(from)) {}
  inline TestResult& operator=(const TestResult& from) {
    CopyFrom(from);
    return *this;
  }
  inline TestResult& operator=(TestResult&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const TestResult& default_instance() {
    return *internal_default_instance();
  }
  static inline const TestResult* internal_default_instance() {
    return reinterpret_cast<const TestResult*>(
        &_TestResult_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(TestResult& a, TestResult& b) { a.Swap(&b); }
  inline void Swap(TestResult* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TestResult* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  TestResult* New(::google::protobuf::Arena* arena = nullptr) const PROTOBUF_FINAL {
    return ::google::protobuf::Message::DefaultConstruct<TestResult>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const TestResult& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const TestResult& from) { TestResult::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(TestResult* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "sample.TestResult"; }

 protected:
  explicit TestResult(::google::protobuf::Arena* arena);
  TestResult(::google::protobuf::Arena* arena, const TestResult& from);
  TestResult(::google::protobuf::Arena* arena, TestResult&& from) noexcept
      : TestResult(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const PROTOBUF_FINAL;
  static const ::google::protobuf::Message::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kTestIdFieldNumber = 1,
  };
  // optional uint32 TestId = 1;
  bool has_testid() const;
  void clear_testid() ;
  ::uint32_t testid() const;
  void set_testid(::uint32_t value);

  private:
  ::uint32_t _internal_testid() const;
  void _internal_set_testid(::uint32_t value);

  public:
  // @@protoc_insertion_point(class_scope:sample.TestResult)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      0, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_TestResult_default_instance_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const TestResult& from_msg);
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    ::uint32_t testid_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_testPacket_2eproto;
};
// -------------------------------------------------------------------

class TestReq final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:sample.TestReq) */ {
 public:
  inline TestReq() : TestReq(nullptr) {}
  ~TestReq() PROTOBUF_FINAL;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR TestReq(
      ::google::protobuf::internal::ConstantInitialized);

  inline TestReq(const TestReq& from) : TestReq(nullptr, from) {}
  inline TestReq(TestReq&& from) noexcept
      : TestReq(nullptr, std::move(from)) {}
  inline TestReq& operator=(const TestReq& from) {
    CopyFrom(from);
    return *this;
  }
  inline TestReq& operator=(TestReq&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const TestReq& default_instance() {
    return *internal_default_instance();
  }
  static inline const TestReq* internal_default_instance() {
    return reinterpret_cast<const TestReq*>(
        &_TestReq_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(TestReq& a, TestReq& b) { a.Swap(&b); }
  inline void Swap(TestReq* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TestReq* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  TestReq* New(::google::protobuf::Arena* arena = nullptr) const PROTOBUF_FINAL {
    return ::google::protobuf::Message::DefaultConstruct<TestReq>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const TestReq& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const TestReq& from) { TestReq::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(TestReq* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "sample.TestReq"; }

 protected:
  explicit TestReq(::google::protobuf::Arena* arena);
  TestReq(::google::protobuf::Arena* arena, const TestReq& from);
  TestReq(::google::protobuf::Arena* arena, TestReq&& from) noexcept
      : TestReq(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const PROTOBUF_FINAL;
  static const ::google::protobuf::Message::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kTestIdFieldNumber = 1,
  };
  // optional uint32 TestId = 1;
  bool has_testid() const;
  void clear_testid() ;
  ::uint32_t testid() const;
  void set_testid(::uint32_t value);

  private:
  ::uint32_t _internal_testid() const;
  void _internal_set_testid(::uint32_t value);

  public:
  // @@protoc_insertion_point(class_scope:sample.TestReq)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      0, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_TestReq_default_instance_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const TestReq& from_msg);
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    ::uint32_t testid_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_testPacket_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// TestReq

// optional uint32 TestId = 1;
inline bool TestReq::has_testid() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline void TestReq::clear_testid() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.testid_ = 0u;
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline ::uint32_t TestReq::testid() const {
  // @@protoc_insertion_point(field_get:sample.TestReq.TestId)
  return _internal_testid();
}
inline void TestReq::set_testid(::uint32_t value) {
  _internal_set_testid(value);
  _impl_._has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_set:sample.TestReq.TestId)
}
inline ::uint32_t TestReq::_internal_testid() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.testid_;
}
inline void TestReq::_internal_set_testid(::uint32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.testid_ = value;
}

// -------------------------------------------------------------------

// TestResult

// optional uint32 TestId = 1;
inline bool TestResult::has_testid() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline void TestResult::clear_testid() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.testid_ = 0u;
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline ::uint32_t TestResult::testid() const {
  // @@protoc_insertion_point(field_get:sample.TestResult.TestId)
  return _internal_testid();
}
inline void TestResult::set_testid(::uint32_t value) {
  _internal_set_testid(value);
  _impl_._has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_set:sample.TestResult.TestId)
}
inline ::uint32_t TestResult::_internal_testid() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.testid_;
}
inline void TestResult::_internal_set_testid(::uint32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.testid_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace sample


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_testPacket_2eproto_2epb_2eh
