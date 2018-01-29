#ifndef IMCHAT_RESOLVER_INTERFACE_H
#define IMCHAT_RESOLVER_INTERFACE_H

#include "message-protocol.h"

#include <vector>

class ResolverInterface {
    virtual void raw_byte_stream_accept(const std::vector<uint8_t> &byte_stream) = 0;
    virtual void message_accept_resolver(const MessageProtocol &msgp) = 0;
};

#endif // IMCHAT_RESOLVER_INTERFACE_H
