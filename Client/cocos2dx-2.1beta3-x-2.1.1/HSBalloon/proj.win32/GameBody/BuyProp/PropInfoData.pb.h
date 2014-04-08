// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PropInfoData.proto

#ifndef PROTOBUF_PropInfoData_2eproto__INCLUDED
#define PROTOBUF_PropInfoData_2eproto__INCLUDED

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
#include "PropInfo.pb.h"
// @@protoc_insertion_point(includes)

namespace message {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_PropInfoData_2eproto();
void protobuf_AssignDesc_PropInfoData_2eproto();
void protobuf_ShutdownFile_PropInfoData_2eproto();

class PropInfoData;

// ===================================================================

class PropInfoData : public ::google::protobuf::MessageLite {
 public:
  PropInfoData();
  virtual ~PropInfoData();
  
  PropInfoData(const PropInfoData& from);
  
  inline PropInfoData& operator=(const PropInfoData& from) {
    CopyFrom(from);
    return *this;
  }
  
  static const PropInfoData& default_instance();
  
  void Swap(PropInfoData* other);
  
  // implements Message ----------------------------------------------
  
  PropInfoData* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const PropInfoData& from);
  void MergeFrom(const PropInfoData& from);
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
  
  // repeated .message.PropInfo manualPropInfoList = 1;
  inline int manualpropinfolist_size() const;
  inline void clear_manualpropinfolist();
  static const int kManualPropInfoListFieldNumber = 1;
  inline const ::message::PropInfo& manualpropinfolist(int index) const;
  inline ::message::PropInfo* mutable_manualpropinfolist(int index);
  inline ::message::PropInfo* add_manualpropinfolist();
  inline const ::google::protobuf::RepeatedPtrField< ::message::PropInfo >&
      manualpropinfolist() const;
  inline ::google::protobuf::RepeatedPtrField< ::message::PropInfo >*
      mutable_manualpropinfolist();
  
  // repeated .message.PropInfo bufferPropInfoList = 2;
  inline int bufferpropinfolist_size() const;
  inline void clear_bufferpropinfolist();
  static const int kBufferPropInfoListFieldNumber = 2;
  inline const ::message::PropInfo& bufferpropinfolist(int index) const;
  inline ::message::PropInfo* mutable_bufferpropinfolist(int index);
  inline ::message::PropInfo* add_bufferpropinfolist();
  inline const ::google::protobuf::RepeatedPtrField< ::message::PropInfo >&
      bufferpropinfolist() const;
  inline ::google::protobuf::RepeatedPtrField< ::message::PropInfo >*
      mutable_bufferpropinfolist();
  
  // repeated .message.PropInfo giftBagPropInfoList = 3;
  inline int giftbagpropinfolist_size() const;
  inline void clear_giftbagpropinfolist();
  static const int kGiftBagPropInfoListFieldNumber = 3;
  inline const ::message::PropInfo& giftbagpropinfolist(int index) const;
  inline ::message::PropInfo* mutable_giftbagpropinfolist(int index);
  inline ::message::PropInfo* add_giftbagpropinfolist();
  inline const ::google::protobuf::RepeatedPtrField< ::message::PropInfo >&
      giftbagpropinfolist() const;
  inline ::google::protobuf::RepeatedPtrField< ::message::PropInfo >*
      mutable_giftbagpropinfolist();
  
  // repeated .message.PropInfo cheapPropInfoList = 4;
  inline int cheappropinfolist_size() const;
  inline void clear_cheappropinfolist();
  static const int kCheapPropInfoListFieldNumber = 4;
  inline const ::message::PropInfo& cheappropinfolist(int index) const;
  inline ::message::PropInfo* mutable_cheappropinfolist(int index);
  inline ::message::PropInfo* add_cheappropinfolist();
  inline const ::google::protobuf::RepeatedPtrField< ::message::PropInfo >&
      cheappropinfolist() const;
  inline ::google::protobuf::RepeatedPtrField< ::message::PropInfo >*
      mutable_cheappropinfolist();
  
  // repeated .message.PropInfo lockPropInfoList = 5;
  inline int lockpropinfolist_size() const;
  inline void clear_lockpropinfolist();
  static const int kLockPropInfoListFieldNumber = 5;
  inline const ::message::PropInfo& lockpropinfolist(int index) const;
  inline ::message::PropInfo* mutable_lockpropinfolist(int index);
  inline ::message::PropInfo* add_lockpropinfolist();
  inline const ::google::protobuf::RepeatedPtrField< ::message::PropInfo >&
      lockpropinfolist() const;
  inline ::google::protobuf::RepeatedPtrField< ::message::PropInfo >*
      mutable_lockpropinfolist();
  
  // @@protoc_insertion_point(class_scope:message.PropInfoData)
 private:
  
  ::google::protobuf::RepeatedPtrField< ::message::PropInfo > manualpropinfolist_;
  ::google::protobuf::RepeatedPtrField< ::message::PropInfo > bufferpropinfolist_;
  ::google::protobuf::RepeatedPtrField< ::message::PropInfo > giftbagpropinfolist_;
  ::google::protobuf::RepeatedPtrField< ::message::PropInfo > cheappropinfolist_;
  ::google::protobuf::RepeatedPtrField< ::message::PropInfo > lockpropinfolist_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];
  
  friend void  protobuf_AddDesc_PropInfoData_2eproto();
  friend void protobuf_AssignDesc_PropInfoData_2eproto();
  friend void protobuf_ShutdownFile_PropInfoData_2eproto();
  
  void InitAsDefaultInstance();
  static PropInfoData* default_instance_;
};
// ===================================================================


