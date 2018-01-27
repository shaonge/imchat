#ifndef IMCHAT_MESSAGE_SERVER_IMPLEMENT_H
#define IMCHAT_MESSAGE_SERVER_IMPLEMENT_H

#include "rpc-client.h"
#include "rpc-server.h"
#include "server-interface.h"

class MessageServer : public ServerInterface, public RPCServer, public RPCClient {
  public:
    MessageServer(uint16_t server_port, const std::string &connect_server_ip,
                  uint16_t connect_server_port)
        : RPCServer(server_port), RPCClient(connect_server_ip, connect_server_port) {}

  public:
    void message_accept_server(const MessageProtocol &msgp) override;
};

#endif // IMCHAT_MESSAGE_SERVER_IMPLEMENT_H
