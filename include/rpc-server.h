#ifndef IMCHAT_RPC_SERVER_H
#define IMCHAT_RPC_SERVER_H

#include <rest_rpc/server.hpp>

class RPCServer {
  private:
    using server_t = timax::rpc::server<timax::rpc::msgpack_codec>;

  public:
    RPCServer(uint16_t port) : port_(port), server_t(port, 1) {}

  private:
    server_t server_;
    uint16_t port_;
};

#endif // IMCHAT_RPC_SERVER_H
