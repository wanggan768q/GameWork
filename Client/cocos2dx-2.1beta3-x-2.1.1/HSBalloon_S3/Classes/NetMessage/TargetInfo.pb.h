// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TargetInfo.proto

#ifndef PROTOBUF_TargetInfo_2eproto__INCLUDED
#define PROTOBUF_TargetInfo_2eproto__INCLUDED

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
#include "UserInfo.pb.h"
// @@protoc_insertion_point(includes)

namespace message {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_TargetInfo_2eproto();
void protobuf_AssignDesc_TargetInfo_2eproto();
void protobuf_ShutdownFile_TargetInfo_2eproto();

class TargetInfoRequest;
class TargetInfoResponse;

enum TargetInfoResponse_FindStatus {
  TargetInfoResponse_FindStatus_SUCCESS = 1,
  TargetInfoResponse_FindStatus_FAIL = 0,
  TargetInfoResponse_FindStatus_NOMONEY = 2
};
bool TargetInfoResponse_FindStatus_IsValid(int value);
const TargetInfoResponse_FindStatus TargetInfoResponse_FindStatus_FindStatus_MIN = TargetInfoResponse_FindStatus_FAIL;
const TargetInfoResponse_FindStatus TargetInfoResponse_FindStatus_FindStatus_MAX = TargetInfoResponse_FindStatus_NOMONEY;
const int TargetInfoResponse_FindStatus_FindStatus_ARRAYSIZE = TargetInfoResponse_FindStatus_FindStatus_MAX + 1;

// ===================================================================

class TargetInfoRequest : public ::google::protobuf::MessageLite {
 public:
  TargetInfoRequest();
  virtual ~TargetInfoRequest();

  TargetInfoRequest(const TargetInfoRequest& from);

  inline TargetInfoRequest& operator=(const TargetInfoRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const TargetInfoRequest& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const TargetInfoRequest* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(TargetInfoRequest* other);

  // implements Message ----------------------------------------------

  TargetInfoRequest* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const TargetInfoRequest& from);
  void MergeFrom(const TargetInfoRequest& from);
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

  // optional uint32 roomId = 1;
  inline bool has_roomid() const;
  inline void clear_roomid();
  static const int kRoomIdFieldNumber = 1;
  inline ::google::protobuf::uint32 roomid() const;
  inline void set_roomid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:message.TargetInfoRequest)
 private:
  inline void set_has_roomid();
  inline void clear_has_roomid();

  ::google::protobuf::uint32 roomid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_TargetInfo_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_TargetInfo_2eproto();
  #endif
  friend void protobuf_AssignDesc_TargetInfo_2eproto();
  friend void protobuf_ShutdownFile_TargetInfo_2eproto();

  void InitAsDefaultInstance();
  static TargetInfoRequest* default_instance_;
};
// -------------------------------------------------------------------

class TargetInfoResponse : public ::google::protobuf::MessageLite {
 public:
  TargetInfoResponse();
  virtual ~TargetInfoResponse();

  TargetInfoResponse(const TargetInfoResponse& from);

  inline TargetInfoResponse& operator=(const TargetInfoResponse& from) {
    CopyFrom(from);
    return *this;
  }

  static const TargetInfoResponse& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const TargetInfoResponse* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(TargetInfoResponse* other);

  // implements Message ----------------------------------------------

