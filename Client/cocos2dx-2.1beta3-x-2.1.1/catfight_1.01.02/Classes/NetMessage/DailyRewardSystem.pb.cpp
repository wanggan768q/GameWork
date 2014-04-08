// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DailyRewardSystem.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "DailyRewardSystem.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_DailyRewardSystem_2eproto() {
  delete DailyRewardSystemData::default_instance_;
  delete DailyRewardSystemData_DailyReward::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_DailyRewardSystem_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_DailyRewardSystem_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  DailyRewardSystemData::default_instance_ = new DailyRewardSystemData();
  DailyRewardSystemData_DailyReward::default_instance_ = new DailyRewardSystemData_DailyReward();
  DailyRewardSystemData::default_instance_->InitAsDefaultInstance();
  DailyRewardSystemData_DailyReward::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_DailyRewardSystem_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_DailyRewardSystem_2eproto_once_);
void protobuf_AddDesc_DailyRewardSystem_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_DailyRewardSystem_2eproto_once_,
                 &protobuf_AddDesc_DailyRewardSystem_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_DailyRewardSystem_2eproto {
  StaticDescriptorInitializer_DailyRewardSystem_2eproto() {
    protobuf_AddDesc_DailyRewardSystem_2eproto();
  }
} static_descriptor_initializer_DailyRewardSystem_2eproto_;
#endif

// ===================================================================

bool DailyRewardSystemData_DailyReward_ClaimedState_IsValid(int value) {
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
const DailyRewardSystemData_DailyReward_ClaimedState DailyRewardSystemData_DailyReward::ClaimedState_Unclaimed;
const DailyRewardSystemData_DailyReward_ClaimedState DailyRewardSystemData_DailyReward::ClaimedState_Claimed;
const DailyRewardSystemData_DailyReward_ClaimedState DailyRewardSystemData_DailyReward::ClaimedState_AllowClaimed;
const DailyRewardSystemData_DailyReward_ClaimedState DailyRewardSystemData_DailyReward::ClaimedState_MIN;
const DailyRewardSystemData_DailyReward_ClaimedState DailyRewardSystemData_DailyReward::ClaimedState_MAX;
const int DailyRewardSystemData_DailyReward::ClaimedState_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int DailyRewardSystemData_DailyReward::kDayIDFieldNumber;
const int DailyRewardSystemData_DailyReward::kGoldFieldNumber;
const int DailyRewardSystemData_DailyReward::kStateFieldNumber;
#endif  // !_MSC_VER

DailyRewardSystemData_DailyReward::DailyRewardSystemData_DailyReward()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void DailyRewardSystemData_DailyReward::InitAsDefaultInstance() {
}

DailyRewardSystemData_DailyReward::DailyRewardSystemData_DailyReward(const DailyRewardSystemData_DailyReward& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void DailyRewardSystemData_DailyReward::SharedCtor() {
  _cached_size_ = 0;
  dayid_ = 0;
  gold_ = 0;
  state_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DailyRewardSystemData_DailyReward::~DailyRewardSystemData_DailyReward() {
  SharedDtor();
}

void DailyRewardSystemData_DailyReward::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void DailyRewardSystemData_DailyReward::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const DailyRewardSystemData_DailyReward& DailyRewardSystemData_DailyReward::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_DailyRewardSystem_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_DailyRewardSystem_2eproto();
#endif
  return *default_instance_;
}

DailyRewardSystemData_DailyReward* DailyRewardSystemData_DailyReward::default_instance_ = NULL;

DailyRewardSystemData_DailyReward* DailyRewardSystemData_DailyReward::New() const {
  return new DailyRewardSystemData_DailyReward;
}

void DailyRewardSystemData_DailyReward::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    dayid_ = 0;
    gold_ = 0;
    state_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool DailyRewardSystemData_DailyReward::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 dayID = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &dayid_)));
          set_has_dayid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_gold;
        break;
      }

      // required int32 gold = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_gold:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &gold_)));
          set_has_gold();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_state;
        break;
      }

      // required .message.DailyRewardSystemData.DailyReward.ClaimedState state = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_state:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::message::DailyRewardSystemData_DailyReward_ClaimedState_IsValid(value)) {
            set_state(static_cast< ::message::DailyRewardSystemData_DailyReward_ClaimedState >(value));
          }
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

