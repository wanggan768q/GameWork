// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AddressBook.proto

#ifndef PROTOBUF_AddressBook_2eproto__INCLUDED
#define PROTOBUF_AddressBook_2eproto__INCLUDED

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
void  protobuf_AddDesc_AddressBook_2eproto();
void protobuf_AssignDesc_AddressBook_2eproto();
void protobuf_ShutdownFile_AddressBook_2eproto();

class AddressBookRequest;
class AddressBookResponse;
class AddressBookResponse_Name;

// ===================================================================

class AddressBookRequest : public ::google::protobuf::MessageLite {
 public:
  AddressBookRequest();
  virtual ~AddressBookRequest();

  AddressBookRequest(const AddressBookRequest& from);

  inline AddressBookRequest& operator=(const AddressBookRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const AddressBookRequest& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const AddressBookRequest* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(AddressBookRequest* other);

  // implements Message ----------------------------------------------

  AddressBookRequest* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const AddressBookRequest& from);
  void MergeFrom(const AddressBookRequest& from);
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

  // optional uint32 wb_Type = 1;
  inline bool has_wb_type() const;
  inline void clear_wb_type();
  static const int kWbTypeFieldNumber = 1;
  inline ::google::protobuf::uint32 wb_type() const;
  inline void set_wb_type(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:message.AddressBookRequest)
 private:
  inline void set_has_wb_type();
  inline void clear_has_wb_type();

  ::google::protobuf::uint32 wb_type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_AddressBook_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_AddressBook_2eproto();
  #endif
  friend void protobuf_AssignDesc_AddressBook_2eproto();
  friend void protobuf_ShutdownFile_AddressBook_2eproto();

  void InitAsDefaultInstance();
  static AddressBookRequest* default_instance_;
};
// -------------------------------------------------------------------

class AddressBookResponse_Name : public ::google::protobuf::MessageLite {
 public:
  AddressBookResponse_Name();
  virtual ~AddressBookResponse_Name();

  AddressBookResponse_Name(const AddressBookResponse_Name& from);

  inline AddressBookResponse_Name& operator=(const AddressBookResponse_Name& from) {
    CopyFrom(from);
    return *this;
  }

  static const AddressBookResponse_Name& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const AddressBookResponse_Name* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(AddressBookResponse_Name* other);

  // implements Message ----------------------------------------------

  AddressBookResponse_Name* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const AddressBookResponse_Name& from);
  void MergeFrom(const AddressBookResponse_Name& from);
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

  // required string wb_name = 1;
  inline bool has_wb_name() const;
  inline void clear_wb_name();
  static const int kWbNameFieldNumber = 1;
  inline const ::std::string& wb_name() const;
  inline void set_wb_name(const ::std::string& value);
  inline void set_wb_name(const char* value);
  inline void set_wb_name(const char* value, size_t size);
  inline ::std::string* mutable_wb_name();
  inline ::std::string* release_wb_name();
  inline void set_allocated_wb_name(::std::string* wb_name);

  // required string nick_name = 2;
  inline bool has_nick_name() const;
  inline void clear_nick_name();
  static const int kNickNameFieldNumber = 2;
  inline const ::std::string& nick_name() const;
  inline void set_nick_name(const ::std::string& value);
  inline void set_nick_name(const char* value);
  inline void set_nick_name(const char* value, size_t size);
  inline ::std::string* mutable_nick_name();
  inline ::std::string* release_nick_name();
  inline void set_allocated_nick_name(::std::string* nick_name);

  // @@protoc_insertion_point(class_scope:message.AddressBookResponse.Name)
 private:
  inline void set_has_wb_name();
  inline void clear_has_wb_name();
  inline void set_has_nick_name();
  inline void clear_has_nick_name();

  ::std::string* wb_name_;
  ::std::string* nick_name_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_AddressBook_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_AddressBook_2eproto();
  #endif
  friend void protobuf_AssignDesc_AddressBook_2eproto();
  friend void protobuf_ShutdownFile_AddressBook_2eproto();

  void InitAsDefaultInstance();
  static AddressBookResponse_Name* default_instance_;
};
// -------------------------------------------------------------------

class AddressBookResponse : public ::google::protobuf::MessageLite {
 public:
  AddressBookResponse();
  virtual ~AddressBookResponse();

  AddressBookResponse(const AddressBookResponse& from);

  inline AddressBookResponse& operator=(const AddressBookResponse& from) {
    CopyFrom(from);
    return *this;
  }

  static const AddressBookResponse& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const AddressBookResponse* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(AddressBookResponse* other);

  // implements Message ----------------------------------------------

  AddressBookResponse* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const AddressBookResponse& from);
  void MergeFrom(const AddressBookResponse& from);
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

  typedef AddressBookResponse_Name Name;

  // accessors -------------------------------------------------------

  // repeated .message.AddressBookResponse.Name nameList = 1;
  inline int namelist_size() const;
  inline void clear_namelist();
  static const int kNameListFieldNumber = 1;
  inline const ::message::AddressBookResponse_Name& namelist(int index) const;
  inline ::message::AddressBookResponse_Name* mutable_namelist(int index);
  inline ::message::AddressBookResponse_Name* add_namelist();
  inline const ::google::protobuf::RepeatedPtrField< ::message::AddressBookResponse_Name >&
      namelist() const;
  inline ::google::protobuf::RepeatedPtrField< ::message::AddressBookResponse_Name >*
      mutable_namelist();

  // @@protoc_insertion_point(class_scope:message.AddressBookResponse)
 private:

  ::google::protobuf::RepeatedPtrField< ::message::AddressBookResponse_Name > namelist_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_AddressBook_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_AddressBook_2eproto();
  #endif
  friend void protobuf_AssignDesc_AddressBook_2eproto();
  friend void protobuf_ShutdownFile_AddressBook_2eproto();

  void InitAsDefaultInstance();
  static AddressBookResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// AddressBookRequest

