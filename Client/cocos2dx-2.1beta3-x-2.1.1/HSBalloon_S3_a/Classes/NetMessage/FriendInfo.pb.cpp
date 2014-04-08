// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FriendInfo.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "FriendInfo.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_FriendInfo_2eproto() {
  delete FriendInfoRequest::default_instance_;
  delete FriendInfoResponse::default_instance_;
  delete FriendInfoResponse_PlayerInfoList::default_instance_;
  delete FriendInfoResponse_PlayerInfo::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_FriendInfo_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_FriendInfo_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  FriendInfoRequest::default_instance_ = new FriendInfoRequest();
  FriendInfoResponse::default_instance_ = new FriendInfoResponse();
  FriendInfoResponse_PlayerInfoList::default_instance_ = new FriendInfoResponse_PlayerInfoList();
  FriendInfoResponse_PlayerInfo::default_instance_ = new FriendInfoResponse_PlayerInfo();
  FriendInfoRequest::default_instance_->InitAsDefaultInstance();
  FriendInfoResponse::default_instance_->InitAsDefaultInstance();
  FriendInfoResponse_PlayerInfoList::default_instance_->InitAsDefaultInstance();
  FriendInfoResponse_PlayerInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_FriendInfo_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_FriendInfo_2eproto_once_);
void protobuf_AddDesc_FriendInfo_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_FriendInfo_2eproto_once_,
                 &protobuf_AddDesc_FriendInfo_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_FriendInfo_2eproto {
  StaticDescriptorInitializer_FriendInfo_2eproto() {
    protobuf_AddDesc_FriendInfo_2eproto();
  }
} static_descriptor_initializer_FriendInfo_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

FriendInfoRequest::FriendInfoRequest()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void FriendInfoRequest::InitAsDefaultInstance() {
}

FriendInfoRequest::FriendInfoRequest(const FriendInfoRequest& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void FriendInfoRequest::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FriendInfoRequest::~FriendInfoRequest() {
  SharedDtor();
}

void FriendInfoRequest::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void FriendInfoRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const FriendInfoRequest& FriendInfoRequest::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_FriendInfo_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_FriendInfo_2eproto();
#endif
  return *default_instance_;
}

FriendInfoRequest* FriendInfoRequest::default_instance_ = NULL;

FriendInfoRequest* FriendInfoRequest::New() const {
  return new FriendInfoRequest;
}

void FriendInfoRequest::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool FriendInfoRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      return true;
    }
    DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
  }
  return true;
#undef DO_
}

void FriendInfoRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
}

int FriendInfoRequest::ByteSize() const {
  int total_size = 0;

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FriendInfoRequest::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const FriendInfoRequest*>(&from));
}

void FriendInfoRequest::MergeFrom(const FriendInfoRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
}

void FriendInfoRequest::CopyFrom(const FriendInfoRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FriendInfoRequest::IsInitialized() const {

  return true;
}

void FriendInfoRequest::Swap(FriendInfoRequest* other) {
  if (other != this) {
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string FriendInfoRequest::GetTypeName() const {
  return "message.FriendInfoRequest";
}


// ===================================================================

#ifndef _MSC_VER
const int FriendInfoResponse_PlayerInfoList::kMaxCountFieldNumber;
const int FriendInfoResponse_PlayerInfoList::kListFieldNumber;
#endif  // !_MSC_VER

FriendInfoResponse_PlayerInfoList::FriendInfoResponse_PlayerInfoList()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void FriendInfoResponse_PlayerInfoList::InitAsDefaultInstance() {
}

FriendInfoResponse_PlayerInfoList::FriendInfoResponse_PlayerInfoList(const FriendInfoResponse_PlayerInfoList& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void FriendInfoResponse_PlayerInfoList::SharedCtor() {
  _cached_size_ = 0;
  maxcount_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FriendInfoResponse_PlayerInfoList::~FriendInfoResponse_PlayerInfoList() {
  SharedDtor();
}

void FriendInfoResponse_PlayerInfoList::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void FriendInfoResponse_PlayerInfoList::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const FriendInfoResponse_PlayerInfoList& FriendInfoResponse_PlayerInfoList::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_FriendInfo_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_FriendInfo_2eproto();
#endif
  return *default_instance_;
}

FriendInfoResponse_PlayerInfoList* FriendInfoResponse_PlayerInfoList::default_instance_ = NULL;

FriendInfoResponse_PlayerInfoList* FriendInfoResponse_PlayerInfoList::New() const {
  return new FriendInfoResponse_PlayerInfoList;
}

void FriendInfoResponse_PlayerInfoList::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    maxcount_ = 0;
  }
  list_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool FriendInfoResponse_PlayerInfoList::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 maxCount = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &maxcount_)));
          set_has_maxcount();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_list;
        break;
      }

      // repeated .message.FriendInfoResponse.PlayerInfo list = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_list:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_list()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_list;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FriendInfoResponse_PlayerInfoList::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 maxCount = 1;
  if (has_maxcount()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->maxcount(), output);
  }

  // repeated .message.FriendInfoResponse.PlayerInfo list = 2;
  for (int i = 0; i < this->list_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      2, this->list(i), output);
  }

}

