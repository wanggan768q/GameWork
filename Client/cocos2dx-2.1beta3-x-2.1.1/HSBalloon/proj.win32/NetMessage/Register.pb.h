// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Register.proto

#ifndef PROTOBUF_Register_2eproto__INCLUDED
#define PROTOBUF_Register_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
// @@protoc_insertion_point(includes)

namespace message {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Register_2eproto();
void protobuf_AssignDesc_Register_2eproto();
void protobuf_ShutdownFile_Register_2eproto();

class RegisterRequest;
class RegisterResponse;

enum RegisterResponse_RegisterStatus {
  RegisterResponse_RegisterStatus_RegisterStatus_OK = 1,
  RegisterResponse_RegisterStatus_RegisterStatus_FAIL = 0
};
bool RegisterResponse_RegisterStatus_IsValid(int value);
const RegisterResponse_RegisterStatus RegisterResponse_RegisterStatus_RegisterStatus_MIN = RegisterResponse_RegisterStatus_RegisterStatus_FAIL;
const RegisterResponse_RegisterStatus RegisterResponse_RegisterStatus_RegisterStatus_MAX = RegisterResponse_RegisterStatus_RegisterStatus_OK;
const int RegisterResponse_RegisterStatus_RegisterStatus_ARRAYSIZE = RegisterResponse_RegisterStatus_RegisterStatus_MAX + 1;

// ===================================================================

class RegisterRequest : public ::google::protobuf::MessageLite {
 public:
  RegisterRequest();
  virtual ~RegisterRequest();
  
  RegisterRequest(const RegisterRequest& from);
  
  inline RegisterRequest& operator=(const RegisterRequest& from) {
    CopyFrom(from);
    return *this;
  }
  
  static const RegisterRequest& default_instance();
  
  void Swap(RegisterRequest* other);
  
  // implements Message ----------------------------------------------
  
  RegisterRequest* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const RegisterRequest& from);
  void MergeFrom(const RegisterRequest& from);
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
  
  // required string userName = 1;
  inline bool has_username() const;
  inline void clear_username();
  static const int kUserNameFieldNumber = 1;
  inline const ::std::string& username() const;
  inline void set_username(const ::std::string& value);
  inline void set_username(const char* value);
  inline void set_username(const char* value, size_t size);
  inline ::std::string* mutable_username();
  inline ::std::string* release_username();
  
  // optional int32 chID = 2;
  inline bool has_chid() const;
  inline void clear_chid();
  static const int kChIDFieldNumber = 2;
  inline ::google::protobuf::int32 chid() const;
  inline void set_chid(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:message.RegisterRequest)
 private:
  inline void set_has_username();
  inline void clear_has_username();
  inline void set_has_chid();
  inline void clear_has_chid();
  
  ::std::string* username_;
  ::google::protobuf::int32 chid_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_Register_2eproto();
  friend void protobuf_AssignDesc_Register_2eproto();
  friend void protobuf_ShutdownFile_Register_2eproto();
  
  void InitAsDefaultInstance();
  static RegisterRequest* default_instance_;
};
// -------------------------------------------------------------------

class RegisterResponse : public ::google::protobuf::MessageLite {
 public:
  RegisterResponse();
  virtual ~RegisterResponse();
  
  RegisterResponse(const RegisterResponse& from);
  
  inline RegisterResponse& operator=(const RegisterResponse& from) {
    CopyFrom(from);
    return *this;
  }
  
  static const RegisterResponse& default_instance();
  
  void Swap(RegisterResponse* other);
  
  // implements Message ----------------------------------------------
  
  RegisterResponse* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const RegisterResponse& from);
  void MergeFrom(const RegisterResponse& from);
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
  
  typedef RegisterResponse_RegisterStatus RegisterStatus;
  static const RegisterStatus RegisterStatus_OK = RegisterResponse_RegisterStatus_RegisterStatus_OK;
  static const RegisterStatus RegisterStatus_FAIL = RegisterResponse_RegisterStatus_RegisterStatus_FAIL;
  static inline bool RegisterStatus_IsValid(int value) {
    return RegisterResponse_RegisterStatus_IsValid(value);
  }
  static const RegisterStatus RegisterStatus_MIN =
    RegisterResponse_RegisterStatus_RegisterStatus_MIN;
  static const RegisterStatus RegisterStatus_MAX =
    RegisterResponse_RegisterStatus_RegisterStatus_MAX;
  static const int RegisterStatus_ARRAYSIZE =
    RegisterResponse_RegisterStatus_RegisterStatus_ARRAYSIZE;
  
  // accessors -------------------------------------------------------
  
  // required .message.RegisterResponse.RegisterStatus status = 1;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 1;
  inline ::message::RegisterResponse_RegisterStatus status() const;
  inline void set_status(::message::RegisterResponse_RegisterStatus value);
  
  // optional string uid = 2;
  inline bool has_uid() const;
  inline void clear_uid();
  static const int kUidFieldNumber = 2;
  inline const ::std::string& uid() const;
  inline void set_uid(const ::std::string& value);
  inline void set_uid(const char* value);
  inline void set_uid(const char* value, size_t size);
  inline ::std::string* mutable_uid();
  inline ::std::string* release_uid();
  
  // optional string userName = 3;
  inline bool has_username() const;
  inline void clear_username();
  static const int kUserNameFieldNumber = 3;
  inline const ::std::string& username() const;
  inline void set_username(const ::std::string& value);
  inline void set_username(const char* value);
  inline void set_username(const char* value, size_t size);
  inline ::std::string* mutable_username();
  inline ::std::string* release_username();
  
  // @@protoc_insertion_point(class_scope:message.RegisterResponse)
 private:
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_uid();
  inline void clear_has_uid();
  inline void set_has_username();
  inline void clear_has_username();
  
  ::std::string* uid_;
  ::std::string* username_;
  int status_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_Register_2eproto();
  friend void protobuf_AssignDesc_Register_2eproto();
  friend void protobuf_ShutdownFile_Register_2eproto();
  
  void InitAsDefaultInstance();
  static RegisterResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// RegisterRequest

