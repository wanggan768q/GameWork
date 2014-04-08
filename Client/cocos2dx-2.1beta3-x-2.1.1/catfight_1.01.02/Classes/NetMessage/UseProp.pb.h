// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UseProp.proto

#ifndef PROTOBUF_UseProp_2eproto__INCLUDED
#define PROTOBUF_UseProp_2eproto__INCLUDED

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
void  protobuf_AddDesc_UseProp_2eproto();
void protobuf_AssignDesc_UseProp_2eproto();
void protobuf_ShutdownFile_UseProp_2eproto();

class UsePropRequest;
class UsePropResponse;

enum UsePropRequest_OperateType {
  UsePropRequest_OperateType_Type_use = 1,
  UsePropRequest_OperateType_Type_unlock = 2
};
bool UsePropRequest_OperateType_IsValid(int value);
const UsePropRequest_OperateType UsePropRequest_OperateType_OperateType_MIN = UsePropRequest_OperateType_Type_use;
const UsePropRequest_OperateType UsePropRequest_OperateType_OperateType_MAX = UsePropRequest_OperateType_Type_unlock;
const int UsePropRequest_OperateType_OperateType_ARRAYSIZE = UsePropRequest_OperateType_OperateType_MAX + 1;

enum UsePropResponse_State {
  UsePropResponse_State_State_Succeed = 0,
  UsePropResponse_State_State_Fail = 1,
  UsePropResponse_State_State_NOMONEY = 2
};
bool UsePropResponse_State_IsValid(int value);
const UsePropResponse_State UsePropResponse_State_State_MIN = UsePropResponse_State_State_Succeed;
const UsePropResponse_State UsePropResponse_State_State_MAX = UsePropResponse_State_State_NOMONEY;
const int UsePropResponse_State_State_ARRAYSIZE = UsePropResponse_State_State_MAX + 1;

// ===================================================================

class UsePropRequest : public ::google::protobuf::MessageLite {
 public:
  UsePropRequest();
  virtual ~UsePropRequest();

  UsePropRequest(const UsePropRequest& from);

  inline UsePropRequest& operator=(const UsePropRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const UsePropRequest& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const UsePropRequest* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(UsePropRequest* other);

  // implements Message ----------------------------------------------

  UsePropRequest* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const UsePropRequest& from);
  void MergeFrom(const UsePropRequest& from);
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

  typedef UsePropRequest_OperateType OperateType;
  static const OperateType Type_use = UsePropRequest_OperateType_Type_use;
  static const OperateType Type_unlock = UsePropRequest_OperateType_Type_unlock;
  static inline bool OperateType_IsValid(int value) {
    return UsePropRequest_OperateType_IsValid(value);
  }
  static const OperateType OperateType_MIN =
    UsePropRequest_OperateType_OperateType_MIN;
  static const OperateType OperateType_MAX =
    UsePropRequest_OperateType_OperateType_MAX;
  static const int OperateType_ARRAYSIZE =
    UsePropRequest_OperateType_OperateType_ARRAYSIZE;

  // accessors -------------------------------------------------------

  // optional string did = 1;
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

  // required .message.UsePropRequest.OperateType type = 2;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 2;
  inline ::message::UsePropRequest_OperateType type() const;
  inline void set_type(::message::UsePropRequest_OperateType value);

  // required uint32 usePropID = 3;
  inline bool has_usepropid() const;
  inline void clear_usepropid();
  static const int kUsePropIDFieldNumber = 3;
  inline ::google::protobuf::uint32 usepropid() const;
  inline void set_usepropid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:message.UsePropRequest)
 private:
  inline void set_has_did();
  inline void clear_has_did();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_usepropid();
  inline void clear_has_usepropid();

  ::std::string* did_;
  int type_;
  ::google::protobuf::uint32 usepropid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_UseProp_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_UseProp_2eproto();
  #endif
  friend void protobuf_AssignDesc_UseProp_2eproto();
  friend void protobuf_ShutdownFile_UseProp_2eproto();

  void InitAsDefaultInstance();
  static UsePropRequest* default_instance_;
};
// -------------------------------------------------------------------

class UsePropResponse : public ::google::protobuf::MessageLite {
 public:
  UsePropResponse();
  virtual ~UsePropResponse();

  UsePropResponse(const UsePropResponse& from);

  inline UsePropResponse& operator=(const UsePropResponse& from) {
    CopyFrom(from);
    return *this;
  }

  static const UsePropResponse& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const UsePropResponse* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(UsePropResponse* other);

  // implements Message ----------------------------------------------

