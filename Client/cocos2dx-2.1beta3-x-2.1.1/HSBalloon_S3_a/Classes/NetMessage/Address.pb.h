// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Address.proto

#ifndef PROTOBUF_Address_2eproto__INCLUDED
#define PROTOBUF_Address_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
// @@protoc_insertion_point(includes)

namespace message {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Address_2eproto();
void protobuf_AssignDesc_Address_2eproto();
void protobuf_ShutdownFile_Address_2eproto();

class NetAddress;

// ===================================================================

class NetAddress : public ::google::protobuf::MessageLite {
 public:
  NetAddress();
  virtual ~NetAddress();

  NetAddress(const NetAddress& from);

  inline NetAddress& operator=(const NetAddress& from) {
    CopyFrom(from);
    return *this;
  }

  static const NetAddress& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const NetAddress* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(NetAddress* other);

  // implements Message ----------------------------------------------

  NetAddress* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const NetAddress& from);
  void MergeFrom(const NetAddress& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::std::string GetTypeName() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string ip = 1;
  inline bool has_ip() const;
  inline void clear_ip();
  static const int kIpFieldNumber = 1;
  inline const ::std::string& ip() const;
  inline void set_ip(const ::std::string& value);
  inline void set_ip(const char* value);
  inline void set_ip(const char* value, size_t size);
  inline ::std::string* mutable_ip();
  inline ::std::string* release_ip();
  inline void set_allocated_ip(::std::string* ip);

  // optional uint32 port = 2;
  inline bool has_port() const;
  inline void clear_port();
  static const int kPortFieldNumber = 2;
  inline ::google::protobuf::uint32 port() const;
  inline void set_port(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:message.NetAddress)
 private:
  inline void set_has_ip();
  inline void clear_has_ip();
  inline void set_has_port();
  inline void clear_has_port();

  ::std::string* ip_;
  ::google::protobuf::uint32 port_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_Address_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_Address_2eproto();
  #endif
  friend void protobuf_AssignDesc_Address_2eproto();
  friend void protobuf_ShutdownFile_Address_2eproto();

  void InitAsDefaultInstance();
  static NetAddress* default_instance_;
};
// ===================================================================


// ===================================================================

// NetAddress

// optional string ip = 1;
inline bool NetAddress::has_ip() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void NetAddress::set_has_ip() {
  _has_bits_[0] |= 0x00000001u;
}
inline void NetAddress::clear_has_ip() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void NetAddress::clear_ip() {
  if (ip_ != &::google::protobuf::internal::kEmptyString) {
    ip_->clear();
  }
  clear_has_ip();
}
inline const ::std::string& NetAddress::ip() const {
  return *ip_;
}
inline void NetAddress::set_ip(const ::std::string& value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void NetAddress::set_ip(const char* value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
}
inline void NetAddress::set_ip(const char* value, size_t size) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  ip_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* NetAddress::mutable_ip() {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    ip_ = new ::std::string;
  }
  return ip_;
}
inline ::std::string* NetAddress::release_ip() {
  clear_has_ip();
  if (ip_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = ip_;
    ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void NetAddress::set_allocated_ip(::std::string* ip) {
  if (ip_ != &::google::protobuf::internal::kEmptyString) {
    delete ip_;
  }
  if (ip) {
    set_has_ip();
    ip_ = ip;
  } else {
    clear_has_ip();
    ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional uint32 port = 2;
inline bool NetAddress::has_port() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void NetAddress::set_has_port() {
  _has_bits_[0] |= 0x00000002u;
}
inline void NetAddress::clear_has_port() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void NetAddress::clear_port() {
  port_ = 0u;
  clear_has_port();
}
inline ::google::protobuf::uint32 NetAddress::port() const {
  return port_;
}
inline void NetAddress::set_port(::google::protobuf::uint32 value) {
  set_has_port();
  port_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Address_2eproto__INCLUDED
