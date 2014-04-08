// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UseBuff.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "UseBuff.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_UseBuff_2eproto() {
  delete UseBuffRequest::default_instance_;
  delete UseBuffResponse::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_UseBuff_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_UseBuff_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ::message::protobuf_AddDesc_PropInfo_2eproto();
  UseBuffRequest::default_instance_ = new UseBuffRequest();
  UseBuffResponse::default_instance_ = new UseBuffResponse();
  UseBuffRequest::default_instance_->InitAsDefaultInstance();
  UseBuffResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_UseBuff_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_UseBuff_2eproto_once_);
void protobuf_AddDesc_UseBuff_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_UseBuff_2eproto_once_,
                 &protobuf_AddDesc_UseBuff_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_UseBuff_2eproto {
  StaticDescriptorInitializer_UseBuff_2eproto() {
    protobuf_AddDesc_UseBuff_2eproto();
  }
} static_descriptor_initializer_UseBuff_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
const int UseBuffRequest::kDidFieldNumber;
const int UseBuffRequest::kTargetUidFieldNumber;
const int UseBuffRequest::kPropIdFieldNumber;
#endif  // !_MSC_VER

UseBuffRequest::UseBuffRequest()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void UseBuffRequest::InitAsDefaultInstance() {
}

UseBuffRequest::UseBuffRequest(const UseBuffRequest& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void UseBuffRequest::SharedCtor() {
  _cached_size_ = 0;
  did_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  targetuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  propid_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

UseBuffRequest::~UseBuffRequest() {
  SharedDtor();
}

void UseBuffRequest::SharedDtor() {
  if (did_ != &::google::protobuf::internal::kEmptyString) {
    delete did_;
  }
  if (targetuid_ != &::google::protobuf::internal::kEmptyString) {
    delete targetuid_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void UseBuffRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const UseBuffRequest& UseBuffRequest::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_UseBuff_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_UseBuff_2eproto();
#endif
  return *default_instance_;
}

UseBuffRequest* UseBuffRequest::default_instance_ = NULL;

UseBuffRequest* UseBuffRequest::New() const {
  return new UseBuffRequest;
}

void UseBuffRequest::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_did()) {
      if (did_ != &::google::protobuf::internal::kEmptyString) {
        did_->clear();
      }
    }
    if (has_targetuid()) {
      if (targetuid_ != &::google::protobuf::internal::kEmptyString) {
        targetuid_->clear();
      }
    }
    propid_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool UseBuffRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string did = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_did()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_targetUid;
        break;
      }

      // required string targetUid = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_targetUid:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_targetuid()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_propId;
        break;
      }

      // required uint32 propId = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_propId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &propid_)));
          set_has_propid();
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

void UseBuffRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string did = 1;
  if (has_did()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->did(), output);
  }

  // required string targetUid = 2;
  if (has_targetuid()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->targetuid(), output);
  }

  // required uint32 propId = 3;
  if (has_propid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->propid(), output);
  }

}

int UseBuffRequest::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string did = 1;
    if (has_did()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->did());
    }

    // required string targetUid = 2;
    if (has_targetuid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->targetuid());
    }

    // required uint32 propId = 3;
    if (has_propid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->propid());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void UseBuffRequest::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const UseBuffRequest*>(&from));
}

void UseBuffRequest::MergeFrom(const UseBuffRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_did()) {
      set_did(from.did());
    }
    if (from.has_targetuid()) {
      set_targetuid(from.targetuid());
    }
    if (from.has_propid()) {
      set_propid(from.propid());
    }
  }
}

void UseBuffRequest::CopyFrom(const UseBuffRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UseBuffRequest::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void UseBuffRequest::Swap(UseBuffRequest* other) {
  if (other != this) {
    std::swap(did_, other->did_);
    std::swap(targetuid_, other->targetuid_);
    std::swap(propid_, other->propid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string UseBuffRequest::GetTypeName() const {
  return "message.UseBuffRequest";
}


// ===================================================================

bool UseBuffResponse_UseStatus_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const UseBuffResponse_UseStatus UseBuffResponse::SUCCESS;
const UseBuffResponse_UseStatus UseBuffResponse::FAIL;
const UseBuffResponse_UseStatus UseBuffResponse::UseStatus_MIN;
const UseBuffResponse_UseStatus UseBuffResponse::UseStatus_MAX;
const int UseBuffResponse::UseStatus_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int UseBuffResponse::kStatusFieldNumber;
#endif  // !_MSC_VER

UseBuffResponse::UseBuffResponse()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void UseBuffResponse::InitAsDefaultInstance() {
}

UseBuffResponse::UseBuffResponse(const UseBuffResponse& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void UseBuffResponse::SharedCtor() {
  _cached_size_ = 0;
  status_ = 1;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

UseBuffResponse::~UseBuffResponse() {
  SharedDtor();
}

void UseBuffResponse::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void UseBuffResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const UseBuffResponse& UseBuffResponse::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_UseBuff_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_UseBuff_2eproto();
#endif
  return *default_instance_;
}

UseBuffResponse* UseBuffResponse::default_instance_ = NULL;

UseBuffResponse* UseBuffResponse::New() const {
  return new UseBuffResponse;
}

void UseBuffResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    status_ = 1;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool UseBuffResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .message.UseBuffResponse.UseStatus status = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::message::UseBuffResponse_UseStatus_IsValid(value)) {
            set_status(static_cast< ::message::UseBuffResponse_UseStatus >(value));
          }
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

void UseBuffResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .message.UseBuffResponse.UseStatus status = 1;
  if (has_status()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->status(), output);
  }

}

int UseBuffResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .message.UseBuffResponse.UseStatus status = 1;
    if (has_status()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->status());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void UseBuffResponse::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const UseBuffResponse*>(&from));
}

void UseBuffResponse::MergeFrom(const UseBuffResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_status()) {
      set_status(from.status());
    }
  }
}

void UseBuffResponse::CopyFrom(const UseBuffResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UseBuffResponse::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void UseBuffResponse::Swap(UseBuffResponse* other) {
  if (other != this) {
    std::swap(status_, other->status_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string UseBuffResponse::GetTypeName() const {
  return "message.UseBuffResponse";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)