// required string userName = 1;
inline bool RegisterRequest::has_username() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RegisterRequest::set_has_username() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RegisterRequest::clear_has_username() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RegisterRequest::clear_username() {
  if (username_ != &::google::protobuf::internal::kEmptyString) {
    username_->clear();
  }
  clear_has_username();
}
inline const ::std::string& RegisterRequest::username() const {
  return *username_;
}
inline void RegisterRequest::set_username(const ::std::string& value) {
  set_has_username();
  if (username_ == &::google::protobuf::internal::kEmptyString) {
    username_ = new ::std::string;
  }
  username_->assign(value);
}
inline void RegisterRequest::set_username(const char* value) {
  set_has_username();
  if (username_ == &::google::protobuf::internal::kEmptyString) {
    username_ = new ::std::string;
  }
  username_->assign(value);
}
inline void RegisterRequest::set_username(const char* value, size_t size) {
  set_has_username();
  if (username_ == &::google::protobuf::internal::kEmptyString) {
    username_ = new ::std::string;
  }
  username_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RegisterRequest::mutable_username() {
  set_has_username();
  if (username_ == &::google::protobuf::internal::kEmptyString) {
    username_ = new ::std::string;
  }
  return username_;
}
inline ::std::string* RegisterRequest::release_username() {
  clear_has_username();
  if (username_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = username_;
    username_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional int32 chID = 2;
inline bool RegisterRequest::has_chid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RegisterRequest::set_has_chid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RegisterRequest::clear_has_chid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RegisterRequest::clear_chid() {
  chid_ = 0;
  clear_has_chid();
}
inline ::google::protobuf::int32 RegisterRequest::chid() const {
  return chid_;
}
inline void RegisterRequest::set_chid(::google::protobuf::int32 value) {
  set_has_chid();
  chid_ = value;
}

// -------------------------------------------------------------------

// RegisterResponse

// required .message.RegisterResponse.RegisterStatus status = 1;
inline bool RegisterResponse::has_status() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RegisterResponse::set_has_status() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RegisterResponse::clear_has_status() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RegisterResponse::clear_status() {
  status_ = 1;
  clear_has_status();
}
inline ::message::RegisterResponse_RegisterStatus RegisterResponse::status() const {
  return static_cast< ::message::RegisterResponse_RegisterStatus >(status_);
}
inline void RegisterResponse::set_status(::message::RegisterResponse_RegisterStatus value) {
  GOOGLE_DCHECK(::message::RegisterResponse_RegisterStatus_IsValid(value));
  set_has_status();
  status_ = value;
}

// optional string uid = 2;
inline bool RegisterResponse::has_uid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RegisterResponse::set_has_uid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RegisterResponse::clear_has_uid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RegisterResponse::clear_uid() {
  if (uid_ != &::google::protobuf::internal::kEmptyString) {
    uid_->clear();
  }
  clear_has_uid();
}
inline const ::std::string& RegisterResponse::uid() const {
  return *uid_;
}
inline void RegisterResponse::set_uid(const ::std::string& value) {
  set_has_uid();
  if (uid_ == &::google::protobuf::internal::kEmptyString) {
    uid_ = new ::std::string;
  }
  uid_->assign(value);
}
inline void RegisterResponse::set_uid(const char* value) {
  set_has_uid();
  if (uid_ == &::google::protobuf::internal::kEmptyString) {
    uid_ = new ::std::string;
  }
  uid_->assign(value);
}
inline void RegisterResponse::set_uid(const char* value, size_t size) {
  set_has_uid();
  if (uid_ == &::google::protobuf::internal::kEmptyString) {
    uid_ = new ::std::string;
  }
  uid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RegisterResponse::mutable_uid() {
  set_has_uid();
  if (uid_ == &::google::protobuf::internal::kEmptyString) {
    uid_ = new ::std::string;
  }
  return uid_;
}
inline ::std::string* RegisterResponse::release_uid() {
  clear_has_uid();
  if (uid_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = uid_;
    uid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string userName = 3;
inline bool RegisterResponse::has_username() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RegisterResponse::set_has_username() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RegisterResponse::clear_has_username() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void RegisterResponse::clear_username() {
  if (username_ != &::google::protobuf::internal::kEmptyString) {
    username_->clear();
  }
  clear_has_username();
}
inline const ::std::string& RegisterResponse::username() const {
  return *username_;
}
inline void RegisterResponse::set_username(const ::std::string& value) {
  set_has_username();
  if (username_ == &::google::protobuf::internal::kEmptyString) {
    username_ = new ::std::string;
  }
  username_->assign(value);
}
inline void RegisterResponse::set_username(const char* value) {
  set_has_username();
  if (username_ == &::google::protobuf::internal::kEmptyString) {
    username_ = new ::std::string;
  }
  username_->assign(value);
}
inline void RegisterResponse::set_username(const char* value, size_t size) {
  set_has_username();
  if (username_ == &::google::protobuf::internal::kEmptyString) {
    username_ = new ::std::string;
  }
  username_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RegisterResponse::mutable_username() {
  set_has_username();
  if (username_ == &::google::protobuf::internal::kEmptyString) {
    username_ = new ::std::string;
  }
  return username_;
}
inline ::std::string* RegisterResponse::release_username() {
  clear_has_username();
  if (username_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = username_;
    username_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Register_2eproto__INCLUDED