// ===================================================================

// PropInfoData

// repeated .message.PropInfo manualPropInfoList = 1;
inline int PropInfoData::manualpropinfolist_size() const {
  return manualpropinfolist_.size();
}
inline void PropInfoData::clear_manualpropinfolist() {
  manualpropinfolist_.Clear();
}
inline const ::message::PropInfo& PropInfoData::manualpropinfolist(int index) const {
  return manualpropinfolist_.Get(index);
}
inline ::message::PropInfo* PropInfoData::mutable_manualpropinfolist(int index) {
  return manualpropinfolist_.Mutable(index);
}
inline ::message::PropInfo* PropInfoData::add_manualpropinfolist() {
  return manualpropinfolist_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::message::PropInfo >&
PropInfoData::manualpropinfolist() const {
  return manualpropinfolist_;
}
inline ::google::protobuf::RepeatedPtrField< ::message::PropInfo >*
PropInfoData::mutable_manualpropinfolist() {
  return &manualpropinfolist_;
}

// repeated .message.PropInfo bufferPropInfoList = 2;
inline int PropInfoData::bufferpropinfolist_size() const {
  return bufferpropinfolist_.size();
}
inline void PropInfoData::clear_bufferpropinfolist() {
  bufferpropinfolist_.Clear();
}
inline const ::message::PropInfo& PropInfoData::bufferpropinfolist(int index) const {
  return bufferpropinfolist_.Get(index);
}
inline ::message::PropInfo* PropInfoData::mutable_bufferpropinfolist(int index) {
  return bufferpropinfolist_.Mutable(index);
}
inline ::message::PropInfo* PropInfoData::add_bufferpropinfolist() {
  return bufferpropinfolist_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::message::PropInfo >&
PropInfoData::bufferpropinfolist() const {
  return bufferpropinfolist_;
}
inline ::google::protobuf::RepeatedPtrField< ::message::PropInfo >*
PropInfoData::mutable_bufferpropinfolist() {
  return &bufferpropinfolist_;
}

// repeated .message.PropInfo giftBagPropInfoList = 3;
inline int PropInfoData::giftbagpropinfolist_size() const {
  return giftbagpropinfolist_.size();
}
inline void PropInfoData::clear_giftbagpropinfolist() {
  giftbagpropinfolist_.Clear();
}
inline const ::message::PropInfo& PropInfoData::giftbagpropinfolist(int index) const {
  return giftbagpropinfolist_.Get(index);
}
inline ::message::PropInfo* PropInfoData::mutable_giftbagpropinfolist(int index) {
  return giftbagpropinfolist_.Mutable(index);
}
inline ::message::PropInfo* PropInfoData::add_giftbagpropinfolist() {
  return giftbagpropinfolist_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::message::PropInfo >&
PropInfoData::giftbagpropinfolist() const {
  return giftbagpropinfolist_;
}
inline ::google::protobuf::RepeatedPtrField< ::message::PropInfo >*
PropInfoData::mutable_giftbagpropinfolist() {
  return &giftbagpropinfolist_;
}

// repeated .message.PropInfo cheapPropInfoList = 4;
inline int PropInfoData::cheappropinfolist_size() const {
  return cheappropinfolist_.size();
}
inline void PropInfoData::clear_cheappropinfolist() {
  cheappropinfolist_.Clear();
}
inline const ::message::PropInfo& PropInfoData::cheappropinfolist(int index) const {
  return cheappropinfolist_.Get(index);
}
inline ::message::PropInfo* PropInfoData::mutable_cheappropinfolist(int index) {
  return cheappropinfolist_.Mutable(index);
}
inline ::message::PropInfo* PropInfoData::add_cheappropinfolist() {
  return cheappropinfolist_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::message::PropInfo >&
PropInfoData::cheappropinfolist() const {
  return cheappropinfolist_;
}
inline ::google::protobuf::RepeatedPtrField< ::message::PropInfo >*
PropInfoData::mutable_cheappropinfolist() {
  return &cheappropinfolist_;
}

// repeated .message.PropInfo lockPropInfoList = 5;
inline int PropInfoData::lockpropinfolist_size() const {
  return lockpropinfolist_.size();
}
inline void PropInfoData::clear_lockpropinfolist() {
  lockpropinfolist_.Clear();
}
inline const ::message::PropInfo& PropInfoData::lockpropinfolist(int index) const {
  return lockpropinfolist_.Get(index);
}
inline ::message::PropInfo* PropInfoData::mutable_lockpropinfolist(int index) {
  return lockpropinfolist_.Mutable(index);
}
inline ::message::PropInfo* PropInfoData::add_lockpropinfolist() {
  return lockpropinfolist_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::message::PropInfo >&
PropInfoData::lockpropinfolist() const {
  return lockpropinfolist_;
}
inline ::google::protobuf::RepeatedPtrField< ::message::PropInfo >*
PropInfoData::mutable_lockpropinfolist() {
  return &lockpropinfolist_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_PropInfoData_2eproto__INCLUDED