int FriendInfoResponse_PlayerInfoList::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 maxCount = 1;
    if (has_maxcount()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->maxcount());
    }

  }
  // repeated .message.FriendInfoResponse.PlayerInfo list = 2;
  total_size += 1 * this->list_size();
  for (int i = 0; i < this->list_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->list(i));
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FriendInfoResponse_PlayerInfoList::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const FriendInfoResponse_PlayerInfoList*>(&from));
}

void FriendInfoResponse_PlayerInfoList::MergeFrom(const FriendInfoResponse_PlayerInfoList& from) {
  GOOGLE_CHECK_NE(&from, this);
  list_.MergeFrom(from.list_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_maxcount()) {
      set_maxcount(from.maxcount());
    }
  }
}

void FriendInfoResponse_PlayerInfoList::CopyFrom(const FriendInfoResponse_PlayerInfoList& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FriendInfoResponse_PlayerInfoList::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  for (int i = 0; i < list_size(); i++) {
    if (!this->list(i).IsInitialized()) return false;
  }
  return true;
}

void FriendInfoResponse_PlayerInfoList::Swap(FriendInfoResponse_PlayerInfoList* other) {
  if (other != this) {
    std::swap(maxcount_, other->maxcount_);
    list_.Swap(&other->list_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string FriendInfoResponse_PlayerInfoList::GetTypeName() const {
  return "message.FriendInfoResponse.PlayerInfoList";
}


// -------------------------------------------------------------------

bool FriendInfoResponse_PlayerInfo_State_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const FriendInfoResponse_PlayerInfo_State FriendInfoResponse_PlayerInfo::State_Online;
const FriendInfoResponse_PlayerInfo_State FriendInfoResponse_PlayerInfo::State_Busy;
const FriendInfoResponse_PlayerInfo_State FriendInfoResponse_PlayerInfo::State_Offline;
const FriendInfoResponse_PlayerInfo_State FriendInfoResponse_PlayerInfo::State_MIN;
const FriendInfoResponse_PlayerInfo_State FriendInfoResponse_PlayerInfo::State_MAX;
const int FriendInfoResponse_PlayerInfo::State_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int FriendInfoResponse_PlayerInfo::kFriendUUIDFieldNumber;
const int FriendInfoResponse_PlayerInfo::kFriendNameFieldNumber;
const int FriendInfoResponse_PlayerInfo::kGameScoreFieldNumber;
const int FriendInfoResponse_PlayerInfo::kMoneyFieldNumber;
const int FriendInfoResponse_PlayerInfo::kHeadIconFieldNumber;
const int FriendInfoResponse_PlayerInfo::kStateFieldNumber;
const int FriendInfoResponse_PlayerInfo::kEmailFieldNumber;
#endif  // !_MSC_VER

FriendInfoResponse_PlayerInfo::FriendInfoResponse_PlayerInfo()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void FriendInfoResponse_PlayerInfo::InitAsDefaultInstance() {
}

FriendInfoResponse_PlayerInfo::FriendInfoResponse_PlayerInfo(const FriendInfoResponse_PlayerInfo& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void FriendInfoResponse_PlayerInfo::SharedCtor() {
  _cached_size_ = 0;
  frienduuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  friendname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  gamescore_ = 0;
  money_ = 0;
  headicon_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  state_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FriendInfoResponse_PlayerInfo::~FriendInfoResponse_PlayerInfo() {
  SharedDtor();
}

void FriendInfoResponse_PlayerInfo::SharedDtor() {
  if (frienduuid_ != &::google::protobuf::internal::kEmptyString) {
    delete frienduuid_;
  }
  if (friendname_ != &::google::protobuf::internal::kEmptyString) {
    delete friendname_;
  }
  if (headicon_ != &::google::protobuf::internal::kEmptyString) {
    delete headicon_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void FriendInfoResponse_PlayerInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const FriendInfoResponse_PlayerInfo& FriendInfoResponse_PlayerInfo::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_FriendInfo_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_FriendInfo_2eproto();
#endif
  return *default_instance_;
}

FriendInfoResponse_PlayerInfo* FriendInfoResponse_PlayerInfo::default_instance_ = NULL;

FriendInfoResponse_PlayerInfo* FriendInfoResponse_PlayerInfo::New() const {
  return new FriendInfoResponse_PlayerInfo;
}

void FriendInfoResponse_PlayerInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_frienduuid()) {
      if (frienduuid_ != &::google::protobuf::internal::kEmptyString) {
        frienduuid_->clear();
      }
    }
    if (has_friendname()) {
      if (friendname_ != &::google::protobuf::internal::kEmptyString) {
        friendname_->clear();
      }
    }
    gamescore_ = 0;
    money_ = 0;
    if (has_headicon()) {
      if (headicon_ != &::google::protobuf::internal::kEmptyString) {
        headicon_->clear();
      }
    }
    state_ = 0;
  }
  email_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool FriendInfoResponse_PlayerInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string friendUUID = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_frienduuid()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_friendName;
        break;
      }

      // required string friendName = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_friendName:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_friendname()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_gameScore;
        break;
      }

      // required int32 gameScore = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_gameScore:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &gamescore_)));
          set_has_gamescore();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_money;
        break;
      }

      // required int32 money = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_money:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &money_)));
          set_has_money();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_headIcon;
        break;
      }

      // required string headIcon = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_headIcon:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_headicon()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_state;
        break;
      }

      // required .message.FriendInfoResponse.PlayerInfo.State state = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_state:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::message::FriendInfoResponse_PlayerInfo_State_IsValid(value)) {
            set_state(static_cast< ::message::FriendInfoResponse_PlayerInfo_State >(value));
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_email;
        break;
      }

      // repeated string email = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_email:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_email()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_email;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FriendInfoResponse_PlayerInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string friendUUID = 1;
  if (has_frienduuid()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->frienduuid(), output);
  }

  // required string friendName = 2;
  if (has_friendname()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->friendname(), output);
  }

  // required int32 gameScore = 3;
  if (has_gamescore()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->gamescore(), output);
  }

  // required int32 money = 4;
  if (has_money()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->money(), output);
  }

  // required string headIcon = 5;
  if (has_headicon()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->headicon(), output);
  }

  // required .message.FriendInfoResponse.PlayerInfo.State state = 6;
  if (has_state()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      6, this->state(), output);
  }

  // repeated string email = 7;
  for (int i = 0; i < this->email_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      7, this->email(i), output);
  }

}

