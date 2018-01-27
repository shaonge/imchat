#ifndef IMCHAT_IMCHAT_SERVER_INTERFACE_H
#define IMCHAT_IMCHAT_SERVER_INTERFACE_H

#include "jspp.h"

class ServerInterface {
  public:
    virtual void message_accept(const Message &msg) = 0;
};

#endif // IMCHAT_IMCHAT_SERVER_INTERFACE_H