// optional uint32 wb_Type = 1;
inline bool AddressBookRequest::has_wb_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AddressBookRequest::set_has_wb_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AddressBookRequest::clear_has_wb_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AddressBookRequest::clear_wb_type() {
  wb_type_ = 0u;
  clear_has_wb_type();
}
inline ::google::protobuf::uint32 AddressBookRequest::wb_type() const {
  return wb_type_;
}
inline void AddressBookRequest::set_wb_type(::google::protobuf::uint32 value) {
  set_has_wb_type();
  wb_type_ = value;
}

// -------------------------------------------------------------------

// AddressBookResponse_Name

// required string wb_name = 1;
inline bool AddressBookResponse_Name::has_wb_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AddressBookResponse_Name::set_has_wb_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AddressBookResponse_Name::clear_has_wb_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AddressBookResponse_Name::clear_wb_name() {
  if (wb_name_ != &::google::protobuf::internal::kEmptyString) {
    wb_name_->clear();
  }
  clear_has_wb_name();
}
inline const ::std::string& AddressBookResponse_Name::wb_name() const {
  return *wb_name_;
}
inline void AddressBookResponse_Name::set_wb_name(const ::std::string& value) {
  set_has_wb_name();
  if (wb_name_ == &::google::protobuf::internal::kEmptyString) {
    wb_name_ = new ::std::string;
  }
  wb_name_->assign(value);
}
inline void AddressBookResponse_Name::set_wb_name(const char* value) {
  set_has_wb_name();
  if (wb_name_ == &::google::protobuf::internal::kEmptyString) {
    wb_name_ = new ::std::string;
  }
  wb_name_->assign(value);
}
inline void AddressBookResponse_Name::set_wb_name(const char* value, size_t size) {
  set_has_wb_name();
  if (wb_name_ == &::google::protobuf::internal::kEmptyString) {
    wb_name_ = new ::std::string;
  }
  wb_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AddressBookResponse_Name::mutable_wb_name() {
  set_has_wb_name();
  if (wb_name_ == &::google::protobuf::internal::kEmptyString) {
    wb_name_ = new ::std::string;
  }
  return wb_name_;
}
inline ::std::string* AddressBookResponse_Name::release_wb_name() {
  clear_has_wb_name();
  if (wb_name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = wb_name_;
    wb_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AddressBookResponse_Name::set_allocated_wb_name(::std::string* wb_name) {
  if (wb_name_ != &::google::protobuf::internal::kEmptyString) {
    delete wb_name_;
  }
  if (wb_name) {
    set_has_wb_name();
    wb_name_ = wb_name;
  } else {
    clear_has_wb_name();
    wb_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string nick_name = 2;
inline bool AddressBookResponse_Name::has_nick_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AddressBookResponse_Name::set_has_nick_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AddressBookResponse_Name::clear_has_nick_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AddressBookResponse_Name::clear_nick_name() {
  if (nick_name_ != &::google::protobuf::internal::kEmptyString) {
    nick_name_->clear();
  }
  clear_has_nick_name();
}
inline const ::std::string& AddressBookResponse_Name::nick_name() const {
  return *nick_name_;
}
inline void AddressBookResponse_Name::set_nick_name(const ::std::string& value) {
  set_has_nick_name();
  if (nick_name_ == &::google::protobuf::internal::kEmptyString) {
    nick_name_ = new ::std::string;
  }
  nick_name_->assign(value);
}
inline void AddressBookResponse_Name::set_nick_name(const char* value) {
  set_has_nick_name();
  if (nick_name_ == &::google::protobuf::internal::kEmptyString) {
    nick_name_ = new ::std::string;
  }
  nick_name_->assign(value);
}
inline void AddressBookResponse_Name::set_nick_name(const char* value, size_t size) {
  set_has_nick_name();
  if (nick_name_ == &::google::protobuf::internal::kEmptyString) {
    nick_name_ = new ::std::string;
  }
  nick_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AddressBookResponse_Name::mutable_nick_name() {
  set_has_nick_name();
  if (nick_name_ == &::google::protobuf::internal::kEmptyString) {
    nick_name_ = new ::std::string;
  }
  return nick_name_;
}
inline ::std::string* AddressBookResponse_Name::release_nick_name() {
  clear_has_nick_name();
  if (nick_name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = nick_name_;
    nick_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AddressBookResponse_Name::set_allocated_nick_name(::std::string* nick_name) {
  if (nick_name_ != &::google::protobuf::internal::kEmptyString) {
    delete nick_name_;
  }
  if (nick_name) {
    set_has_nick_name();
    nick_name_ = nick_name;
  } else {
    clear_has_nick_name();
    nick_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// AddressBookResponse

// repeated .message.AddressBookResponse.Name nameList = 1;
inline int AddressBookResponse::namelist_size() const {
  return namelist_.size();
}
inline void AddressBookResponse::clear_namelist() {
  namelist_.Clear();
}
inline const ::message::AddressBookResponse_Name& AddressBookResponse::namelist(int index) const {
  return namelist_.Get(index);
}
inline ::message::AddressBookResponse_Name* AddressBookResponse::mutable_namelist(int index) {
  return namelist_.Mutable(index);
}
inline ::message::AddressBookResponse_Name* AddressBookResponse::add_namelist() {
  return namelist_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::message::AddressBookResponse_Name >&
AddressBookResponse::namelist() const {
  return namelist_;
}
inline ::google::protobuf::RepeatedPtrField< ::message::AddressBookResponse_Name >*
AddressBookResponse::mutable_namelist() {
  return &namelist_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_AddressBook_2eproto__INCLUDED