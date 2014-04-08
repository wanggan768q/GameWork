// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GameSearchStrength.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "GameSearchStrength.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace message {

void protobuf_ShutdownFile_GameSearchStrength_2eproto() {
  delete GameSearchStrengthRequest::default_instance_;
  delete GameSearchStrengthResponse::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_GameSearchStrength_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_GameSearchStrength_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  GameSearchStrengthRequest::default_instance_ = new GameSearchStrengthRequest();
  GameSearchStrengthResponse::default_instance_ = new GameSearchStrengthResponse();
  GameSearchStrengthRequest::default_instance_->InitAsDefaultInstance();
  GameSearchStrengthResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_GameSearchStrength_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_GameSearchStrength_2eproto_once_);
void protobuf_AddDesc_GameSearchStrength_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_GameSearchStrength_2eproto_once_,
                 &protobuf_AddDesc_GameSearchStrength_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_GameSearchStrength_2eproto {
  StaticDescriptorInitializer_GameSearchStrength_2eproto() {
    protobuf_AddDesc_GameSearchStrength_2eproto();
  }
} static_descriptor_initializer_GameSearchStrength_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

GameSearchStrengthRequest::GameSearchStrengthRequest()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void GameSearchStrengthRequest::InitAsDefaultInstance() {
}

GameSearchStrengthRequest::GameSearchStrengthRequest(const GameSearchStrengthRequest& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void GameSearchStrengthRequest::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GameSearchStrengthRequest::~GameSearchStrengthRequest() {
  SharedDtor();
}

void GameSearchStrengthRequest::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void GameSearchStrengthRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const GameSearchStrengthRequest& GameSearchStrengthRequest::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_GameSearchStrength_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_GameSearchStrength_2eproto();
#endif
  return *default_instance_;
}

GameSearchStrengthRequest* GameSearchStrengthRequest::default_instance_ = NULL;

GameSearchStrengthRequest* GameSearchStrengthRequest::New() const {
  return new GameSearchStrengthRequest;
}

void GameSearchStrengthRequest::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool GameSearchStrengthRequest::MergePartialFromCodedStream(
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

void GameSearchStrengthRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
}

int GameSearchStrengthRequest::ByteSize() const {
  int total_size = 0;

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GameSearchStrengthRequest::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const GameSearchStrengthRequest*>(&from));
}

void GameSearchStrengthRequest::MergeFrom(const GameSearchStrengthRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
}

void GameSearchStrengthRequest::CopyFrom(const GameSearchStrengthRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GameSearchStrengthRequest::IsInitialized() const {

  return true;
}

void GameSearchStrengthRequest::Swap(GameSearchStrengthRequest* other) {
  if (other != this) {
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string GameSearchStrengthRequest::GetTypeName() const {
  return "message.GameSearchStrengthRequest";
}


// ===================================================================

#ifndef _MSC_VER
const int GameSearchStrengthResponse::kStrengthFieldNumber;
const int GameSearchStrengthResponse::kSecondsFieldNumber;
#endif  // !_MSC_VER

GameSearchStrengthResponse::GameSearchStrengthResponse()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void GameSearchStrengthResponse::InitAsDefaultInstance() {
}

GameSearchStrengthResponse::GameSearchStrengthResponse(const GameSearchStrengthResponse& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void GameSearchStrengthResponse::SharedCtor() {
  _cached_size_ = 0;
  strength_ = 0;
  seconds_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GameSearchStrengthResponse::~GameSearchStrengthResponse() {
  SharedDtor();
}

void GameSearchStrengthResponse::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void GameSearchStrengthResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const GameSearchStrengthResponse& GameSearchStrengthResponse::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_GameSearchStrength_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_GameSearchStrength_2eproto();
#endif
  return *default_instance_;
}

GameSearchStrengthResponse* GameSearchStrengthResponse::default_instance_ = NULL;

GameSearchStrengthResponse* GameSearchStrengthResponse::New() const {
  return new GameSearchStrengthResponse;
}

void GameSearchStrengthResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    strength_ = 0;
    seconds_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool GameSearchStrengthResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 strength = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &strength_)));
          set_has_strength();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_seconds;
        break;
      }

      // optional int32 seconds = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_seconds:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &seconds_)));
          set_has_seconds();
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

void GameSearchStrengthResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 strength = 1;
  if (has_strength()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->strength(), output);
  }

  // optional int32 seconds = 2;
  if (has_seconds()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->seconds(), output);
  }

}

int GameSearchStrengthResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 strength = 1;
    if (has_strength()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->strength());
    }

    // optional int32 seconds = 2;
    if (has_seconds()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->seconds());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GameSearchStrengthResponse::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const GameSearchStrengthResponse*>(&from));
}

void GameSearchStrengthResponse::MergeFrom(const GameSearchStrengthResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_strength()) {
      set_strength(from.strength());
    }
    if (from.has_seconds()) {
      set_seconds(from.seconds());
    }
  }
}

void GameSearchStrengthResponse::CopyFrom(const GameSearchStrengthResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GameSearchStrengthResponse::IsInitialized() const {

  return true;
}

void GameSearchStrengthResponse::Swap(GameSearchStrengthResponse* other) {
  if (other != this) {
    std::swap(strength_, other->strength_);
    std::swap(seconds_, other->seconds_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string GameSearchStrengthResponse::GetTypeName() const {
  return "message.GameSearchStrengthResponse";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace message

// @@protoc_insertion_point(global_scope)
