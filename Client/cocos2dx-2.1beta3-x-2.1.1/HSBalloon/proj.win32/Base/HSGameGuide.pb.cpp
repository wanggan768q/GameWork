// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "HSGameGuide.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_HSGameGuide_2eproto() {
  delete GameGuide::default_instance_;
  delete GameGuide_Guide::default_instance_;
  delete GameGuide_Guide_Rect::default_instance_;
  delete GameGuide_Guide_Point::default_instance_;
}

void protobuf_AddDesc_HSGameGuide_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  GameGuide::default_instance_ = new GameGuide();
  GameGuide_Guide::default_instance_ = new GameGuide_Guide();
  GameGuide_Guide_Rect::default_instance_ = new GameGuide_Guide_Rect();
  GameGuide_Guide_Point::default_instance_ = new GameGuide_Guide_Point();
  GameGuide::default_instance_->InitAsDefaultInstance();
  GameGuide_Guide::default_instance_->InitAsDefaultInstance();
  GameGuide_Guide_Rect::default_instance_->InitAsDefaultInstance();
  GameGuide_Guide_Point::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_HSGameGuide_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_HSGameGuide_2eproto {
  StaticDescriptorInitializer_HSGameGuide_2eproto() {
    protobuf_AddDesc_HSGameGuide_2eproto();
  }
} static_descriptor_initializer_HSGameGuide_2eproto_;


// ===================================================================

bool GameGuide_Guide_ModeType_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const GameGuide_Guide_ModeType GameGuide_Guide::ModeType_Round;
const GameGuide_Guide_ModeType GameGuide_Guide::ModeType_Rect;
const GameGuide_Guide_ModeType GameGuide_Guide::ModeType_MIN;
const GameGuide_Guide_ModeType GameGuide_Guide::ModeType_MAX;
const int GameGuide_Guide::ModeType_ARRAYSIZE;
#endif  // _MSC_VER
bool GameGuide_Guide_TouchType_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const GameGuide_Guide_TouchType GameGuide_Guide::TouchType_leak;
const GameGuide_Guide_TouchType GameGuide_Guide::TouchType_intercept;
const GameGuide_Guide_TouchType GameGuide_Guide::TouchType_MIN;
const GameGuide_Guide_TouchType GameGuide_Guide::TouchType_MAX;
const int GameGuide_Guide::TouchType_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int GameGuide_Guide_Rect::kXFieldNumber;
const int GameGuide_Guide_Rect::kYFieldNumber;
const int GameGuide_Guide_Rect::kWFieldNumber;
const int GameGuide_Guide_Rect::kHFieldNumber;
#endif  // !_MSC_VER

GameGuide_Guide_Rect::GameGuide_Guide_Rect()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void GameGuide_Guide_Rect::InitAsDefaultInstance() {
}

GameGuide_Guide_Rect::GameGuide_Guide_Rect(const GameGuide_Guide_Rect& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void GameGuide_Guide_Rect::SharedCtor() {
  _cached_size_ = 0;
  x_ = 0;
  y_ = 0;
  w_ = 0;
  h_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GameGuide_Guide_Rect::~GameGuide_Guide_Rect() {
  SharedDtor();
}

void GameGuide_Guide_Rect::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GameGuide_Guide_Rect::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const GameGuide_Guide_Rect& GameGuide_Guide_Rect::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_HSGameGuide_2eproto();  return *default_instance_;
}

GameGuide_Guide_Rect* GameGuide_Guide_Rect::default_instance_ = NULL;

GameGuide_Guide_Rect* GameGuide_Guide_Rect::New() const {
  return new GameGuide_Guide_Rect;
}

void GameGuide_Guide_Rect::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    x_ = 0;
    y_ = 0;
    w_ = 0;
    h_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool GameGuide_Guide_Rect::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required float x = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &x_)));
          set_has_x();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_y;
        break;
      }
      
      // required float y = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_y:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &y_)));
          set_has_y();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(29)) goto parse_w;
        break;
      }
      
      // required float w = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_w:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &w_)));
          set_has_w();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(37)) goto parse_h;
        break;
      }
      
      // required float h = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_h:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &h_)));
          set_has_h();
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

void GameGuide_Guide_Rect::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required float x = 1;
  if (has_x()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(1, this->x(), output);
  }
  
  // required float y = 2;
  if (has_y()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->y(), output);
  }
  
  // required float w = 3;
  if (has_w()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(3, this->w(), output);
  }
  
  // required float h = 4;
  if (has_h()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(4, this->h(), output);
  }
  
}

