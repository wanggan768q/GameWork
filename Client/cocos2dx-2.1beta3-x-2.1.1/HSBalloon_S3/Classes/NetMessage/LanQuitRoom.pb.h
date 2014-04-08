// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: LanQuitRoom.proto

#ifndef PROTOBUF_LanQuitRoom_2eproto__INCLUDED
#define PROTOBUF_LanQuitRoom_2eproto__INCLUDED

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
void  protobuf_AddDesc_LanQuitRoom_2eproto();
void protobuf_AssignDesc_LanQuitRoom_2eproto();
void protobuf_ShutdownFile_LanQuitRoom_2eproto();

class LanQuitRoomNotice;

// ===================================================================

class LanQuitRoomNotice : public ::google::protobuf::MessageLite {
 public:
  LanQuitRoomNotice();
  virtual ~LanQuitRoomNotice();

  LanQuitRoomNotice(const LanQuitRoomNotice& from);

  inline LanQuitRoomNotice& operator=(const LanQuitRoomNotice& from) {
    CopyFrom(from);
    return *this;
  }

  static const LanQuitRoomNotice& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const LanQuitRoomNotice* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(LanQuitRoomNotice* other);

  // implements Message ----------------------------------------------

  LanQuitRoomNotice* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const LanQuitRoomNotice& from);
  void MergeFrom(const LanQuitRoomNotice& from);
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

  // required string uuid = 1;
  inline bool has_uuid() const;
  inline void clear_uuid();
  static const int kUuidFieldNumber = 1;
  inline const ::std::string& uuid() const;
  inline void set_uuid(const ::std::string& value);
  inline void set_uuid(const char* value);
  inline void set_uuid(const char* value, size_t size);
  inline ::std::string* mutable_uuid();
  inline ::std::string* release_uuid();
  inline void set_allocated_uuid(::std::string* uuid);

  // @@protoc_insertion_point(class_scope:message.LanQuitRoomNotice)
 private:
  inline void set_has_uuid();
  inline void clear_has_uuid();

  ::std::string* uuid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_LanQuitRoom_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_LanQuitRoom_2eproto();
  #endif
  friend void protobuf_AssignDesc_LanQuitRoom_2eproto();
  friend void protobuf_ShutdownFile_LanQuitRoom_2eproto();

  void InitAsDefaultInstance();
  static LanQuitRoomNotice* default_instance_;
};
// ===================================================================


// ===================================================================

// LanQuitRoomNotice

// required string uuid = 1;
inline bool LanQuitRoomNotice::has_uuid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LanQuitRoomNotice::set_has_uuid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LanQuitRoomNotice::clear_has_uuid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LanQuitRoomNotice::clear_uuid() {
  if (uuid_ != &::google::protobuf::internal::kEmptyString) {
    uuid_->clear();
  }
  clear_has_uuid();
}
inline const ::std::string& LanQuitRoomNotice::uuid() const {
  return *uuid_;
}
inline void LanQuitRoomNotice::set_uuid(const ::std::string& value) {
  set_has_uuid();
  if (uuid_ == &::google::protobuf::internal::kEmptyString) {
    uuid_ = new ::std::string;
  }
  uuid_->assign(value);
}
inline void LanQuitRoomNotice::set_uuid(const char* value) {
  set_has_uuid();
  if (uuid_ == &::google::protobuf::internal::kEmptyString) {
    uuid_ = new ::std::string;
  }
  uuid_->assign(value);
}
inline void LanQuitRoomNotice::set_uuid(const char* value, size_t size) {
  set_has_uuid();
  if (uuid_ == &::google::protobuf::internal::kEmptyString) {
    uuid_ = new ::std::string;
  }
  uuid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* LanQuitRoomNotice::mutable_uuid() {
  set_has_uuid();
  if (uuid_ == &::google::protobuf::internal::kEmptyString) {
    uuid_ = new ::std::string;
  }
  return uuid_;
}
inline ::std::string* LanQuitRoomNotice::release_uuid() {
  clear_has_uuid();
  if (uuid_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = uuid_;
    uuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void LanQuitRoomNotice::set_allocated_uuid(::std::string* uuid) {
  if (uuid_ != &::google::protobuf::internal::kEmptyString) {
    delete uuid_;
  }
  if (uuid) {
    set_has_uuid();
    uuid_ = uuid;
  } else {
    clear_has_uuid();
    uuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_LanQuitRoom_2eproto__INCLUDED