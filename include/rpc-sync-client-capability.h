///
/// \file    rpc-sync-client-capability.h
/// \brief   RCF异步客户端类定义
///
/// \author  shaonge@gmail.com
/// \date    10:44 PM 1/29/18
///

#ifndef IMCHAT_RPC_SYNC_CLIENT_CAPABILITY_H
#define IMCHAT_RPC_SYNC_CLIENT_CAPABILITY_H

#include <RCF/RCF.hpp>

template <typename T> class RPCSyncClientCapability {
  public:
    RPCSyncClientCapability() : server_port_() {}
    RPCSyncClientCapability(const std::string &server_ip, uint16_t server_port)
        : server_ip_(server_ip), server_port_(server_port),
          client_(RCF::TcpEndpoint(server_ip, server_port)) {}

    RcfClient<T> &operator()() { return client_; }

  private:
    static inline RCF::RcfInitDeinit rcf_init;

  private:
    RcfClient<T> client_;
    std::string server_ip_;
    uint16_t server_port_;
};

#endif // IMCHAT_RPC_SYNC_CLIENT_CAPABILITY_H
