// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: OpenEmail.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "OpenEmail.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_OpenEmail_2eproto() {
  delete OpenEmailRequest::default_instance_;
  delete OpenEmailResponse::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_OpenEmail_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_OpenEmail_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  OpenEmailRequest::default_instance_ = new OpenEmailRequest();
  OpenEmailResponse::default_instance_ = new OpenEmailResponse();
  OpenEmailRequest::default_instance_->InitAsDefaultInstance();
  OpenEmailResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_OpenEmail_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_OpenEmail_2eproto_once_);
void protobuf_AddDesc_OpenEmail_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_OpenEmail_2eproto_once_,
                 &protobuf_AddDesc_OpenEmail_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_OpenEmail_2eproto {
  StaticDescriptorInitializer_OpenEmail_2eproto() {
    protobuf_AddDesc_OpenEmail_2eproto();
  }
} static_descriptor_initializer_OpenEmail_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
const int OpenEmailRequest::kEmailIDFieldNumber;
#endif  // !_MSC_VER

OpenEmailRequest::OpenEmailRequest()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void OpenEmailRequest::InitAsDefaultInstance() {
}

OpenEmailRequest::OpenEmailRequest(const OpenEmailRequest& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void OpenEmailRequest::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

OpenEmailRequest::~OpenEmailRequest() {
  SharedDtor();
}

void OpenEmailRequest::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void OpenEmailRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const OpenEmailRequest& OpenEmailRequest::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_OpenEmail_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_OpenEmail_2eproto();
#endif
  return *default_instance_;
}

OpenEmailRequest* OpenEmailRequest::default_instance_ = NULL;

OpenEmailRequest* OpenEmailRequest::New() const {
  return new OpenEmailRequest;
}

void OpenEmailRequest::Clear() {
  email_id_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool OpenEmailRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint64 email_ID = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_email_ID:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 1, 8, input, this->mutable_email_id())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, this->mutable_email_id())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(8)) goto parse_email_ID;
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

void OpenEmailRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated uint64 email_ID = 1;
  for (int i = 0; i < this->email_id_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(
      1, this->email_id(i), output);
  }

}

int OpenEmailRequest::ByteSize() const {
  int total_size = 0;

  // repeated uint64 email_ID = 1;
  {
    int data_size = 0;
    for (int i = 0; i < this->email_id_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt64Size(this->email_id(i));
    }
    total_size += 1 * this->email_id_size() + data_size;
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void OpenEmailRequest::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const OpenEmailRequest*>(&from));
}

void OpenEmailRequest::MergeFrom(const OpenEmailRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
  email_id_.MergeFrom(from.email_id_);
}

void OpenEmailRequest::CopyFrom(const OpenEmailRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool OpenEmailRequest::IsInitialized() const {

  return true;
}

void OpenEmailRequest::Swap(OpenEmailRequest* other) {
  if (other != this) {
    email_id_.Swap(&other->email_id_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string OpenEmailRequest::GetTypeName() const {
  return "message.OpenEmailRequest";
}


// ===================================================================

bool OpenEmailResponse_OpenEmailState_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const OpenEmailResponse_OpenEmailState OpenEmailResponse::Succeed;
const OpenEmailResponse_OpenEmailState OpenEmailResponse::Failed;
const OpenEmailResponse_OpenEmailState OpenEmailResponse::OpenEmailState_MIN;
const OpenEmailResponse_OpenEmailState OpenEmailResponse::OpenEmailState_MAX;
const int OpenEmailResponse::OpenEmailState_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int OpenEmailResponse::kGoldFieldNumber;
const int OpenEmailResponse::kStateFieldNumber;
#endif  // !_MSC_VER

OpenEmailResponse::OpenEmailResponse()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void OpenEmailResponse::InitAsDefaultInstance() {
}

OpenEmailResponse::OpenEmailResponse(const OpenEmailResponse& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void OpenEmailResponse::SharedCtor() {
  _cached_size_ = 0;
  gold_ = 0;
  state_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

OpenEmailResponse::~OpenEmailResponse() {
  SharedDtor();
}

void OpenEmailResponse::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void OpenEmailResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const OpenEmailResponse& OpenEmailResponse::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_OpenEmail_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_OpenEmail_2eproto();
#endif
  return *default_instance_;
}

OpenEmailResponse* OpenEmailResponse::default_instance_ = NULL;

OpenEmailResponse* OpenEmailResponse::New() const {
  return new OpenEmailResponse;
}

void OpenEmailResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    gold_ = 0;
    state_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool OpenEmailResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 gold = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &gold_)));
          set_has_gold();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_state;
        break;
      }

      // required .message.OpenEmailResponse.OpenEmailState state = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_state:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::message::OpenEmailResponse_OpenEmailState_IsValid(value)) {
            set_state(static_cast< ::message::OpenEmailResponse_OpenEmailState >(value));
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

void OpenEmailResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 gold = 1;
  if (has_gold()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->gold(), output);
  }

  // required .message.OpenEmailResponse.OpenEmailState state = 2;
  if (has_state()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->state(), output);
  }

}

int OpenEmailResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 gold = 1;
    if (has_gold()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->gold());
    }

    // required .message.OpenEmailResponse.OpenEmailState state = 2;
    if (has_state()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->state());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void OpenEmailResponse::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const OpenEmailResponse*>(&from));
}

void OpenEmailResponse::MergeFrom(const OpenEmailResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_gold()) {
      set_gold(from.gold());
    }
    if (from.has_state()) {
      set_state(from.state());
    }
  }
}

void OpenEmailResponse::CopyFrom(const OpenEmailResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool OpenEmailResponse::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000002) != 0x00000002) return false;

  return true;
}

void OpenEmailResponse::Swap(OpenEmailResponse* other) {
  if (other != this) {
    std::swap(gold_, other->gold_);
    std::swap(state_, other->state_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string OpenEmailResponse::GetTypeName() const {
  return "message.OpenEmailResponse";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)
