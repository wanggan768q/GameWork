// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Recharge.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Recharge.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_Recharge_2eproto() {
  delete NotifyRecharge::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_Recharge_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_Recharge_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  NotifyRecharge::default_instance_ = new NotifyRecharge();
  NotifyRecharge::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Recharge_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_Recharge_2eproto_once_);
void protobuf_AddDesc_Recharge_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_Recharge_2eproto_once_,
                 &protobuf_AddDesc_Recharge_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Recharge_2eproto {
  StaticDescriptorInitializer_Recharge_2eproto() {
    protobuf_AddDesc_Recharge_2eproto();
  }
} static_descriptor_initializer_Recharge_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
const int NotifyRecharge::kTotalGoldsFieldNumber;
#endif  // !_MSC_VER

NotifyRecharge::NotifyRecharge()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void NotifyRecharge::InitAsDefaultInstance() {
}

NotifyRecharge::NotifyRecharge(const NotifyRecharge& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void NotifyRecharge::SharedCtor() {
  _cached_size_ = 0;
  totalgolds_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

NotifyRecharge::~NotifyRecharge() {
  SharedDtor();
}

void NotifyRecharge::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void NotifyRecharge::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const NotifyRecharge& NotifyRecharge::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_Recharge_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_Recharge_2eproto();
#endif
  return *default_instance_;
}

NotifyRecharge* NotifyRecharge::default_instance_ = NULL;

NotifyRecharge* NotifyRecharge::New() const {
  return new NotifyRecharge;
}

void NotifyRecharge::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    totalgolds_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool NotifyRecharge::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 totalGolds = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &totalgolds_)));
          set_has_totalgolds();
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

void NotifyRecharge::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 totalGolds = 1;
  if (has_totalgolds()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->totalgolds(), output);
  }

}

int NotifyRecharge::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 totalGolds = 1;
    if (has_totalgolds()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->totalgolds());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void NotifyRecharge::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const NotifyRecharge*>(&from));
}

void NotifyRecharge::MergeFrom(const NotifyRecharge& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_totalgolds()) {
      set_totalgolds(from.totalgolds());
    }
  }
}

void NotifyRecharge::CopyFrom(const NotifyRecharge& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NotifyRecharge::IsInitialized() const {

  return true;
}

void NotifyRecharge::Swap(NotifyRecharge* other) {
  if (other != this) {
    std::swap(totalgolds_, other->totalgolds_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string NotifyRecharge::GetTypeName() const {
  return "message.NotifyRecharge";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)
