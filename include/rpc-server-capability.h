///
/// \file    rpc-server-capability.h
/// \brief   RCF服务端类定义
///
/// \author  shaonge@gmail.com
/// \date    10:46 PM 1/29/18
///

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
