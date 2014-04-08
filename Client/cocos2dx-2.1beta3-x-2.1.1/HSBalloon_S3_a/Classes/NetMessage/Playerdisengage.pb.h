// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Playerdisengage.proto

#ifndef PROTOBUF_Playerdisengage_2eproto__INCLUDED
#define PROTOBUF_Playerdisengage_2eproto__INCLUDED

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
void  protobuf_AddDesc_Playerdisengage_2eproto();
void protobuf_AssignDesc_Playerdisengage_2eproto();
void protobuf_ShutdownFile_Playerdisengage_2eproto();

class PlayerDisengageRequest;
class PlayerDisengageResponse;

enum PlayerDisengageResponse_DisengageStatus {
  PlayerDisengageResponse_DisengageStatus_INITIATIVE = 1,
  PlayerDisengageResponse_DisengageStatus_REACTIVE = 0
};
bool PlayerDisengageResponse_DisengageStatus_IsValid(int value);
const PlayerDisengageResponse_DisengageStatus PlayerDisengageResponse_DisengageStatus_DisengageStatus_MIN = PlayerDisengageResponse_DisengageStatus_REACTIVE;
const PlayerDisengageResponse_DisengageStatus PlayerDisengageResponse_DisengageStatus_DisengageStatus_MAX = PlayerDisengageResponse_DisengageStatus_INITIATIVE;
const int PlayerDisengageResponse_DisengageStatus_DisengageStatus_ARRAYSIZE = PlayerDisengageResponse_DisengageStatus_DisengageStatus_MAX + 1;

// ===================================================================

class PlayerDisengageRequest : public ::google::protobuf::MessageLite {
 public:
  PlayerDisengageRequest();
  virtual ~PlayerDisengageRequest();

  PlayerDisengageRequest(const PlayerDisengageRequest& from);

  inline PlayerDisengageRequest& operator=(const PlayerDisengageRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const PlayerDisengageRequest& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const PlayerDisengageRequest* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(PlayerDisengageRequest* other);

  // implements Message ----------------------------------------------

  PlayerDisengageRequest* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const PlayerDisengageRequest& from);
  void MergeFrom(const PlayerDisengageRequest& from);
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

  // @@protoc_insertion_point(class_scope:message.PlayerDisengageRequest)
 private:
  inline void set_has_did();
  inline void clear_has_did();

  ::std::string* did_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_Playerdisengage_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_Playerdisengage_2eproto();
  #endif
  friend void protobuf_AssignDesc_Playerdisengage_2eproto();
  friend void protobuf_ShutdownFile_Playerdisengage_2eproto();

  void InitAsDefaultInstance();
  static PlayerDisengageRequest* default_instance_;
};
// -------------------------------------------------------------------

class PlayerDisengageResponse : public ::google::protobuf::MessageLite {
 public:
  PlayerDisengageResponse();
  virtual ~PlayerDisengageResponse();

  PlayerDisengageResponse(const PlayerDisengageResponse& from);

  inline PlayerDisengageResponse& operator=(const PlayerDisengageResponse& from) {
    CopyFrom(from);
    return *this;
  }

  static const PlayerDisengageResponse& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const PlayerDisengageResponse* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(PlayerDisengageResponse* other);

  // implements Message ----------------------------------------------

  PlayerDisengageResponse* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const PlayerDisengageResponse& from);
  void MergeFrom(const PlayerDisengageResponse& from);
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

  typedef PlayerDisengageResponse_DisengageStatus DisengageStatus;
  static const DisengageStatus INITIATIVE = PlayerDisengageResponse_DisengageStatus_INITIATIVE;
  static const DisengageStatus REACTIVE = PlayerDisengageResponse_DisengageStatus_REACTIVE;
  static inline bool DisengageStatus_IsValid(int value) {
    return PlayerDisengageResponse_DisengageStatus_IsValid(value);
  }
  static const DisengageStatus DisengageStatus_MIN =
    PlayerDisengageResponse_DisengageStatus_DisengageStatus_MIN;
  static const DisengageStatus DisengageStatus_MAX =
    PlayerDisengageResponse_DisengageStatus_DisengageStatus_MAX;
  static const int DisengageStatus_ARRAYSIZE =
    PlayerDisengageResponse_DisengageStatus_DisengageStatus_ARRAYSIZE;

  // accessors -------------------------------------------------------

  // required .message.PlayerDisengageResponse.DisengageStatus status = 1;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 1;
  inline ::message::PlayerDisengageResponse_DisengageStatus status() const;
  inline void set_status(::message::PlayerDisengageResponse_DisengageStatus value);

  // @@protoc_insertion_point(class_scope:message.PlayerDisengageResponse)
 private:
  inline void set_has_status();
  inline void clear_has_status();

  int status_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_Playerdisengage_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_Playerdisengage_2eproto();
  #endif
  friend void protobuf_AssignDesc_Playerdisengage_2eproto();
  friend void protobuf_ShutdownFile_Playerdisengage_2eproto();

  void InitAsDefaultInstance();
  static PlayerDisengageResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// PlayerDisengageRequest

// required string did = 1;
inline bool PlayerDisengageRequest::has_did() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PlayerDisengageRequest::set_has_did() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PlayerDisengageRequest::clear_has_did() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PlayerDisengageRequest::clear_did() {
  if (did_ != &::google::protobuf::internal::kEmptyString) {
    did_->clear();
  }
  clear_has_did();
}
inline const ::std::string& PlayerDisengageRequest::did() const {
  return *did_;
}
inline void PlayerDisengageRequest::set_did(const ::std::string& value) {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  did_->assign(value);
}
inline void PlayerDisengageRequest::set_did(const char* value) {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  did_->assign(value);
}
inline void PlayerDisengageRequest::set_did(const char* value, size_t size) {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  did_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PlayerDisengageRequest::mutable_did() {
  set_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    did_ = new ::std::string;
  }
  return did_;
}
inline ::std::string* PlayerDisengageRequest::release_did() {
  clear_has_did();
  if (did_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = did_;
    did_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void PlayerDisengageRequest::set_allocated_did(::std::string* did) {
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

// -------------------------------------------------------------------

// PlayerDisengageResponse

// required .message.PlayerDisengageResponse.DisengageStatus status = 1;
inline bool PlayerDisengageResponse::has_status() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PlayerDisengageResponse::set_has_status() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PlayerDisengageResponse::clear_has_status() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PlayerDisengageResponse::clear_status() {
  status_ = 1;
  clear_has_status();
}
inline ::message::PlayerDisengageResponse_DisengageStatus PlayerDisengageResponse::status() const {
  return static_cast< ::message::PlayerDisengageResponse_DisengageStatus >(status_);
}
inline void PlayerDisengageResponse::set_status(::message::PlayerDisengageResponse_DisengageStatus value) {
  assert(::message::PlayerDisengageResponse_DisengageStatus_IsValid(value));
  set_has_status();
  status_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Playerdisengage_2eproto__INCLUDED
