// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rpc.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace muduo {

namespace {

const ::google::protobuf::Descriptor* RpcMessage_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RpcMessage_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* MessageType_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* ErrorCode_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rpc_2eproto() {
  protobuf_AddDesc_rpc_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rpc.proto");
  GOOGLE_CHECK(file != NULL);
  RpcMessage_descriptor_ = file->message_type(0);
  static const int RpcMessage_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMessage, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMessage, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMessage, service_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMessage, method_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMessage, request_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMessage, response_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMessage, error_),
  };
  RpcMessage_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RpcMessage_descriptor_,
      RpcMessage::default_instance_,
      RpcMessage_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMessage, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMessage, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RpcMessage));
  MessageType_descriptor_ = file->enum_type(0);
  ErrorCode_descriptor_ = file->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rpc_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RpcMessage_descriptor_, &RpcMessage::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rpc_2eproto() {
  delete RpcMessage::default_instance_;
  delete RpcMessage_reflection_;
}

void protobuf_AddDesc_rpc_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\trpc.proto\022\005muduo\"\237\001\n\nRpcMessage\022 \n\004typ"
    "e\030\001 \002(\0162\022.muduo.MessageType\022\n\n\002id\030\002 \002(\006\022"
    "\017\n\007service\030\003 \001(\t\022\016\n\006method\030\004 \001(\t\022\017\n\007requ"
    "est\030\005 \001(\014\022\020\n\010response\030\006 \001(\014\022\037\n\005error\030\007 \001"
    "(\0162\020.muduo.ErrorCode*3\n\013MessageType\022\013\n\007R"
    "EQUEST\020\001\022\014\n\010RESPONSE\020\002\022\t\n\005ERROR\020\003*f\n\tErr"
    "orCode\022\017\n\013WRONG_PROTO\020\001\022\016\n\nNO_SERVICE\020\002\022"
    "\r\n\tNO_METHOD\020\003\022\023\n\017INVALID_REQUEST\020\004\022\024\n\020I"
    "NVALID_RESPONSE\020\005B\034\n\020muduo1.rpc.protoB\010R"
    "pcProto", 367);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rpc.proto", &protobuf_RegisterTypes);
  RpcMessage::default_instance_ = new RpcMessage();
  RpcMessage::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rpc_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rpc_2eproto {
  StaticDescriptorInitializer_rpc_2eproto() {
    protobuf_AddDesc_rpc_2eproto();
  }
} static_descriptor_initializer_rpc_2eproto_;

const ::google::protobuf::EnumDescriptor* MessageType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MessageType_descriptor_;
}
bool MessageType_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* ErrorCode_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ErrorCode_descriptor_;
}
bool ErrorCode_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      return true;
    default:
      return false;
  }
}


// ===================================================================

const ::std::string RpcMessage::_default_service_;
const ::std::string RpcMessage::_default_method_;
const ::std::string RpcMessage::_default_request_;
const ::std::string RpcMessage::_default_response_;
#ifndef _MSC_VER
const int RpcMessage::kTypeFieldNumber;
const int RpcMessage::kIdFieldNumber;
const int RpcMessage::kServiceFieldNumber;
const int RpcMessage::kMethodFieldNumber;
const int RpcMessage::kRequestFieldNumber;
const int RpcMessage::kResponseFieldNumber;
const int RpcMessage::kErrorFieldNumber;
#endif  // !_MSC_VER

RpcMessage::RpcMessage()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void RpcMessage::InitAsDefaultInstance() {
}

RpcMessage::RpcMessage(const RpcMessage& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void RpcMessage::SharedCtor() {
  _cached_size_ = 0;
  type_ = 1;
  id_ = GOOGLE_ULONGLONG(0);
  service_ = const_cast< ::std::string*>(&_default_service_);
  method_ = const_cast< ::std::string*>(&_default_method_);
  request_ = const_cast< ::std::string*>(&_default_request_);
  response_ = const_cast< ::std::string*>(&_default_response_);
  error_ = 1;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RpcMessage::~RpcMessage() {
  SharedDtor();
}

void RpcMessage::SharedDtor() {
  if (service_ != &_default_service_) {
    delete service_;
  }
  if (method_ != &_default_method_) {
    delete method_;
  }
  if (request_ != &_default_request_) {
    delete request_;
  }
  if (response_ != &_default_response_) {
    delete response_;
  }
  if (this != default_instance_) {
  }
}

void RpcMessage::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RpcMessage::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RpcMessage_descriptor_;
}

const RpcMessage& RpcMessage::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rpc_2eproto();  return *default_instance_;
}

