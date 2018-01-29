#ifndef IMCHAT_RPC_SERVER_CAPABILITY_H
#define IMCHAT_RPC_SERVER_CAPABILITY_H

#include <RCF/RCF.hpp>

class RPCServerCapability {
  public:
    RPCServerCapability(uint16_t port) : port_(port), server_(RCF::TcpEndpoint(port)) {}
    RCF::RcfServer &operator()() { return server_; }

  private:
    static inline RCF::RcfInitDeinit rcf_init;

  private:
    RCF::RcfServer server_;
    uint16_t port_;
};

#endif // IMCHAT_RPC_SERVER_CAPABILITY_H