  TargetInfoResponse* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const TargetInfoResponse& from);
  void MergeFrom(const TargetInfoResponse& from);
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

  typedef TargetInfoResponse_FindStatus FindStatus;
  static const FindStatus SUCCESS = TargetInfoResponse_FindStatus_SUCCESS;
  static const FindStatus FAIL = TargetInfoResponse_FindStatus_FAIL;
  static const FindStatus NOMONEY = TargetInfoResponse_FindStatus_NOMONEY;
  static inline bool FindStatus_IsValid(int value) {
    return TargetInfoResponse_FindStatus_IsValid(value);
  }
  static const FindStatus FindStatus_MIN =
    TargetInfoResponse_FindStatus_FindStatus_MIN;
  static const FindStatus FindStatus_MAX =
    TargetInfoResponse_FindStatus_FindStatus_MAX;
  static const int FindStatus_ARRAYSIZE =
    TargetInfoResponse_FindStatus_FindStatus_ARRAYSIZE;

  // accessors -------------------------------------------------------

  // required .message.TargetInfoResponse.FindStatus status = 1;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 1;
  inline ::message::TargetInfoResponse_FindStatus status() const;
  inline void set_status(::message::TargetInfoResponse_FindStatus value);

  // optional string dungoenId = 2;
  inline bool has_dungoenid() const;
  inline void clear_dungoenid();
  static const int kDungoenIdFieldNumber = 2;
  inline const ::std::string& dungoenid() const;
  inline void set_dungoenid(const ::std::string& value);
  inline void set_dungoenid(const char* value);
  inline void set_dungoenid(const char* value, size_t size);
  inline ::std::string* mutable_dungoenid();
  inline ::std::string* release_dungoenid();
  inline void set_allocated_dungoenid(::std::string* dungoenid);

  // optional .message.UserBasicInfo self = 3;
  inline bool has_self() const;
  inline void clear_self();
  static const int kSelfFieldNumber = 3;
  inline const ::message::UserBasicInfo& self() const;
  inline ::message::UserBasicInfo* mutable_self();
  inline ::message::UserBasicInfo* release_self();
  inline void set_allocated_self(::message::UserBasicInfo* self);

  // optional .message.UserBasicInfo target = 4;
  inline bool has_target() const;
  inline void clear_target();
  static const int kTargetFieldNumber = 4;
  inline const ::message::UserBasicInfo& target() const;
  inline ::message::UserBasicInfo* mutable_target();
  inline ::message::UserBasicInfo* release_target();
  inline void set_allocated_target(::message::UserBasicInfo* target);

  // @@protoc_insertion_point(class_scope:message.TargetInfoResponse)
 private:
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_dungoenid();
  inline void clear_has_dungoenid();
  inline void set_has_self();
  inline void clear_has_self();
  inline void set_has_target();
  inline void clear_has_target();

  ::std::string* dungoenid_;
  ::message::UserBasicInfo* self_;
  ::message::UserBasicInfo* target_;
  int status_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_TargetInfo_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_TargetInfo_2eproto();
  #endif
  friend void protobuf_AssignDesc_TargetInfo_2eproto();
  friend void protobuf_ShutdownFile_TargetInfo_2eproto();

  void InitAsDefaultInstance();
  static TargetInfoResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// TargetInfoRequest

// optional uint32 roomId = 1;
inline bool TargetInfoRequest::has_roomid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TargetInfoRequest::set_has_roomid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TargetInfoRequest::clear_has_roomid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TargetInfoRequest::clear_roomid() {
  roomid_ = 0u;
  clear_has_roomid();
}
inline ::google::protobuf::uint32 TargetInfoRequest::roomid() const {
  return roomid_;
}
inline void TargetInfoRequest::set_roomid(::google::protobuf::uint32 value) {
  set_has_roomid();
  roomid_ = value;
}

// -------------------------------------------------------------------

// TargetInfoResponse

// required .message.TargetInfoResponse.FindStatus status = 1;
inline bool TargetInfoResponse::has_status() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TargetInfoResponse::set_has_status() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TargetInfoResponse::clear_has_status() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TargetInfoResponse::clear_status() {
  status_ = 1;
  clear_has_status();
}
inline ::message::TargetInfoResponse_FindStatus TargetInfoResponse::status() const {
  return static_cast< ::message::TargetInfoResponse_FindStatus >(status_);
}
inline void TargetInfoResponse::set_status(::message::TargetInfoResponse_FindStatus value) {
  assert(::message::TargetInfoResponse_FindStatus_IsValid(value));
  set_has_status();
  status_ = value;
}

