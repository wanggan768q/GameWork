// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: StartBattle.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "StartBattle.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_StartBattle_2eproto() {
  delete NotifyStartBattle::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_StartBattle_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_StartBattle_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  NotifyStartBattle::default_instance_ = new NotifyStartBattle();
  NotifyStartBattle::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_StartBattle_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_StartBattle_2eproto_once_);
void protobuf_AddDesc_StartBattle_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_StartBattle_2eproto_once_,
                 &protobuf_AddDesc_StartBattle_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_StartBattle_2eproto {
  StaticDescriptorInitializer_StartBattle_2eproto() {
    protobuf_AddDesc_StartBattle_2eproto();
  }
} static_descriptor_initializer_StartBattle_2eproto_;
#endif

// ===================================================================

bool NotifyStartBattle_NotifyType_IsValid(int value) {
  switch(value) {
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const NotifyStartBattle_NotifyType NotifyStartBattle::START;
const NotifyStartBattle_NotifyType NotifyStartBattle::NotifyType_MIN;
const NotifyStartBattle_NotifyType NotifyStartBattle::NotifyType_MAX;
const int NotifyStartBattle::NotifyType_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int NotifyStartBattle::kTypeFieldNumber;
#endif  // !_MSC_VER

NotifyStartBattle::NotifyStartBattle()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void NotifyStartBattle::InitAsDefaultInstance() {
}

NotifyStartBattle::NotifyStartBattle(const NotifyStartBattle& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void NotifyStartBattle::SharedCtor() {
  _cached_size_ = 0;
  type_ = 1;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

NotifyStartBattle::~NotifyStartBattle() {
  SharedDtor();
}

void NotifyStartBattle::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void NotifyStartBattle::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const NotifyStartBattle& NotifyStartBattle::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_StartBattle_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_StartBattle_2eproto();
#endif
  return *default_instance_;
}

NotifyStartBattle* NotifyStartBattle::default_instance_ = NULL;

NotifyStartBattle* NotifyStartBattle::New() const {
  return new NotifyStartBattle;
}

void NotifyStartBattle::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    type_ = 1;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool NotifyStartBattle::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .message.NotifyStartBattle.NotifyType type = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::message::NotifyStartBattle_NotifyType_IsValid(value)) {
            set_type(static_cast< ::message::NotifyStartBattle_NotifyType >(value));
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

void NotifyStartBattle::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .message.NotifyStartBattle.NotifyType type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->type(), output);
  }

}

int NotifyStartBattle::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .message.NotifyStartBattle.NotifyType type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void NotifyStartBattle::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const NotifyStartBattle*>(&from));
}

void NotifyStartBattle::MergeFrom(const NotifyStartBattle& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_type()) {
      set_type(from.type());
    }
  }
}

void NotifyStartBattle::CopyFrom(const NotifyStartBattle& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NotifyStartBattle::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void NotifyStartBattle::Swap(NotifyStartBattle* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string NotifyStartBattle::GetTypeName() const {
  return "message.NotifyStartBattle";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)