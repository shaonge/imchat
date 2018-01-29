#ifndef IMCHAT_MESSAGE_SERVER_H
#define IMCHAT_MESSAGE_SERVER_H

#include "dao-interface.h"
#include "rcf-idl.h"
#include "rpc-server-capability.h"
#include "rpc-sync-client-capability.h"
#include "server-interface.h"

class MessageServer : public ServerInterface {
  public:
    MessageServer(uint16_t server_port, const std::string &connect_server_ip,
                  uint16_t connect_server_port);
    ~MessageServer() { delete dao_handler_; };

  public:
    void message_accept_server(const MessageProtocol &msgp) override;

    void service_start() {
        server_().bind<I_ServerInterface>(*this);
        server_().start();
        pause();
    }

  private:
    bool basic_check_(const MessageProtocol &msgp);
    bool chat_check_(const MessageProtocol &msgp);
    void chat_message_transmit_(const std::string &from, const std::string &to, uint64_t id,
                                const std::string &msg_body);

  private:
    DaoInterface *dao_handler_ = nullptr;
    RPCServerCapability server_;
    RPCSyncClientCapability<I_ResolverInterface> client_;
};

#endif // IMCHAT_MESSAGE_SERVER_H
