// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Email.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Email.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_Email_2eproto() {
  delete EmailRequest::default_instance_;
  delete EmailResponse::default_instance_;
  delete EmailResponse_EmailInfo::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_Email_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_Email_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  EmailRequest::default_instance_ = new EmailRequest();
  EmailResponse::default_instance_ = new EmailResponse();
  EmailResponse_EmailInfo::default_instance_ = new EmailResponse_EmailInfo();
  EmailRequest::default_instance_->InitAsDefaultInstance();
  EmailResponse::default_instance_->InitAsDefaultInstance();
  EmailResponse_EmailInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Email_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_Email_2eproto_once_);
void protobuf_AddDesc_Email_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_Email_2eproto_once_,
                 &protobuf_AddDesc_Email_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Email_2eproto {
  StaticDescriptorInitializer_Email_2eproto() {
    protobuf_AddDesc_Email_2eproto();
  }
} static_descriptor_initializer_Email_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

EmailRequest::EmailRequest()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void EmailRequest::InitAsDefaultInstance() {
}

EmailRequest::EmailRequest(const EmailRequest& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void EmailRequest::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

EmailRequest::~EmailRequest() {
  SharedDtor();
}

void EmailRequest::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void EmailRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const EmailRequest& EmailRequest::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_Email_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_Email_2eproto();
#endif
  return *default_instance_;
}

EmailRequest* EmailRequest::default_instance_ = NULL;

EmailRequest* EmailRequest::New() const {
  return new EmailRequest;
}

void EmailRequest::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool EmailRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      return true;
    }
    DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
  }
  return true;
#undef DO_
}

void EmailRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
}

int EmailRequest::ByteSize() const {
  int total_size = 0;

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void EmailRequest::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const EmailRequest*>(&from));
}

void EmailRequest::MergeFrom(const EmailRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
}

void EmailRequest::CopyFrom(const EmailRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EmailRequest::IsInitialized() const {

  return true;
}

void EmailRequest::Swap(EmailRequest* other) {
  if (other != this) {
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string EmailRequest::GetTypeName() const {
  return "message.EmailRequest";
}


// ===================================================================

#ifndef _MSC_VER
const int EmailResponse_EmailInfo::kEmailIDFieldNumber;
const int EmailResponse_EmailInfo::kGivePalyerNameFieldNumber;
#endif  // !_MSC_VER

EmailResponse_EmailInfo::EmailResponse_EmailInfo()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void EmailResponse_EmailInfo::InitAsDefaultInstance() {
}

EmailResponse_EmailInfo::EmailResponse_EmailInfo(const EmailResponse_EmailInfo& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void EmailResponse_EmailInfo::SharedCtor() {
  _cached_size_ = 0;
  email_id_ = GOOGLE_ULONGLONG(0);
  givepalyername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

EmailResponse_EmailInfo::~EmailResponse_EmailInfo() {
  SharedDtor();
}

void EmailResponse_EmailInfo::SharedDtor() {
  if (givepalyername_ != &::google::protobuf::internal::kEmptyString) {
    delete givepalyername_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void EmailResponse_EmailInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const EmailResponse_EmailInfo& EmailResponse_EmailInfo::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_Email_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_Email_2eproto();
#endif
  return *default_instance_;
}

EmailResponse_EmailInfo* EmailResponse_EmailInfo::default_instance_ = NULL;

EmailResponse_EmailInfo* EmailResponse_EmailInfo::New() const {
  return new EmailResponse_EmailInfo;
}

void EmailResponse_EmailInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    email_id_ = GOOGLE_ULONGLONG(0);
    if (has_givepalyername()) {
      if (givepalyername_ != &::google::protobuf::internal::kEmptyString) {
        givepalyername_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool EmailResponse_EmailInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint64 email_ID = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &email_id_)));
          set_has_email_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_givePalyerName;
        break;
      }

      // required string givePalyerName = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_givePalyerName:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_givepalyername()));
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

void EmailResponse_EmailInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint64 email_ID = 1;
  if (has_email_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(1, this->email_id(), output);
  }

  // required string givePalyerName = 2;
  if (has_givepalyername()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->givepalyername(), output);
  }

}

int EmailResponse_EmailInfo::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint64 email_ID = 1;
    if (has_email_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->email_id());
    }

    // required string givePalyerName = 2;
    if (has_givepalyername()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->givepalyername());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void EmailResponse_EmailInfo::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const EmailResponse_EmailInfo*>(&from));
}

void EmailResponse_EmailInfo::MergeFrom(const EmailResponse_EmailInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_email_id()) {
      set_email_id(from.email_id());
    }
    if (from.has_givepalyername()) {
      set_givepalyername(from.givepalyername());
    }
  }
}

void EmailResponse_EmailInfo::CopyFrom(const EmailResponse_EmailInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EmailResponse_EmailInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void EmailResponse_EmailInfo::Swap(EmailResponse_EmailInfo* other) {
  if (other != this) {
    std::swap(email_id_, other->email_id_);
    std::swap(givepalyername_, other->givepalyername_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string EmailResponse_EmailInfo::GetTypeName() const {
  return "message.EmailResponse.EmailInfo";
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int EmailResponse::kEmailListFieldNumber;
#endif  // !_MSC_VER

EmailResponse::EmailResponse()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void EmailResponse::InitAsDefaultInstance() {
}

EmailResponse::EmailResponse(const EmailResponse& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void EmailResponse::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

EmailResponse::~EmailResponse() {
  SharedDtor();
}

void EmailResponse::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void EmailResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const EmailResponse& EmailResponse::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_Email_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_Email_2eproto();
#endif
  return *default_instance_;
}

EmailResponse* EmailResponse::default_instance_ = NULL;

EmailResponse* EmailResponse::New() const {
  return new EmailResponse;
}

void EmailResponse::Clear() {
  emaillist_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool EmailResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .message.EmailResponse.EmailInfo emailList = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_emailList:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_emaillist()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_emailList;
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

void EmailResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .message.EmailResponse.EmailInfo emailList = 1;
  for (int i = 0; i < this->emaillist_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      1, this->emaillist(i), output);
  }

}

int EmailResponse::ByteSize() const {
  int total_size = 0;

  // repeated .message.EmailResponse.EmailInfo emailList = 1;
  total_size += 1 * this->emaillist_size();
  for (int i = 0; i < this->emaillist_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->emaillist(i));
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void EmailResponse::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const EmailResponse*>(&from));
}

void EmailResponse::MergeFrom(const EmailResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  emaillist_.MergeFrom(from.emaillist_);
}

void EmailResponse::CopyFrom(const EmailResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EmailResponse::IsInitialized() const {

  for (int i = 0; i < emaillist_size(); i++) {
    if (!this->emaillist(i).IsInitialized()) return false;
  }
  return true;
}

void EmailResponse::Swap(EmailResponse* other) {
  if (other != this) {
    emaillist_.Swap(&other->emaillist_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string EmailResponse::GetTypeName() const {
  return "message.EmailResponse";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)