int FriendInfoResponse_PlayerInfo::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string friendUUID = 1;
    if (has_frienduuid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->frienduuid());
    }

    // required string friendName = 2;
    if (has_friendname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->friendname());
    }

    // required int32 gameScore = 3;
    if (has_gamescore()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->gamescore());
    }

    // required int32 money = 4;
    if (has_money()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->money());
    }

    // required string headIcon = 5;
    if (has_headicon()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->headicon());
    }

    // required .message.FriendInfoResponse.PlayerInfo.State state = 6;
    if (has_state()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->state());
    }

  }
  // repeated string email = 7;
  total_size += 1 * this->email_size();
  for (int i = 0; i < this->email_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->email(i));
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FriendInfoResponse_PlayerInfo::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const FriendInfoResponse_PlayerInfo*>(&from));
}

void FriendInfoResponse_PlayerInfo::MergeFrom(const FriendInfoResponse_PlayerInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  email_.MergeFrom(from.email_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_frienduuid()) {
      set_frienduuid(from.frienduuid());
    }
    if (from.has_friendname()) {
      set_friendname(from.friendname());
    }
    if (from.has_gamescore()) {
      set_gamescore(from.gamescore());
    }
    if (from.has_money()) {
      set_money(from.money());
    }
    if (from.has_headicon()) {
      set_headicon(from.headicon());
    }
    if (from.has_state()) {
      set_state(from.state());
    }
  }
}

void FriendInfoResponse_PlayerInfo::CopyFrom(const FriendInfoResponse_PlayerInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FriendInfoResponse_PlayerInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000003f) != 0x0000003f) return false;

  return true;
}

