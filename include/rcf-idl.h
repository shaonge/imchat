///
/// \file    rcf-idl.h
/// \brief   RCF接口描述头文件，注意本文件包含具有外部链接属性的如全局函数之类的定义，
///          故不可同时包含在同一程序的不同编译单元里
///
/// \author  shaonge@gmail.com
/// \date    10:38 PM 1/29/18
///

#ifndef IMCHAT_RCF_IDL_H
#define IMCHAT_RCF_IDL_H

#include "message-protocol.h"
#include "rcf-serialize.h"

#include <RCF/RCF.hpp>
#include <SF/vector.hpp>

RCF_BEGIN(I_ServerInterface, "I_ServerInterface")
    RCF_METHOD_V1(void, message_accept_server, const MessageProtocol &)
RCF_END(I_ServerInterface)

RCF_BEGIN(I_ResolverInterface, "I_ResolverInterface")
    RCF_METHOD_V1(void, message_accept_resolver, const MessageProtocol &)
    RCF_METHOD_V1(void, raw_byte_stream_accept, const std::vector<uint8_t> &)
RCF_END(I_ResolverInterface)

#endif // IMCHAT_RCF_IDL_H
