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
