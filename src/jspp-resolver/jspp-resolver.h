///
/// \file    jspp-resolver.h
/// \brief   jspp解析层实现类
///
/// \author  shaonge@gmail.com
/// \date    10:47 PM 1/29/18
///

#ifndef IMCHAT_JSPP_RESOLVER_H
#define IMCHAT_JSPP_RESOLVER_H

#include "rcf-idl.h"
#include "resolver-interface.h"
#include "rpc-server-capability.h"
#include "rpc-sync-client-capability.h"

#include <jsoncpp/json/json.h>

class JsppResolver : public ResolverInterface {
  public:
    JsppResolver(uint16_t server_port) : server_(server_port) {}

  public:
    void raw_byte_stream_accept(const std::vector<uint8_t> &byte_stream) override;
    void message_accept_resolver(const MessageProtocol &msgp) override;

    void connect_to_server(const std::string &server_ip, uint16_t server_port);
    void service_start() {
        server_().bind<I_ResolverInterface>(*this);
        server_().start();
        pause();
        server_().stop();
    }

  private:
    void json_to_message_(const Json::Value &value, MessageProtocol &msgp);
    void json_to_presence_(const Json::Value &value, MessageProtocol &msgp);
    void json_to_service_(const Json::Value &value, MessageProtocol &msgp);
    void message_to_json_(const MessageProtocol &msgp, Json::Value &value);
    void presence_to_json_(const MessageProtocol &msgp, Json::Value &value);
    void service_to_json_(const MessageProtocol &msgp, Json::Value &value);

  private:
    Json::Reader reader_;
    Json::Value root_;
    RPCServerCapability server_;
    RPCSyncClientCapability<I_ServerInterface> message_server_client_;
};

#endif // IMCHAT_JSPP_RESOLVER_H
