// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GameCacheData.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "GameCacheData.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_GameCacheData_2eproto() {
  delete GameCacheData::default_instance_;
  delete GameCacheData::_default_uid_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_GameCacheData_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_GameCacheData_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ::message::protobuf_AddDesc_UserInfo_2eproto();
  GameCacheData::_default_uid_ =
      new ::std::string("0", 1);
  GameCacheData::default_instance_ = new GameCacheData();
  GameCacheData::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_GameCacheData_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_GameCacheData_2eproto_once_);
void protobuf_AddDesc_GameCacheData_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_GameCacheData_2eproto_once_,
                 &protobuf_AddDesc_GameCacheData_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_GameCacheData_2eproto {
  StaticDescriptorInitializer_GameCacheData_2eproto() {
    protobuf_AddDesc_GameCacheData_2eproto();
  }
} static_descriptor_initializer_GameCacheData_2eproto_;
#endif

// ===================================================================

::std::string* GameCacheData::_default_uid_ = NULL;
#ifndef _MSC_VER
const int GameCacheData::kUidFieldNumber;
const int GameCacheData::kIMEIFieldNumber;
const int GameCacheData::kIsBackgroundMusicFieldNumber;
const int GameCacheData::kIsSoundFieldNumber;
const int GameCacheData::kFinishedAchievementIDFieldNumber;
const int GameCacheData::kUserInfoFieldNumber;
const int GameCacheData::kIsRunGameGuideFieldNumber;
const int GameCacheData::kNicknameFieldNumber;
const int GameCacheData::kIsSendNicknameFieldNumber;
#endif  // !_MSC_VER

GameCacheData::GameCacheData()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void GameCacheData::InitAsDefaultInstance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  userinfo_ = const_cast< ::message::UserBasicInfo*>(
      ::message::UserBasicInfo::internal_default_instance());
#else
  userinfo_ = const_cast< ::message::UserBasicInfo*>(&::message::UserBasicInfo::default_instance());
#endif
}

GameCacheData::GameCacheData(const GameCacheData& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void GameCacheData::SharedCtor() {
  _cached_size_ = 0;
  uid_ = const_cast< ::std::string*>(_default_uid_);
  imei_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  isbackgroundmusic_ = true;
  issound_ = true;
  userinfo_ = NULL;
  isrungameguide_ = true;
  nickname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  issendnickname_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GameCacheData::~GameCacheData() {
  SharedDtor();
}

void GameCacheData::SharedDtor() {
  if (uid_ != _default_uid_) {
    delete uid_;
  }
  if (imei_ != &::google::protobuf::internal::kEmptyString) {
    delete imei_;
  }
  if (nickname_ != &::google::protobuf::internal::kEmptyString) {
    delete nickname_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
    delete userinfo_;
  }
}

void GameCacheData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const GameCacheData& GameCacheData::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_GameCacheData_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_GameCacheData_2eproto();
#endif
  return *default_instance_;
}

GameCacheData* GameCacheData::default_instance_ = NULL;

GameCacheData* GameCacheData::New() const {
  return new GameCacheData;
}

void GameCacheData::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_uid()) {
      if (uid_ != _default_uid_) {
        uid_->assign(*_default_uid_);
      }
    }
    if (has_imei()) {
      if (imei_ != &::google::protobuf::internal::kEmptyString) {
        imei_->clear();
      }
    }
    isbackgroundmusic_ = true;
    issound_ = true;
    if (has_userinfo()) {
      if (userinfo_ != NULL) userinfo_->::message::UserBasicInfo::Clear();
    }
    isrungameguide_ = true;
    if (has_nickname()) {
      if (nickname_ != &::google::protobuf::internal::kEmptyString) {
        nickname_->clear();
      }
    }
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    issendnickname_ = false;
  }
  finishedachievementid_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool GameCacheData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string uid = 1 [default = "0"];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_uid()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_IMEI;
        break;
      }

      // optional string IMEI = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_IMEI:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_imei()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_isBackgroundMusic;
        break;
      }

      // optional bool isBackgroundMusic = 3 [default = true];
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_isBackgroundMusic:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &isbackgroundmusic_)));
          set_has_isbackgroundmusic();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_isSound;
        break;
      }

      // optional bool isSound = 4 [default = true];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_isSound:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &issound_)));
          set_has_issound();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_finishedAchievementID;
        break;
      }

      // repeated int32 finishedAchievementID = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_finishedAchievementID:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 1, 40, input, this->mutable_finishedachievementid())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, this->mutable_finishedachievementid())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_finishedAchievementID;
        if (input->ExpectTag(50)) goto parse_userInfo;
        break;
      }

      // optional .message.UserBasicInfo userInfo = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_userInfo:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_userinfo()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_isRunGameGuide;
        break;
      }

      // optional bool isRunGameGuide = 7 [default = true];
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_isRunGameGuide:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &isrungameguide_)));
          set_has_isrungameguide();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(66)) goto parse_nickname;
        break;
      }

      // optional string nickname = 8 [default = ""];
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_nickname:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_nickname()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_isSendNickname;
        break;
      }

      // optional bool isSendNickname = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_isSendNickname:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &issendnickname_)));
          set_has_issendnickname();
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

