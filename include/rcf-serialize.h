///
/// \file    rcf-serialize.h
/// \brief   RCF序列化头文件，注意本文件包含具有外部链接属性的如全局函数之类的定义，
///          故不可同时包含在同一程序的不同编译单元里
///
/// \author  shaonge@gmail.com
/// \date    10:38 PM 1/29/18
///

#ifndef IMCHAT_RCF_SERIALIZE_H
#define IMCHAT_RCF_SERIALIZE_H

#include "message-protocol.h"

#include <SF/map.hpp>
#include <SF/string.hpp>
#include <SF/variant.hpp>

SF_SERIALIZE_ENUM_CLASS(ProtocolType, int)
SF_SERIALIZE_ENUM_CLASS(MessageType, int)
SF_SERIALIZE_ENUM_CLASS(PrecenceType, int)
SF_SERIALIZE_ENUM_CLASS(ServiceType, int)

namespace SF {

void serialize(SF::Archive &ar, ErrorType &et) { ar & et.error_code & et.error_msg; }

void serialize(SF::Archive &ar, MessageProtocol &mp) {
    ar & mp.protocol_type & mp.type & mp.from & mp.to & mp.id & mp.ns & mp.payload;
}

} // namespace SF

#endif // IMCHAT_RCF_SERIALIZE_H
