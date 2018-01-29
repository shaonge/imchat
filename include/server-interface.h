///
/// \file    server-interface.h
/// \brief   业务层接口定义
/// 
/// \author  shaonge@gmail.com
/// \date    10:43 PM 1/29/18
///

#ifndef IMCHAT_IMCHAT_SERVER_INTERFACE_H
#define IMCHAT_IMCHAT_SERVER_INTERFACE_H

#include "message-protocol.h"

class ServerInterface {
  public:
    virtual void message_accept_server(const MessageProtocol &msgp) = 0;
};

#endif // IMCHAT_IMCHAT_SERVER_INTERFACE_H