void DailyRewardSystemData_DailyReward::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 dayID = 1;
  if (has_dayid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->dayid(), output);
  }

  // required int32 gold = 2;
  if (has_gold()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->gold(), output);
  }

  // required .message.DailyRewardSystemData.DailyReward.ClaimedState state = 3;
  if (has_state()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      3, this->state(), output);
  }

}

int DailyRewardSystemData_DailyReward::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 dayID = 1;
    if (has_dayid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->dayid());
    }

    // required int32 gold = 2;
    if (has_gold()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->gold());
    }

    // required .message.DailyRewardSystemData.DailyReward.ClaimedState state = 3;
    if (has_state()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->state());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void DailyRewardSystemData_DailyReward::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const DailyRewardSystemData_DailyReward*>(&from));
}

void DailyRewardSystemData_DailyReward::MergeFrom(const DailyRewardSystemData_DailyReward& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_dayid()) {
      set_dayid(from.dayid());
    }
    if (from.has_gold()) {
      set_gold(from.gold());
    }
    if (from.has_state()) {
      set_state(from.state());
    }
  }
}

void DailyRewardSystemData_DailyReward::CopyFrom(const DailyRewardSystemData_DailyReward& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DailyRewardSystemData_DailyReward::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void DailyRewardSystemData_DailyReward::Swap(DailyRewardSystemData_DailyReward* other) {
  if (other != this) {
    std::swap(dayid_, other->dayid_);
    std::swap(gold_, other->gold_);
    std::swap(state_, other->state_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string DailyRewardSystemData_DailyReward::GetTypeName() const {
  return "message.DailyRewardSystemData.DailyReward";
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int DailyRewardSystemData::kDailyRewardListFieldNumber;
#endif  // !_MSC_VER

DailyRewardSystemData::DailyRewardSystemData()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void DailyRewardSystemData::InitAsDefaultInstance() {
}

DailyRewardSystemData::DailyRewardSystemData(const DailyRewardSystemData& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void DailyRewardSystemData::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DailyRewardSystemData::~DailyRewardSystemData() {
  SharedDtor();
}

void DailyRewardSystemData::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void DailyRewardSystemData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const DailyRewardSystemData& DailyRewardSystemData::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_DailyRewardSystem_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_DailyRewardSystem_2eproto();
#endif
  return *default_instance_;
}

DailyRewardSystemData* DailyRewardSystemData::default_instance_ = NULL;

DailyRewardSystemData* DailyRewardSystemData::New() const {
  return new DailyRewardSystemData;
}

void DailyRewardSystemData::Clear() {
  dailyrewardlist_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool DailyRewardSystemData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .message.DailyRewardSystemData.DailyReward dailyRewardList = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_dailyRewardList:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_dailyrewardlist()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_dailyRewardList;
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

void DailyRewardSystemData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .message.DailyRewardSystemData.DailyReward dailyRewardList = 1;
  for (int i = 0; i < this->dailyrewardlist_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      1, this->dailyrewardlist(i), output);
  }

}

int DailyRewardSystemData::ByteSize() const {
  int total_size = 0;

  // repeated .message.DailyRewardSystemData.DailyReward dailyRewardList = 1;
  total_size += 1 * this->dailyrewardlist_size();
  for (int i = 0; i < this->dailyrewardlist_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->dailyrewardlist(i));
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void DailyRewardSystemData::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const DailyRewardSystemData*>(&from));
}

void DailyRewardSystemData::MergeFrom(const DailyRewardSystemData& from) {
  GOOGLE_CHECK_NE(&from, this);
  dailyrewardlist_.MergeFrom(from.dailyrewardlist_);
}

void DailyRewardSystemData::CopyFrom(const DailyRewardSystemData& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DailyRewardSystemData::IsInitialized() const {

  for (int i = 0; i < dailyrewardlist_size(); i++) {
    if (!this->dailyrewardlist(i).IsInitialized()) return false;
  }
  return true;
}

void DailyRewardSystemData::Swap(DailyRewardSystemData* other) {
  if (other != this) {
    dailyrewardlist_.Swap(&other->dailyrewardlist_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string DailyRewardSystemData::GetTypeName() const {
  return "message.DailyRewardSystemData";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)
