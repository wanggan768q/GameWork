// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UseBuff.proto

#ifndef PROTOBUF_UseBuff_2eproto__INCLUDED
#define PROTOBUF_UseBuff_2eproto__INCLUDED

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
#include "PropInfo.pb.h"
// @@protoc_insertion_point(includes)

namespace message {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_UseBuff_2eproto();
void protobuf_AssignDesc_UseBuff_2eproto();
void protobuf_ShutdownFile_UseBuff_2eproto();

class UseBuffRequest;
class UseBuffResponse;

enum UseBuffResponse_UseStatus {
  UseBuffResponse_UseStatus_SUCCESS = 1,
  UseBuffResponse_UseStatus_FAIL = 0,
  UseBuffResponse_UseStatus_NOMONEY = 2
};
bool UseBuffResponse_UseStatus_IsValid(int value);
const UseBuffResponse_UseStatus UseBuffResponse_UseStatus_UseStatus_MIN = UseBuffResponse_UseStatus_FAIL;
const UseBuffResponse_UseStatus UseBuffResponse_UseStatus_UseStatus_MAX = UseBuffResponse_UseStatus_NOMONEY;
const int UseBuffResponse_UseStatus_UseStatus_ARRAYSIZE = UseBuffResponse_UseStatus_UseStatus_MAX + 1;

// ===================================================================

class UseBuffRequest : public ::google::protobuf::MessageLite {
 public:
  UseBuffRequest();
  virtual ~UseBuffRequest();

  UseBuffRequest(const UseBuffRequest& from);

  inline UseBuffRequest& operator=(const UseBuffRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const UseBuffRequest& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const UseBuffRequest* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(UseBuffRequest* other);

  // implements Message ----------------------------------------------

  UseBuffRequest* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const UseBuffRequest& from);
  void MergeFrom(const UseBuffRequest& from);
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

  // required string did = 1;
  inline bool has_did() const;
  inline void clear_did();
  static const int kDidFieldNumber = 1;
  inline const ::std::string& did() const;
  inline void set_did(const ::std::string& value);
  inline void set_did(const char* value);
  inline void set_did(const char* value, size_t size);
  inline ::std::string* mutable_did();
  inline ::std::string* release_did();
  inline void set_allocated_did(::std::string* did);

  // required string targetUid = 2;
  inline bool has_targetuid() const;
  inline void clear_targetuid();
  static const int kTargetUidFieldNumber = 2;
  inline const ::std::string& targetuid() const;
  inline void set_targetuid(const ::std::string& value);
  inline void set_targetuid(const char* value);
  inline void set_targetuid(const char* value, size_t size);
  inline ::std::string* mutable_targetuid();
  inline ::std::string* release_targetuid();
  inline void set_allocated_targetuid(::std::string* targetuid);

  // required uint32 propId = 3;
  inline bool has_propid() const;
  inline void clear_propid();
  static const int kPropIdFieldNumber = 3;
  inline ::google::protobuf::uint32 propid() const;
  inline void set_propid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:message.UseBuffRequest)
 private:
  inline void set_has_did();
  inline void clear_has_did();
  inline void set_has_targetuid();
  inline void clear_has_targetuid();
  inline void set_has_propid();
  inline void clear_has_propid();

  ::std::string* did_;
  ::std::string* targetuid_;
  ::google::protobuf::uint32 propid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_UseBuff_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_UseBuff_2eproto();
  #endif
  friend void protobuf_AssignDesc_UseBuff_2eproto();
  friend void protobuf_ShutdownFile_UseBuff_2eproto();

  void InitAsDefaultInstance();
  static UseBuffRequest* default_instance_;
};
// -------------------------------------------------------------------

class UseBuffResponse : public ::google::protobuf::MessageLite {
 public:
  UseBuffResponse();
  virtual ~UseBuffResponse();

  UseBuffResponse(const UseBuffResponse& from);

  inline UseBuffResponse& operator=(const UseBuffResponse& from) {
    CopyFrom(from);
    return *this;
  }

  static const UseBuffResponse& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const UseBuffResponse* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(UseBuffResponse* other);

  // implements Message ----------------------------------------------

  UseBuffResponse* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const UseBuffResponse& from);
  void MergeFrom(const UseBuffResponse& from);
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

  typedef UseBuffResponse_UseStatus UseStatus;
  static const UseStatus SUCCESS = UseBuffResponse_UseStatus_SUCCESS;
  static const UseStatus FAIL = UseBuffResponse_UseStatus_FAIL;
  static const UseStatus NOMONEY = UseBuffResponse_UseStatus_NOMONEY;
  static inline bool UseStatus_IsValid(int value) {
    return UseBuffResponse_UseStatus_IsValid(value);
  }
  static const UseStatus UseStatus_MIN =
    UseBuffResponse_UseStatus_UseStatus_MIN;
  static const UseStatus UseStatus_MAX =
    UseBuffResponse_UseStatus_UseStatus_MAX;
  static const int UseStatus_ARRAYSIZE =
    UseBuffResponse_UseStatus_UseStatus_ARRAYSIZE;

  // accessors -------------------------------------------------------

  // required .message.UseBuffResponse.UseStatus status = 1;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 1;
  inline ::message::UseBuffResponse_UseStatus status() const;
  inline void set_status(::message::UseBuffResponse_UseStatus value);

  // @@protoc_insertion_point(class_scope:message.UseBuffResponse)
 private:
  inline void set_has_status();
  inline void clear_has_status();

  int status_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_UseBuff_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_UseBuff_2eproto();
  #endif
  friend void protobuf_AssignDesc_UseBuff_2eproto();
  friend void protobuf_ShutdownFile_UseBuff_2eproto();

  void InitAsDefaultInstance();
  static UseBuffResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// UseBuffRequest