int GameGuide_Guide_Rect::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required float x = 1;
    if (has_x()) {
      total_size += 1 + 4;
    }
    
    // required float y = 2;
    if (has_y()) {
      total_size += 1 + 4;
    }
    
    // required float w = 3;
    if (has_w()) {
      total_size += 1 + 4;
    }
    
    // required float h = 4;
    if (has_h()) {
      total_size += 1 + 4;
    }
    
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GameGuide_Guide_Rect::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const GameGuide_Guide_Rect*>(&from));
}

void GameGuide_Guide_Rect::MergeFrom(const GameGuide_Guide_Rect& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_x()) {
      set_x(from.x());
    }
    if (from.has_y()) {
      set_y(from.y());
    }
    if (from.has_w()) {
      set_w(from.w());
    }
    if (from.has_h()) {
      set_h(from.h());
    }
  }
}

void GameGuide_Guide_Rect::CopyFrom(const GameGuide_Guide_Rect& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GameGuide_Guide_Rect::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;
  
  return true;
}

void GameGuide_Guide_Rect::Swap(GameGuide_Guide_Rect* other) {
  if (other != this) {
    std::swap(x_, other->x_);
    std::swap(y_, other->y_);
    std::swap(w_, other->w_);
    std::swap(h_, other->h_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string GameGuide_Guide_Rect::GetTypeName() const {
  return "message.GameGuide.Guide.Rect";
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int GameGuide_Guide_Point::kXFieldNumber;
const int GameGuide_Guide_Point::kYFieldNumber;
#endif  // !_MSC_VER

GameGuide_Guide_Point::GameGuide_Guide_Point()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void GameGuide_Guide_Point::InitAsDefaultInstance() {
}

GameGuide_Guide_Point::GameGuide_Guide_Point(const GameGuide_Guide_Point& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void GameGuide_Guide_Point::SharedCtor() {
  _cached_size_ = 0;
  x_ = 0;
  y_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GameGuide_Guide_Point::~GameGuide_Guide_Point() {
  SharedDtor();
}

void GameGuide_Guide_Point::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GameGuide_Guide_Point::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const GameGuide_Guide_Point& GameGuide_Guide_Point::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_HSGameGuide_2eproto();  return *default_instance_;
}

GameGuide_Guide_Point* GameGuide_Guide_Point::default_instance_ = NULL;

GameGuide_Guide_Point* GameGuide_Guide_Point::New() const {
  return new GameGuide_Guide_Point;
}

void GameGuide_Guide_Point::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    x_ = 0;
    y_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool GameGuide_Guide_Point::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required float x = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &x_)));
          set_has_x();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_y;
        break;
      }
      
      // required float y = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_y:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &y_)));
          set_has_y();
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

void GameGuide_Guide_Point::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required float x = 1;
  if (has_x()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(1, this->x(), output);
  }
  
  // required float y = 2;
  if (has_y()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->y(), output);
  }
  
}

int GameGuide_Guide_Point::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required float x = 1;
    if (has_x()) {
      total_size += 1 + 4;
    }
    
    // required float y = 2;
    if (has_y()) {
      total_size += 1 + 4;
    }
    
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GameGuide_Guide_Point::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const GameGuide_Guide_Point*>(&from));
}

void GameGuide_Guide_Point::MergeFrom(const GameGuide_Guide_Point& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_x()) {
      set_x(from.x());
    }
    if (from.has_y()) {
      set_y(from.y());
    }
  }
}

