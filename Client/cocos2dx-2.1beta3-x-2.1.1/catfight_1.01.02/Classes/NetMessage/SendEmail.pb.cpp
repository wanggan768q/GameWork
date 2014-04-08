// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SendEmail.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "SendEmail.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_SendEmail_2eproto() {
  delete SendEmailRequest::default_instance_;
  delete SendEmailResponse::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_SendEmail_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_SendEmail_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  SendEmailRequest::default_instance_ = new SendEmailRequest();
  SendEmailResponse::default_instance_ = new SendEmailResponse();
  SendEmailRequest::default_instance_->InitAsDefaultInstance();
  SendEmailResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_SendEmail_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_SendEmail_2eproto_once_);
void protobuf_AddDesc_SendEmail_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_SendEmail_2eproto_once_,
                 &protobuf_AddDesc_SendEmail_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_SendEmail_2eproto {
  StaticDescriptorInitializer_SendEmail_2eproto() {
    protobuf_AddDesc_SendEmail_2eproto();
  }
} static_descriptor_initializer_SendEmail_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
const int SendEmailRequest::kGameUUIDFieldNumber;
#endif  // !_MSC_VER

SendEmailRequest::SendEmailRequest()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void SendEmailRequest::InitAsDefaultInstance() {
}

SendEmailRequest::SendEmailRequest(const SendEmailRequest& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void SendEmailRequest::SharedCtor() {
  _cached_size_ = 0;
  game_uuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SendEmailRequest::~SendEmailRequest() {
  SharedDtor();
}

void SendEmailRequest::SharedDtor() {
  if (game_uuid_ != &::google::protobuf::internal::kEmptyString) {
    delete game_uuid_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void SendEmailRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const SendEmailRequest& SendEmailRequest::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_SendEmail_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_SendEmail_2eproto();
#endif
  return *default_instance_;
}

SendEmailRequest* SendEmailRequest::default_instance_ = NULL;

SendEmailRequest* SendEmailRequest::New() const {
  return new SendEmailRequest;
}

void SendEmailRequest::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_game_uuid()) {
      if (game_uuid_ != &::google::protobuf::internal::kEmptyString) {
        game_uuid_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool SendEmailRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string game_UUID = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_game_uuid()));
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

void SendEmailRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string game_UUID = 1;
  if (has_game_uuid()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->game_uuid(), output);
  }

}

int SendEmailRequest::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string game_UUID = 1;
    if (has_game_uuid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->game_uuid());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SendEmailRequest::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const SendEmailRequest*>(&from));
}

void SendEmailRequest::MergeFrom(const SendEmailRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_game_uuid()) {
      set_game_uuid(from.game_uuid());
    }
  }
}

void SendEmailRequest::CopyFrom(const SendEmailRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SendEmailRequest::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void SendEmailRequest::Swap(SendEmailRequest* other) {
  if (other != this) {
    std::swap(game_uuid_, other->game_uuid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string SendEmailRequest::GetTypeName() const {
  return "message.SendEmailRequest";
}


// ===================================================================

bool SendEmailResponse_SendEmailStatus_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const SendEmailResponse_SendEmailStatus SendEmailResponse::Success;
const SendEmailResponse_SendEmailStatus SendEmailResponse::Fail;
const SendEmailResponse_SendEmailStatus SendEmailResponse::SendEmailStatus_MIN;
const SendEmailResponse_SendEmailStatus SendEmailResponse::SendEmailStatus_MAX;
const int SendEmailResponse::SendEmailStatus_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int SendEmailResponse::kStatusFieldNumber;
#endif  // !_MSC_VER

SendEmailResponse::SendEmailResponse()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void SendEmailResponse::InitAsDefaultInstance() {
}

SendEmailResponse::SendEmailResponse(const SendEmailResponse& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void SendEmailResponse::SharedCtor() {
  _cached_size_ = 0;
  status_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SendEmailResponse::~SendEmailResponse() {
  SharedDtor();
}

void SendEmailResponse::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void SendEmailResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const SendEmailResponse& SendEmailResponse::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_SendEmail_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_SendEmail_2eproto();
#endif
  return *default_instance_;
}

SendEmailResponse* SendEmailResponse::default_instance_ = NULL;

SendEmailResponse* SendEmailResponse::New() const {
  return new SendEmailResponse;
}

void SendEmailResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    status_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool SendEmailResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .message.SendEmailResponse.SendEmailStatus status = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::message::SendEmailResponse_SendEmailStatus_IsValid(value)) {
            set_status(static_cast< ::message::SendEmailResponse_SendEmailStatus >(value));
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

void SendEmailResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .message.SendEmailResponse.SendEmailStatus status = 1;
  if (has_status()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->status(), output);
  }

}

int SendEmailResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .message.SendEmailResponse.SendEmailStatus status = 1;
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

void SendEmailResponse::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const SendEmailResponse*>(&from));
}

void SendEmailResponse::MergeFrom(const SendEmailResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_status()) {
      set_status(from.status());
    }
  }
}

void SendEmailResponse::CopyFrom(const SendEmailResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SendEmailResponse::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void SendEmailResponse::Swap(SendEmailResponse* other) {
  if (other != this) {
    std::swap(status_, other->status_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string SendEmailResponse::GetTypeName() const {
  return "message.SendEmailResponse";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)