RpcMessage* RpcMessage::default_instance_ = NULL;

RpcMessage* RpcMessage::New() const {
  return new RpcMessage;
}

void RpcMessage::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    type_ = 1;
    id_ = GOOGLE_ULONGLONG(0);
    if (_has_bit(2)) {
      if (service_ != &_default_service_) {
        service_->clear();
      }
    }
    if (_has_bit(3)) {
      if (method_ != &_default_method_) {
        method_->clear();
      }
    }
    if (_has_bit(4)) {
      if (request_ != &_default_request_) {
        request_->clear();
      }
    }
    if (_has_bit(5)) {
      if (response_ != &_default_response_) {
        response_->clear();
      }
    }
    error_ = 1;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RpcMessage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .muduo.MessageType type = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (muduo::MessageType_IsValid(value)) {
            set_type(static_cast< muduo::MessageType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(17)) goto parse_id;
        break;
      }
      
      // required fixed64 id = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_FIXED64>(
                 input, &id_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_service;
        break;
      }
      
      // optional string service = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_service:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_service()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->service().data(), this->service().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_method;
        break;
      }
      
      // optional string method = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_method:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_method()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->method().data(), this->method().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_request;
        break;
      }
      
      // optional bytes request = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_request:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_request()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_response;
        break;
      }
      
      // optional bytes response = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_response:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_response()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_error;
        break;
      }
      
      // optional .muduo.ErrorCode error = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_error:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (muduo::ErrorCode_IsValid(value)) {
            set_error(static_cast< muduo::ErrorCode >(value));
          } else {
            mutable_unknown_fields()->AddVarint(7, value);
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
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void RpcMessage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .muduo.MessageType type = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->type(), output);
  }
  
  // required fixed64 id = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteFixed64(2, this->id(), output);
  }
  
  // optional string service = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->service().data(), this->service().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->service(), output);
  }
  
  // optional string method = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->method().data(), this->method().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->method(), output);
  }
  
  // optional bytes request = 5;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      5, this->request(), output);
  }
  
  // optional bytes response = 6;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      6, this->response(), output);
  }
  
  // optional .muduo.ErrorCode error = 7;
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      7, this->error(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* RpcMessage::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .muduo.MessageType type = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->type(), target);
  }
  
  // required fixed64 id = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFixed64ToArray(2, this->id(), target);
  }
  
  // optional string service = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->service().data(), this->service().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->service(), target);
  }
  
  // optional string method = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->method().data(), this->method().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->method(), target);
  }
  
  // optional bytes request = 5;
  if (_has_bit(4)) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        5, this->request(), target);
  }
  
  // optional bytes response = 6;
  if (_has_bit(5)) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        6, this->response(), target);
  }
  
  // optional .muduo.ErrorCode error = 7;
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      7, this->error(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int RpcMessage::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .muduo.MessageType type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }
    
    // required fixed64 id = 2;
    if (has_id()) {
      total_size += 1 + 8;
    }
    
    // optional string service = 3;
    if (has_service()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->service());
    }
    
    // optional string method = 4;
    if (has_method()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->method());
    }
    
    // optional bytes request = 5;
    if (has_request()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->request());
    }
    
    // optional bytes response = 6;
    if (has_response()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->response());
    }
    
    // optional .muduo.ErrorCode error = 7;
    if (has_error()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->error());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void RpcMessage::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RpcMessage* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RpcMessage*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RpcMessage::MergeFrom(const RpcMessage& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_type(from.type());
    }
    if (from._has_bit(1)) {
      set_id(from.id());
    }
    if (from._has_bit(2)) {
      set_service(from.service());
    }
    if (from._has_bit(3)) {
      set_method(from.method());
    }
    if (from._has_bit(4)) {
      set_request(from.request());
    }
    if (from._has_bit(5)) {
      set_response(from.response());
    }
    if (from._has_bit(6)) {
      set_error(from.error());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RpcMessage::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RpcMessage::CopyFrom(const RpcMessage& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RpcMessage::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void RpcMessage::Swap(RpcMessage* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    std::swap(id_, other->id_);
    std::swap(service_, other->service_);
    std::swap(method_, other->method_);
    std::swap(request_, other->request_);
    std::swap(response_, other->response_);
    std::swap(error_, other->error_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RpcMessage::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RpcMessage_descriptor_;
  metadata.reflection = RpcMessage_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace muduo

// @@protoc_insertion_point(global_scope)