void GameGuide_Guide_Point::CopyFrom(const GameGuide_Guide_Point& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GameGuide_Guide_Point::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void GameGuide_Guide_Point::Swap(GameGuide_Guide_Point* other) {
  if (other != this) {
    std::swap(x_, other->x_);
    std::swap(y_, other->y_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string GameGuide_Guide_Point::GetTypeName() const {
  return "message.GameGuide.Guide.Point";
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int GameGuide_Guide::kIdFieldNumber;
const int GameGuide_Guide::kModeTypeFieldNumber;
const int GameGuide_Guide::kRectFieldNumber;
const int GameGuide_Guide::kPointListFieldNumber;
const int GameGuide_Guide::kDiameterFieldNumber;
const int GameGuide_Guide::kMultipleFieldNumber;
const int GameGuide_Guide::kDescribePosFieldNumber;
const int GameGuide_Guide::kTouchTypeFieldNumber;
const int GameGuide_Guide::kDescribeFieldNumber;
#endif  // !_MSC_VER

GameGuide_Guide::GameGuide_Guide()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void GameGuide_Guide::InitAsDefaultInstance() {
  describepos_ = const_cast< ::message::GameGuide_Guide_Point*>(&::message::GameGuide_Guide_Point::default_instance());
}

GameGuide_Guide::GameGuide_Guide(const GameGuide_Guide& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void GameGuide_Guide::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0;
  modetype_ = 1;
  describepos_ = NULL;
  touchtype_ = 1;
  describe_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GameGuide_Guide::~GameGuide_Guide() {
  SharedDtor();
}

void GameGuide_Guide::SharedDtor() {
  if (describe_ != &::google::protobuf::internal::kEmptyString) {
    delete describe_;
  }
  if (this != default_instance_) {
    delete describepos_;
  }
}

void GameGuide_Guide::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const GameGuide_Guide& GameGuide_Guide::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_HSGameGuide_2eproto();  return *default_instance_;
}

GameGuide_Guide* GameGuide_Guide::default_instance_ = NULL;

GameGuide_Guide* GameGuide_Guide::New() const {
  return new GameGuide_Guide;
}

void GameGuide_Guide::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = 0;
    modetype_ = 1;
    if (has_describepos()) {
      if (describepos_ != NULL) describepos_->::message::GameGuide_Guide_Point::Clear();
    }
    touchtype_ = 1;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (has_describe()) {
      if (describe_ != &::google::protobuf::internal::kEmptyString) {
        describe_->clear();
      }
    }
  }
  rect_.Clear();
  pointlist_.Clear();
  diameter_.Clear();
  multiple_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool GameGuide_Guide::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_modeType;
        break;
      }
      
      // required .message.GameGuide.Guide.ModeType modeType = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_modeType:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::message::GameGuide_Guide_ModeType_IsValid(value)) {
            set_modetype(static_cast< ::message::GameGuide_Guide_ModeType >(value));
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_rect;
        break;
      }
      
      // repeated .message.GameGuide.Guide.Rect rect = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_rect:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_rect()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_rect;
        if (input->ExpectTag(34)) goto parse_pointList;
        break;
      }
      
      // repeated .message.GameGuide.Guide.Point pointList = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_pointList:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_pointlist()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_pointList;
        if (input->ExpectTag(45)) goto parse_diameter;
        break;
      }
      
      // repeated float diameter = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_diameter:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 1, 45, input, this->mutable_diameter())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, this->mutable_diameter())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(45)) goto parse_diameter;
        if (input->ExpectTag(53)) goto parse_multiple;
        break;
      }
      
      // repeated float multiple = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_multiple:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 1, 53, input, this->mutable_multiple())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, this->mutable_multiple())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(53)) goto parse_multiple;
        if (input->ExpectTag(58)) goto parse_describePos;
        break;
      }
      
      // optional .message.GameGuide.Guide.Point describePos = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_describePos:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_describepos()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_touchType;
        break;
      }
      
      // optional .message.GameGuide.Guide.TouchType touchType = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_touchType:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::message::GameGuide_Guide_TouchType_IsValid(value)) {
            set_touchtype(static_cast< ::message::GameGuide_Guide_TouchType >(value));
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(74)) goto parse_describe;
        break;
      }
      
      // optional string describe = 9 [default = ""];
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_describe:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_describe()));
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

void GameGuide_Guide::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->id(), output);
  }
  
  // required .message.GameGuide.Guide.ModeType modeType = 2;
  if (has_modetype()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->modetype(), output);
  }
  
  // repeated .message.GameGuide.Guide.Rect rect = 3;
  for (int i = 0; i < this->rect_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      3, this->rect(i), output);
  }
  
  // repeated .message.GameGuide.Guide.Point pointList = 4;
  for (int i = 0; i < this->pointlist_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      4, this->pointlist(i), output);
  }
  
  // repeated float diameter = 5;
  for (int i = 0; i < this->diameter_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(
      5, this->diameter(i), output);
  }
  
  // repeated float multiple = 6;
  for (int i = 0; i < this->multiple_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(
      6, this->multiple(i), output);
  }
  
  // optional .message.GameGuide.Guide.Point describePos = 7;
  if (has_describepos()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      7, this->describepos(), output);
  }
  
  // optional .message.GameGuide.Guide.TouchType touchType = 8;
  if (has_touchtype()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      8, this->touchtype(), output);
  }
  
  // optional string describe = 9 [default = ""];
  if (has_describe()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      9, this->describe(), output);
  }
  
}