void GameCacheData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string uid = 1 [default = "0"];
  if (has_uid()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->uid(), output);
  }

  // optional string IMEI = 2;
  if (has_imei()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->imei(), output);
  }

  // optional bool isBackgroundMusic = 3 [default = true];
  if (has_isbackgroundmusic()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->isbackgroundmusic(), output);
  }

  // optional bool isSound = 4 [default = true];
  if (has_issound()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->issound(), output);
  }

  // repeated int32 finishedAchievementID = 5;
  for (int i = 0; i < this->finishedachievementid_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(
      5, this->finishedachievementid(i), output);
  }

  // optional .message.UserBasicInfo userInfo = 6;
  if (has_userinfo()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      6, this->userinfo(), output);
  }

  // optional bool isRunGameGuide = 7 [default = true];
  if (has_isrungameguide()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(7, this->isrungameguide(), output);
  }

  // optional string nickname = 8 [default = ""];
  if (has_nickname()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      8, this->nickname(), output);
  }

  // optional bool isSendNickname = 9;
  if (has_issendnickname()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(9, this->issendnickname(), output);
  }

}

int GameCacheData::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string uid = 1 [default = "0"];
    if (has_uid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->uid());
    }

    // optional string IMEI = 2;
    if (has_imei()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->imei());
    }

    // optional bool isBackgroundMusic = 3 [default = true];
    if (has_isbackgroundmusic()) {
      total_size += 1 + 1;
    }

    // optional bool isSound = 4 [default = true];
    if (has_issound()) {
      total_size += 1 + 1;
    }

    // optional .message.UserBasicInfo userInfo = 6;
    if (has_userinfo()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->userinfo());
    }

    // optional bool isRunGameGuide = 7 [default = true];
    if (has_isrungameguide()) {
      total_size += 1 + 1;
    }

    // optional string nickname = 8 [default = ""];
    if (has_nickname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->nickname());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional bool isSendNickname = 9;
    if (has_issendnickname()) {
      total_size += 1 + 1;
    }

  }
  // repeated int32 finishedAchievementID = 5;
  {
    int data_size = 0;
    for (int i = 0; i < this->finishedachievementid_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->finishedachievementid(i));
    }
    total_size += 1 * this->finishedachievementid_size() + data_size;
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GameCacheData::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const GameCacheData*>(&from));
}

void GameCacheData::MergeFrom(const GameCacheData& from) {
  GOOGLE_CHECK_NE(&from, this);
  finishedachievementid_.MergeFrom(from.finishedachievementid_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_uid()) {
      set_uid(from.uid());
    }
    if (from.has_imei()) {
      set_imei(from.imei());
    }
    if (from.has_isbackgroundmusic()) {
      set_isbackgroundmusic(from.isbackgroundmusic());
    }
    if (from.has_issound()) {
      set_issound(from.issound());
    }
    if (from.has_userinfo()) {
      mutable_userinfo()->::message::UserBasicInfo::MergeFrom(from.userinfo());
    }
    if (from.has_isrungameguide()) {
      set_isrungameguide(from.isrungameguide());
    }
    if (from.has_nickname()) {
      set_nickname(from.nickname());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_issendnickname()) {
      set_issendnickname(from.issendnickname());
    }
  }
}

void GameCacheData::CopyFrom(const GameCacheData& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GameCacheData::IsInitialized() const {

  if (has_userinfo()) {
    if (!this->userinfo().IsInitialized()) return false;
  }
  return true;
}

void GameCacheData::Swap(GameCacheData* other) {
  if (other != this) {
    std::swap(uid_, other->uid_);
    std::swap(imei_, other->imei_);
    std::swap(isbackgroundmusic_, other->isbackgroundmusic_);
    std::swap(issound_, other->issound_);
    finishedachievementid_.Swap(&other->finishedachievementid_);
    std::swap(userinfo_, other->userinfo_);
    std::swap(isrungameguide_, other->isrungameguide_);
    std::swap(nickname_, other->nickname_);
    std::swap(issendnickname_, other->issendnickname_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string GameCacheData::GetTypeName() const {
  return "message.GameCacheData";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)
