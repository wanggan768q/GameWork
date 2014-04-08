// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Address.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Address.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_Address_2eproto() {
  delete NetAddress::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_Address_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_Address_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  NetAddress::default_instance_ = new NetAddress();
  NetAddress::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Address_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_Address_2eproto_once_);
void protobuf_AddDesc_Address_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_Address_2eproto_once_,
                 &protobuf_AddDesc_Address_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Address_2eproto {
  StaticDescriptorInitializer_Address_2eproto() {
    protobuf_AddDesc_Address_2eproto();
  }
} static_descriptor_initializer_Address_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
const int NetAddress::kIpFieldNumber;
const int NetAddress::kPortFieldNumber;
#endif  // !_MSC_VER

NetAddress::NetAddress()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void NetAddress::InitAsDefaultInstance() {
}

NetAddress::NetAddress(const NetAddress& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void NetAddress::SharedCtor() {
  _cached_size_ = 0;
  ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  port_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

NetAddress::~NetAddress() {
  SharedDtor();
}

void NetAddress::SharedDtor() {
  if (ip_ != &::google::protobuf::internal::kEmptyString) {
    delete ip_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void NetAddress::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const NetAddress& NetAddress::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_Address_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_Address_2eproto();
#endif
  return *default_instance_;
}

NetAddress* NetAddress::default_instance_ = NULL;

NetAddress* NetAddress::New() const {
  return new NetAddress;
}

void NetAddress::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_ip()) {
      if (ip_ != &::google::protobuf::internal::kEmptyString) {
        ip_->clear();
      }
    }
    port_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool NetAddress::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string ip = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_ip()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_port;
        break;
      }

      // optional uint32 port = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_port:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &port_)));
          set_has_port();
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

void NetAddress::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string ip = 1;
  if (has_ip()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->ip(), output);
  }

  // optional uint32 port = 2;
  if (has_port()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->port(), output);
  }

}

int NetAddress::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string ip = 1;
    if (has_ip()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->ip());
    }

    // optional uint32 port = 2;
    if (has_port()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->port());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void NetAddress::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const NetAddress*>(&from));
}

void NetAddress::MergeFrom(const NetAddress& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ip()) {
      set_ip(from.ip());
    }
    if (from.has_port()) {
      set_port(from.port());
    }
  }
}

void NetAddress::CopyFrom(const NetAddress& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NetAddress::IsInitialized() const {

  return true;
}

void NetAddress::Swap(NetAddress* other) {
  if (other != this) {
    std::swap(ip_, other->ip_);
    std::swap(port_, other->port_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string NetAddress::GetTypeName() const {
  return "message.NetAddress";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)