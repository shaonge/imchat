#ifndef IMCHAT_IMCHAT_SERVER_INTERFACE_H
#define IMCHAT_IMCHAT_SERVER_INTERFACE_H

#include "message-protocol.h"

class ServerInterface {
  public:
    virtual void message_accept_server(const MessageProtocol &msgp) = 0;
};

#endif // IMCHAT_IMCHAT_SERVER_INTERFACE_H