int GameGuide_Guide::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->id());
    }
    
    // required .message.GameGuide.Guide.ModeType modeType = 2;
    if (has_modetype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->modetype());
    }
    
    // optional .message.GameGuide.Guide.Point describePos = 7;
    if (has_describepos()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->describepos());
    }
    
    // optional .message.GameGuide.Guide.TouchType touchType = 8;
    if (has_touchtype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->touchtype());
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional string describe = 9 [default = ""];
    if (has_describe()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->describe());
    }
    
  }
  // repeated .message.GameGuide.Guide.Rect rect = 3;
  total_size += 1 * this->rect_size();
  for (int i = 0; i < this->rect_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->rect(i));
  }
  
  // repeated .message.GameGuide.Guide.Point pointList = 4;
  total_size += 1 * this->pointlist_size();
  for (int i = 0; i < this->pointlist_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->pointlist(i));
  }
  
  // repeated float diameter = 5;
  {
    int data_size = 0;
    data_size = 4 * this->diameter_size();
    total_size += 1 * this->diameter_size() + data_size;
  }
  
  // repeated float multiple = 6;
  {
    int data_size = 0;
    data_size = 4 * this->multiple_size();
    total_size += 1 * this->multiple_size() + data_size;
  }
  
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GameGuide_Guide::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const GameGuide_Guide*>(&from));
}

void GameGuide_Guide::MergeFrom(const GameGuide_Guide& from) {
  GOOGLE_CHECK_NE(&from, this);
  rect_.MergeFrom(from.rect_);
  pointlist_.MergeFrom(from.pointlist_);
  diameter_.MergeFrom(from.diameter_);
  multiple_.MergeFrom(from.multiple_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_modetype()) {
      set_modetype(from.modetype());
    }
    if (from.has_describepos()) {
      mutable_describepos()->::message::GameGuide_Guide_Point::MergeFrom(from.describepos());
    }
    if (from.has_touchtype()) {
      set_touchtype(from.touchtype());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_describe()) {
      set_describe(from.describe());
    }
  }
}

void GameGuide_Guide::CopyFrom(const GameGuide_Guide& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GameGuide_Guide::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  for (int i = 0; i < rect_size(); i++) {
    if (!this->rect(i).IsInitialized()) return false;
  }
  for (int i = 0; i < pointlist_size(); i++) {
    if (!this->pointlist(i).IsInitialized()) return false;
  }
  if (has_describepos()) {
    if (!this->describepos().IsInitialized()) return false;
  }
  return true;
}

void GameGuide_Guide::Swap(GameGuide_Guide* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(modetype_, other->modetype_);
    rect_.Swap(&other->rect_);
    pointlist_.Swap(&other->pointlist_);
    diameter_.Swap(&other->diameter_);
    multiple_.Swap(&other->multiple_);
    std::swap(describepos_, other->describepos_);
    std::swap(touchtype_, other->touchtype_);
    std::swap(describe_, other->describe_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string GameGuide_Guide::GetTypeName() const {
  return "message.GameGuide.Guide";
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int GameGuide::kGuideListFieldNumber;
#endif  // !_MSC_VER

GameGuide::GameGuide()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void GameGuide::InitAsDefaultInstance() {
}

GameGuide::GameGuide(const GameGuide& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void GameGuide::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GameGuide::~GameGuide() {
  SharedDtor();
}

void GameGuide::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GameGuide::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const GameGuide& GameGuide::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_HSGameGuide_2eproto();  return *default_instance_;
}

GameGuide* GameGuide::default_instance_ = NULL;

GameGuide* GameGuide::New() const {
  return new GameGuide;
}

void GameGuide::Clear() {
  guidelist_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool GameGuide::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .message.GameGuide.Guide guideList = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_guideList:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_guidelist()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_guideList;
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

void GameGuide::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .message.GameGuide.Guide guideList = 1;
  for (int i = 0; i < this->guidelist_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      1, this->guidelist(i), output);
  }
  
}

int GameGuide::ByteSize() const {
  int total_size = 0;
  
  // repeated .message.GameGuide.Guide guideList = 1;
  total_size += 1 * this->guidelist_size();
  for (int i = 0; i < this->guidelist_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->guidelist(i));
  }
  
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GameGuide::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const GameGuide*>(&from));
}

void GameGuide::MergeFrom(const GameGuide& from) {
  GOOGLE_CHECK_NE(&from, this);
  guidelist_.MergeFrom(from.guidelist_);
}

void GameGuide::CopyFrom(const GameGuide& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GameGuide::IsInitialized() const {
  
  for (int i = 0; i < guidelist_size(); i++) {
    if (!this->guidelist(i).IsInitialized()) return false;
  }
  return true;
}

void GameGuide::Swap(GameGuide* other) {
  if (other != this) {
    guidelist_.Swap(&other->guidelist_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string GameGuide::GetTypeName() const {
  return "message.GameGuide";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)