void FriendInfoResponse_PlayerInfo::Swap(FriendInfoResponse_PlayerInfo* other) {
  if (other != this) {
    std::swap(frienduuid_, other->frienduuid_);
    std::swap(friendname_, other->friendname_);
    std::swap(gamescore_, other->gamescore_);
    std::swap(money_, other->money_);
    std::swap(headicon_, other->headicon_);
    std::swap(state_, other->state_);
    email_.Swap(&other->email_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string FriendInfoResponse_PlayerInfo::GetTypeName() const {
  return "message.FriendInfoResponse.PlayerInfo";
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int FriendInfoResponse::kFriendListFieldNumber;
const int FriendInfoResponse::kEnemyListFieldNumber;
#endif  // !_MSC_VER

FriendInfoResponse::FriendInfoResponse()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void FriendInfoResponse::InitAsDefaultInstance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friendlist_ = const_cast< ::message::FriendInfoResponse_PlayerInfoList*>(
      ::message::FriendInfoResponse_PlayerInfoList::internal_default_instance());
#else
  friendlist_ = const_cast< ::message::FriendInfoResponse_PlayerInfoList*>(&::message::FriendInfoResponse_PlayerInfoList::default_instance());
#endif
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  enemylist_ = const_cast< ::message::FriendInfoResponse_PlayerInfoList*>(
      ::message::FriendInfoResponse_PlayerInfoList::internal_default_instance());
#else
  enemylist_ = const_cast< ::message::FriendInfoResponse_PlayerInfoList*>(&::message::FriendInfoResponse_PlayerInfoList::default_instance());
#endif
}

FriendInfoResponse::FriendInfoResponse(const FriendInfoResponse& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void FriendInfoResponse::SharedCtor() {
  _cached_size_ = 0;
  friendlist_ = NULL;
  enemylist_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FriendInfoResponse::~FriendInfoResponse() {
  SharedDtor();
}

void FriendInfoResponse::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
    delete friendlist_;
    delete enemylist_;
  }
}

void FriendInfoResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const FriendInfoResponse& FriendInfoResponse::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_FriendInfo_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_FriendInfo_2eproto();
#endif
  return *default_instance_;
}

FriendInfoResponse* FriendInfoResponse::default_instance_ = NULL;

FriendInfoResponse* FriendInfoResponse::New() const {
  return new FriendInfoResponse;
}

void FriendInfoResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_friendlist()) {
      if (friendlist_ != NULL) friendlist_->::message::FriendInfoResponse_PlayerInfoList::Clear();
    }
    if (has_enemylist()) {
      if (enemylist_ != NULL) enemylist_->::message::FriendInfoResponse_PlayerInfoList::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool FriendInfoResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .message.FriendInfoResponse.PlayerInfoList friendList = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_friendlist()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_enemyList;
        break;
      }

      // optional .message.FriendInfoResponse.PlayerInfoList enemyList = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_enemyList:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_enemylist()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FriendInfoResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .message.FriendInfoResponse.PlayerInfoList friendList = 1;
  if (has_friendlist()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      1, this->friendlist(), output);
  }

  // optional .message.FriendInfoResponse.PlayerInfoList enemyList = 2;
  if (has_enemylist()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      2, this->enemylist(), output);
  }

}

int FriendInfoResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .message.FriendInfoResponse.PlayerInfoList friendList = 1;
    if (has_friendlist()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->friendlist());
    }

    // optional .message.FriendInfoResponse.PlayerInfoList enemyList = 2;
    if (has_enemylist()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->enemylist());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FriendInfoResponse::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const FriendInfoResponse*>(&from));
}

void FriendInfoResponse::MergeFrom(const FriendInfoResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_friendlist()) {
      mutable_friendlist()->::message::FriendInfoResponse_PlayerInfoList::MergeFrom(from.friendlist());
    }
    if (from.has_enemylist()) {
      mutable_enemylist()->::message::FriendInfoResponse_PlayerInfoList::MergeFrom(from.enemylist());
    }
  }
}

void FriendInfoResponse::CopyFrom(const FriendInfoResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FriendInfoResponse::IsInitialized() const {

  if (has_friendlist()) {
    if (!this->friendlist().IsInitialized()) return false;
  }
  if (has_enemylist()) {
    if (!this->enemylist().IsInitialized()) return false;
  }
  return true;
}

void FriendInfoResponse::Swap(FriendInfoResponse* other) {
  if (other != this) {
    std::swap(friendlist_, other->friendlist_);
    std::swap(enemylist_, other->enemylist_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string FriendInfoResponse::GetTypeName() const {
  return "message.FriendInfoResponse";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)
