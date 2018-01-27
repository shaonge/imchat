#ifndef IMCHAT_RPC_CLIENT_H
#define IMCHAT_RPC_CLIENT_H

#include <rest_rpc/client.hpp>

class RPCClient {
  private:
    using sync_client_t = timax::rpc::sync_client<timax::rpc::msgpack_codec>;

  public:
    RPCClient(const std::string &server_ip, uint16_t server_port_)
        : server_ip_(server_ip), server_port_(server_port) {}

  private:
    sync_client_t client_;
    std::string server_ip_;
    uint16_t server_port_;
};

#endif // IMCHAT_RPC_CLIENT_H
