// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: RemoveFriend.proto

#ifndef PROTOBUF_RemoveFriend_2eproto__INCLUDED
#define PROTOBUF_RemoveFriend_2eproto__INCLUDED

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
void  protobuf_AddDesc_RemoveFriend_2eproto();
void protobuf_AssignDesc_RemoveFriend_2eproto();
void protobuf_ShutdownFile_RemoveFriend_2eproto();

class RemoveFriendRequest;
class RemoveFriendResponse;

enum RemoveFriendResponse_State {
  RemoveFriendResponse_State_State_Succeed = 1,
  RemoveFriendResponse_State_State_Fail = 0
};
bool RemoveFriendResponse_State_IsValid(int value);
const RemoveFriendResponse_State RemoveFriendResponse_State_State_MIN = RemoveFriendResponse_State_State_Fail;
const RemoveFriendResponse_State RemoveFriendResponse_State_State_MAX = RemoveFriendResponse_State_State_Succeed;
const int RemoveFriendResponse_State_State_ARRAYSIZE = RemoveFriendResponse_State_State_MAX + 1;

// ===================================================================

class RemoveFriendRequest : public ::google::protobuf::MessageLite {
 public:
  RemoveFriendRequest();
  virtual ~RemoveFriendRequest();

  RemoveFriendRequest(const RemoveFriendRequest& from);

  inline RemoveFriendRequest& operator=(const RemoveFriendRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const RemoveFriendRequest& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const RemoveFriendRequest* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(RemoveFriendRequest* other);

  // implements Message ----------------------------------------------

  RemoveFriendRequest* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const RemoveFriendRequest& from);
  void MergeFrom(const RemoveFriendRequest& from);
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

  // required string friendUUID = 1;
  inline bool has_frienduuid() const;
  inline void clear_frienduuid();
  static const int kFriendUUIDFieldNumber = 1;
  inline const ::std::string& frienduuid() const;
  inline void set_frienduuid(const ::std::string& value);
  inline void set_frienduuid(const char* value);
  inline void set_frienduuid(const char* value, size_t size);
  inline ::std::string* mutable_frienduuid();
  inline ::std::string* release_frienduuid();
  inline void set_allocated_frienduuid(::std::string* frienduuid);

  // @@protoc_insertion_point(class_scope:message.RemoveFriendRequest)
 private:
  inline void set_has_frienduuid();
  inline void clear_has_frienduuid();

  ::std::string* frienduuid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_RemoveFriend_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_RemoveFriend_2eproto();
  #endif
  friend void protobuf_AssignDesc_RemoveFriend_2eproto();
  friend void protobuf_ShutdownFile_RemoveFriend_2eproto();

  void InitAsDefaultInstance();
  static RemoveFriendRequest* default_instance_;
};
// -------------------------------------------------------------------

class RemoveFriendResponse : public ::google::protobuf::MessageLite {
 public:
  RemoveFriendResponse();
  virtual ~RemoveFriendResponse();

  RemoveFriendResponse(const RemoveFriendResponse& from);

  inline RemoveFriendResponse& operator=(const RemoveFriendResponse& from) {
    CopyFrom(from);
    return *this;
  }

  static const RemoveFriendResponse& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const RemoveFriendResponse* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(RemoveFriendResponse* other);

  // implements Message ----------------------------------------------

  RemoveFriendResponse* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const RemoveFriendResponse& from);
  void MergeFrom(const RemoveFriendResponse& from);
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

  typedef RemoveFriendResponse_State State;
  static const State State_Succeed = RemoveFriendResponse_State_State_Succeed;
  static const State State_Fail = RemoveFriendResponse_State_State_Fail;
  static inline bool State_IsValid(int value) {
    return RemoveFriendResponse_State_IsValid(value);
  }
  static const State State_MIN =
    RemoveFriendResponse_State_State_MIN;
  static const State State_MAX =
    RemoveFriendResponse_State_State_MAX;
  static const int State_ARRAYSIZE =
    RemoveFriendResponse_State_State_ARRAYSIZE;

  // accessors -------------------------------------------------------

  // required .message.RemoveFriendResponse.State state = 1;
  inline bool has_state() const;
  inline void clear_state();
  static const int kStateFieldNumber = 1;
  inline ::message::RemoveFriendResponse_State state() const;
  inline void set_state(::message::RemoveFriendResponse_State value);

  // @@protoc_insertion_point(class_scope:message.RemoveFriendResponse)
 private:
  inline void set_has_state();
  inline void clear_has_state();

  int state_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_RemoveFriend_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_RemoveFriend_2eproto();
  #endif
  friend void protobuf_AssignDesc_RemoveFriend_2eproto();
  friend void protobuf_ShutdownFile_RemoveFriend_2eproto();

  void InitAsDefaultInstance();
  static RemoveFriendResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// RemoveFriendRequest

// required string friendUUID = 1;
inline bool RemoveFriendRequest::has_frienduuid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RemoveFriendRequest::set_has_frienduuid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RemoveFriendRequest::clear_has_frienduuid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RemoveFriendRequest::clear_frienduuid() {
  if (frienduuid_ != &::google::protobuf::internal::kEmptyString) {
    frienduuid_->clear();
  }
  clear_has_frienduuid();
}
inline const ::std::string& RemoveFriendRequest::frienduuid() const {
  return *frienduuid_;
}
inline void RemoveFriendRequest::set_frienduuid(const ::std::string& value) {
  set_has_frienduuid();
  if (frienduuid_ == &::google::protobuf::internal::kEmptyString) {
    frienduuid_ = new ::std::string;
  }
  frienduuid_->assign(value);
}
inline void RemoveFriendRequest::set_frienduuid(const char* value) {
  set_has_frienduuid();
  if (frienduuid_ == &::google::protobuf::internal::kEmptyString) {
    frienduuid_ = new ::std::string;
  }
  frienduuid_->assign(value);
}
inline void RemoveFriendRequest::set_frienduuid(const char* value, size_t size) {
  set_has_frienduuid();
  if (frienduuid_ == &::google::protobuf::internal::kEmptyString) {
    frienduuid_ = new ::std::string;
  }
  frienduuid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RemoveFriendRequest::mutable_frienduuid() {
  set_has_frienduuid();
  if (frienduuid_ == &::google::protobuf::internal::kEmptyString) {
    frienduuid_ = new ::std::string;
  }
  return frienduuid_;
}
inline ::std::string* RemoveFriendRequest::release_frienduuid() {
  clear_has_frienduuid();
  if (frienduuid_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = frienduuid_;
    frienduuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void RemoveFriendRequest::set_allocated_frienduuid(::std::string* frienduuid) {
  if (frienduuid_ != &::google::protobuf::internal::kEmptyString) {
    delete frienduuid_;
  }
  if (frienduuid) {
    set_has_frienduuid();
    frienduuid_ = frienduuid;
  } else {
    clear_has_frienduuid();
    frienduuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// RemoveFriendResponse

// required .message.RemoveFriendResponse.State state = 1;
inline bool RemoveFriendResponse::has_state() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RemoveFriendResponse::set_has_state() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RemoveFriendResponse::clear_has_state() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RemoveFriendResponse::clear_state() {
  state_ = 1;
  clear_has_state();
}
inline ::message::RemoveFriendResponse_State RemoveFriendResponse::state() const {
  return static_cast< ::message::RemoveFriendResponse_State >(state_);
}
inline void RemoveFriendResponse::set_state(::message::RemoveFriendResponse_State value) {
  assert(::message::RemoveFriendResponse_State_IsValid(value));
  set_has_state();
  state_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_RemoveFriend_2eproto__INCLUDED
