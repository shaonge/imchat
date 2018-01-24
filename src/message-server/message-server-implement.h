#ifndef IMCHAT_MESSAGE_SERVER_IMPLEMENT_H
#define IMCHAT_MESSAGE_SERVER_IMPLEMENT_H

#include "server-interface.h"

class MessageServer : public ServerInterface {
  public:
    void message_accept(const Message &msg);
};

#endif // IMCHAT_MESSAGE_SERVER_IMPLEMENT_H