// required string did = 1;
inline bool UseBuffRequest::has_did() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UseBuffRequest::set_has_did() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UseBuffRequest::clear_has_did() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UseBuffRequest::clear_did() {
  if (did_ != &::google::protobuf::internal::kEmptyString) {
    did_->clear();
  }
  clear_has_did();
}
inline const ::std::string& UseBuffRequest::did() const {
  return *did_;
}
inline void UseBuffRequest::set_did(const ::std::string& value) {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  did_->assign(value);
}
inline void UseBuffRequest::set_did(const char* value) {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  did_->assign(value);
}
inline void UseBuffRequest::set_did(const char* value, size_t size) {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  did_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* UseBuffRequest::mutable_did() {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  return did_;
}
inline ::std::string* UseBuffRequest::release_did() {
  clear_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = did_;
    did_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void UseBuffRequest::set_allocated_did(::std::string* did) {
  if (did_ != &::google::protobuf::internal::kEmptyString) {
    delete did_;
  }
  if (did) {
    set_has_did();
    did_ = did;
  } else {
    clear_has_did();
    did_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string targetUid = 2;
inline bool UseBuffRequest::has_targetuid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UseBuffRequest::set_has_targetuid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UseBuffRequest::clear_has_targetuid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UseBuffRequest::clear_targetuid() {
  if (targetuid_ != &::google::protobuf::internal::kEmptyString) {
    targetuid_->clear();
  }
  clear_has_targetuid();
}
inline const ::std::string& UseBuffRequest::targetuid() const {
  return *targetuid_;
}
inline void UseBuffRequest::set_targetuid(const ::std::string& value) {
  set_has_targetuid();
  if (targetuid_ == &::google::protobuf::internal::kEmptyString) {
    targetuid_ = new ::std::string;
  }
  targetuid_->assign(value);
}
inline void UseBuffRequest::set_targetuid(const char* value) {
  set_has_targetuid();
  if (targetuid_ == &::google::protobuf::internal::kEmptyString) {
    targetuid_ = new ::std::string;
  }
  targetuid_->assign(value);
}
inline void UseBuffRequest::set_targetuid(const char* value, size_t size) {
  set_has_targetuid();
  if (targetuid_ == &::google::protobuf::internal::kEmptyString) {
    targetuid_ = new ::std::string;
  }
  targetuid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* UseBuffRequest::mutable_targetuid() {
  set_has_targetuid();
  if (targetuid_ == &::google::protobuf::internal::kEmptyString) {
    targetuid_ = new ::std::string;
  }
  return targetuid_;
}
inline ::std::string* UseBuffRequest::release_targetuid() {
  clear_has_targetuid();
  if (targetuid_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = targetuid_;
    targetuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void UseBuffRequest::set_allocated_targetuid(::std::string* targetuid) {
  if (targetuid_ != &::google::protobuf::internal::kEmptyString) {
    delete targetuid_;
  }
  if (targetuid) {
    set_has_targetuid();
    targetuid_ = targetuid;
  } else {
    clear_has_targetuid();
    targetuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required uint32 propId = 3;
inline bool UseBuffRequest::has_propid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UseBuffRequest::set_has_propid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UseBuffRequest::clear_has_propid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UseBuffRequest::clear_propid() {
  propid_ = 0u;
  clear_has_propid();
}
inline ::google::protobuf::uint32 UseBuffRequest::propid() const {
  return propid_;
}
inline void UseBuffRequest::set_propid(::google::protobuf::uint32 value) {
  set_has_propid();
  propid_ = value;
}

// -------------------------------------------------------------------

// UseBuffResponse

// required .message.UseBuffResponse.UseStatus status = 1;
inline bool UseBuffResponse::has_status() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UseBuffResponse::set_has_status() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UseBuffResponse::clear_has_status() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UseBuffResponse::clear_status() {
  status_ = 1;
  clear_has_status();
}
inline ::message::UseBuffResponse_UseStatus UseBuffResponse::status() const {
  return static_cast< ::message::UseBuffResponse_UseStatus >(status_);
}
inline void UseBuffResponse::set_status(::message::UseBuffResponse_UseStatus value) {
  assert(::message::UseBuffResponse_UseStatus_IsValid(value));
  set_has_status();
  status_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UseBuff_2eproto__INCLUDED