  UsePropResponse* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const UsePropResponse& from);
  void MergeFrom(const UsePropResponse& from);
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

  typedef UsePropResponse_State State;
  static const State State_Succeed = UsePropResponse_State_State_Succeed;
  static const State State_Fail = UsePropResponse_State_State_Fail;
  static const State State_NOMONEY = UsePropResponse_State_State_NOMONEY;
  static inline bool State_IsValid(int value) {
    return UsePropResponse_State_IsValid(value);
  }
  static const State State_MIN =
    UsePropResponse_State_State_MIN;
  static const State State_MAX =
    UsePropResponse_State_State_MAX;
  static const int State_ARRAYSIZE =
    UsePropResponse_State_State_ARRAYSIZE;

  // accessors -------------------------------------------------------

  // required .message.UsePropResponse.State state = 1;
  inline bool has_state() const;
  inline void clear_state();
  static const int kStateFieldNumber = 1;
  inline ::message::UsePropResponse_State state() const;
  inline void set_state(::message::UsePropResponse_State value);

  // optional uint32 golds = 2;
  inline bool has_golds() const;
  inline void clear_golds();
  static const int kGoldsFieldNumber = 2;
  inline ::google::protobuf::uint32 golds() const;
  inline void set_golds(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:message.UsePropResponse)
 private:
  inline void set_has_state();
  inline void clear_has_state();
  inline void set_has_golds();
  inline void clear_has_golds();

  int state_;
  ::google::protobuf::uint32 golds_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_UseProp_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_UseProp_2eproto();
  #endif
  friend void protobuf_AssignDesc_UseProp_2eproto();
  friend void protobuf_ShutdownFile_UseProp_2eproto();

  void InitAsDefaultInstance();
  static UsePropResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// UsePropRequest

// optional string did = 1;
inline bool UsePropRequest::has_did() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UsePropRequest::set_has_did() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UsePropRequest::clear_has_did() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UsePropRequest::clear_did() {
  if (did_ != &::google::protobuf::internal::kEmptyString) {
    did_->clear();
  }
  clear_has_did();
}
inline const ::std::string& UsePropRequest::did() const {
  return *did_;
}
inline void UsePropRequest::set_did(const ::std::string& value) {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  did_->assign(value);
}
inline void UsePropRequest::set_did(const char* value) {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  did_->assign(value);
}
inline void UsePropRequest::set_did(const char* value, size_t size) {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  did_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* UsePropRequest::mutable_did() {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  return did_;
}
inline ::std::string* UsePropRequest::release_did() {
  clear_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = did_;
    did_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void UsePropRequest::set_allocated_did(::std::string* did) {
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

// required .message.UsePropRequest.OperateType type = 2;
inline bool UsePropRequest::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UsePropRequest::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UsePropRequest::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UsePropRequest::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::message::UsePropRequest_OperateType UsePropRequest::type() const {
  return static_cast< ::message::UsePropRequest_OperateType >(type_);
}
inline void UsePropRequest::set_type(::message::UsePropRequest_OperateType value) {
  assert(::message::UsePropRequest_OperateType_IsValid(value));
  set_has_type();
  type_ = value;
}

// required uint32 usePropID = 3;
inline bool UsePropRequest::has_usepropid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UsePropRequest::set_has_usepropid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UsePropRequest::clear_has_usepropid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UsePropRequest::clear_usepropid() {
  usepropid_ = 0u;
  clear_has_usepropid();
}
inline ::google::protobuf::uint32 UsePropRequest::usepropid() const {
  return usepropid_;
}
inline void UsePropRequest::set_usepropid(::google::protobuf::uint32 value) {
  set_has_usepropid();
  usepropid_ = value;
}

// -------------------------------------------------------------------

// UsePropResponse

// required .message.UsePropResponse.State state = 1;
inline bool UsePropResponse::has_state() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UsePropResponse::set_has_state() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UsePropResponse::clear_has_state() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UsePropResponse::clear_state() {
  state_ = 0;
  clear_has_state();
}
inline ::message::UsePropResponse_State UsePropResponse::state() const {
  return static_cast< ::message::UsePropResponse_State >(state_);
}
inline void UsePropResponse::set_state(::message::UsePropResponse_State value) {
  assert(::message::UsePropResponse_State_IsValid(value));
  set_has_state();
  state_ = value;
}

// optional uint32 golds = 2;
inline bool UsePropResponse::has_golds() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UsePropResponse::set_has_golds() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UsePropResponse::clear_has_golds() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UsePropResponse::clear_golds() {
  golds_ = 0u;
  clear_has_golds();
}
inline ::google::protobuf::uint32 UsePropResponse::golds() const {
  return golds_;
}
inline void UsePropResponse::set_golds(::google::protobuf::uint32 value) {
  set_has_golds();
  golds_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UseProp_2eproto__INCLUDED
