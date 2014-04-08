// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ClaimedDailyReward.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ClaimedDailyReward.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_ClaimedDailyReward_2eproto() {
  delete ClaimedDailyRewardRequest::default_instance_;
  delete ClaimedDailyRewardResponse::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_ClaimedDailyReward_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_ClaimedDailyReward_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ClaimedDailyRewardRequest::default_instance_ = new ClaimedDailyRewardRequest();
  ClaimedDailyRewardResponse::default_instance_ = new ClaimedDailyRewardResponse();
  ClaimedDailyRewardRequest::default_instance_->InitAsDefaultInstance();
  ClaimedDailyRewardResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ClaimedDailyReward_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_ClaimedDailyReward_2eproto_once_);
void protobuf_AddDesc_ClaimedDailyReward_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_ClaimedDailyReward_2eproto_once_,
                 &protobuf_AddDesc_ClaimedDailyReward_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ClaimedDailyReward_2eproto {
  StaticDescriptorInitializer_ClaimedDailyReward_2eproto() {
    protobuf_AddDesc_ClaimedDailyReward_2eproto();
  }
} static_descriptor_initializer_ClaimedDailyReward_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
const int ClaimedDailyRewardRequest::kDayIDFieldNumber;
#endif  // !_MSC_VER

ClaimedDailyRewardRequest::ClaimedDailyRewardRequest()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void ClaimedDailyRewardRequest::InitAsDefaultInstance() {
}

ClaimedDailyRewardRequest::ClaimedDailyRewardRequest(const ClaimedDailyRewardRequest& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void ClaimedDailyRewardRequest::SharedCtor() {
  _cached_size_ = 0;
  dayid_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ClaimedDailyRewardRequest::~ClaimedDailyRewardRequest() {
  SharedDtor();
}

void ClaimedDailyRewardRequest::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void ClaimedDailyRewardRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ClaimedDailyRewardRequest& ClaimedDailyRewardRequest::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_ClaimedDailyReward_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_ClaimedDailyReward_2eproto();
#endif
  return *default_instance_;
}

ClaimedDailyRewardRequest* ClaimedDailyRewardRequest::default_instance_ = NULL;

ClaimedDailyRewardRequest* ClaimedDailyRewardRequest::New() const {
  return new ClaimedDailyRewardRequest;
}

void ClaimedDailyRewardRequest::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    dayid_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool ClaimedDailyRewardRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 dayID = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &dayid_)));
          set_has_dayid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ClaimedDailyRewardRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 dayID = 1;
  if (has_dayid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->dayid(), output);
  }

}

int ClaimedDailyRewardRequest::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 dayID = 1;
    if (has_dayid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->dayid());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ClaimedDailyRewardRequest::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const ClaimedDailyRewardRequest*>(&from));
}

void ClaimedDailyRewardRequest::MergeFrom(const ClaimedDailyRewardRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_dayid()) {
      set_dayid(from.dayid());
    }
  }
}

void ClaimedDailyRewardRequest::CopyFrom(const ClaimedDailyRewardRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ClaimedDailyRewardRequest::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void ClaimedDailyRewardRequest::Swap(ClaimedDailyRewardRequest* other) {
  if (other != this) {
    std::swap(dayid_, other->dayid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string ClaimedDailyRewardRequest::GetTypeName() const {
  return "message.ClaimedDailyRewardRequest";
}


// ===================================================================

#ifndef _MSC_VER
const int ClaimedDailyRewardResponse::kAddGoldNumberFieldNumber;
#endif  // !_MSC_VER

ClaimedDailyRewardResponse::ClaimedDailyRewardResponse()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void ClaimedDailyRewardResponse::InitAsDefaultInstance() {
}

ClaimedDailyRewardResponse::ClaimedDailyRewardResponse(const ClaimedDailyRewardResponse& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void ClaimedDailyRewardResponse::SharedCtor() {
  _cached_size_ = 0;
  addgoldnumber_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ClaimedDailyRewardResponse::~ClaimedDailyRewardResponse() {
  SharedDtor();
}

void ClaimedDailyRewardResponse::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void ClaimedDailyRewardResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ClaimedDailyRewardResponse& ClaimedDailyRewardResponse::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_ClaimedDailyReward_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_ClaimedDailyReward_2eproto();
#endif
  return *default_instance_;
}

ClaimedDailyRewardResponse* ClaimedDailyRewardResponse::default_instance_ = NULL;

ClaimedDailyRewardResponse* ClaimedDailyRewardResponse::New() const {
  return new ClaimedDailyRewardResponse;
}

void ClaimedDailyRewardResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    addgoldnumber_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool ClaimedDailyRewardResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 addGoldNumber = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &addgoldnumber_)));
          set_has_addgoldnumber();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ClaimedDailyRewardResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 addGoldNumber = 1;
  if (has_addgoldnumber()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->addgoldnumber(), output);
  }

}

int ClaimedDailyRewardResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 addGoldNumber = 1;
    if (has_addgoldnumber()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->addgoldnumber());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ClaimedDailyRewardResponse::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const ClaimedDailyRewardResponse*>(&from));
}

void ClaimedDailyRewardResponse::MergeFrom(const ClaimedDailyRewardResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_addgoldnumber()) {
      set_addgoldnumber(from.addgoldnumber());
    }
  }
}

void ClaimedDailyRewardResponse::CopyFrom(const ClaimedDailyRewardResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ClaimedDailyRewardResponse::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void ClaimedDailyRewardResponse::Swap(ClaimedDailyRewardResponse* other) {
  if (other != this) {
    std::swap(addgoldnumber_, other->addgoldnumber_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string ClaimedDailyRewardResponse::GetTypeName() const {
  return "message.ClaimedDailyRewardResponse";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)