// optional string dungoenId = 2;
inline bool TargetInfoResponse::has_dungoenid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TargetInfoResponse::set_has_dungoenid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TargetInfoResponse::clear_has_dungoenid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TargetInfoResponse::clear_dungoenid() {
  if (dungoenid_ != &::google::protobuf::internal::kEmptyString) {
    dungoenid_->clear();
  }
  clear_has_dungoenid();
}
inline const ::std::string& TargetInfoResponse::dungoenid() const {
  return *dungoenid_;
}
inline void TargetInfoResponse::set_dungoenid(const ::std::string& value) {
  set_has_dungoenid();
  if (dungoenid_ == &::google::protobuf::internal::kEmptyString) {
    dungoenid_ = new ::std::string;
  }
  dungoenid_->assign(value);
}
inline void TargetInfoResponse::set_dungoenid(const char* value) {
  set_has_dungoenid();
  if (dungoenid_ == &::google::protobuf::internal::kEmptyString) {
    dungoenid_ = new ::std::string;
  }
  dungoenid_->assign(value);
}
inline void TargetInfoResponse::set_dungoenid(const char* value, size_t size) {
  set_has_dungoenid();
  if (dungoenid_ == &::google::protobuf::internal::kEmptyString) {
    dungoenid_ = new ::std::string;
  }
  dungoenid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TargetInfoResponse::mutable_dungoenid() {
  set_has_dungoenid();
  if (dungoenid_ == &::google::protobuf::internal::kEmptyString) {
    dungoenid_ = new ::std::string;
  }
  return dungoenid_;
}
inline ::std::string* TargetInfoResponse::release_dungoenid() {
  clear_has_dungoenid();
  if (dungoenid_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = dungoenid_;
    dungoenid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TargetInfoResponse::set_allocated_dungoenid(::std::string* dungoenid) {
  if (dungoenid_ != &::google::protobuf::internal::kEmptyString) {
    delete dungoenid_;
  }
  if (dungoenid) {
    set_has_dungoenid();
    dungoenid_ = dungoenid;
  } else {
    clear_has_dungoenid();
    dungoenid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional .message.UserBasicInfo self = 3;
inline bool TargetInfoResponse::has_self() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TargetInfoResponse::set_has_self() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TargetInfoResponse::clear_has_self() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TargetInfoResponse::clear_self() {
  if (self_ != NULL) self_->::message::UserBasicInfo::Clear();
  clear_has_self();
}
inline const ::message::UserBasicInfo& TargetInfoResponse::self() const {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  return self_ != NULL ? *self_ : *default_instance().self_;
#else
  return self_ != NULL ? *self_ : *default_instance_->self_;
#endif
}
inline ::message::UserBasicInfo* TargetInfoResponse::mutable_self() {
  set_has_self();
  if (self_ == NULL) self_ = new ::message::UserBasicInfo;
  return self_;
}
inline ::message::UserBasicInfo* TargetInfoResponse::release_self() {
  clear_has_self();
  ::message::UserBasicInfo* temp = self_;
  self_ = NULL;
  return temp;
}
inline void TargetInfoResponse::set_allocated_self(::message::UserBasicInfo* self) {
  delete self_;
  self_ = self;
  if (self) {
    set_has_self();
  } else {
    clear_has_self();
  }
}

// optional .message.UserBasicInfo target = 4;
inline bool TargetInfoResponse::has_target() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TargetInfoResponse::set_has_target() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TargetInfoResponse::clear_has_target() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TargetInfoResponse::clear_target() {
  if (target_ != NULL) target_->::message::UserBasicInfo::Clear();
  clear_has_target();
}
inline const ::message::UserBasicInfo& TargetInfoResponse::target() const {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  return target_ != NULL ? *target_ : *default_instance().target_;
#else
  return target_ != NULL ? *target_ : *default_instance_->target_;
#endif
}
inline ::message::UserBasicInfo* TargetInfoResponse::mutable_target() {
  set_has_target();
  if (target_ == NULL) target_ = new ::message::UserBasicInfo;
  return target_;
}
inline ::message::UserBasicInfo* TargetInfoResponse::release_target() {
  clear_has_target();
  ::message::UserBasicInfo* temp = target_;
  target_ = NULL;
  return temp;
}
inline void TargetInfoResponse::set_allocated_target(::message::UserBasicInfo* target) {
  delete target_;
  target_ = target;
  if (target) {
    set_has_target();
  } else {
    clear_has_target();
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_TargetInfo_2eproto__INCLUDED
