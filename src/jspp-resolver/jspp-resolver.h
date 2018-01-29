#ifndef IMCHAT_JSPP_RESOLVER_H
#define IMCHAT_JSPP_RESOLVER_H

#include "rcf-idl.h"
#include "resolver-interface.h"
#include "rpc-server-capability.h"
#include "rpc-sync-client-capability.h"

#include <jsoncpp/json/json.h>

class JsppResolver : public ResolverInterface {
  public:
    JsppResolver(uint16_t server_port, const std::string &connect_server_ip,
                 uint16_t connect_server_port)
        : server_(server_port), client_(connect_server_ip, connect_server_port) {}

  public:
    void raw_byte_stream_accept(const std::vector<uint8_t> &byte_stream) override;
    void message_accept_resolver(const MessageProtocol &msgp) override;

    void service_start() {
        server_().bind<I_ResolverInterface>(*this);
        server_().start();
        pause();
    }

  private:
    void json_to_message_(const Json::Value &value);
    void json_to_precence_(const Json::Value &value);
    void json_to_service_(const Json::Value &value);
    void message_to_json(const MessageProtocol& msgp, const Json::Value& value);
    void precence_to_json(const MessageProtocol& msgp, const Json::Value& value);
    void service_to_json(const MessageProtocol& msgp, const Json::Value& value);

private:
    Json::Reader reader_;
    Json::Value root_;
    RPCServerCapability server_;
    RPCSyncClientCapability<I_ServerInterface> client_;
};

#endif // IMCHAT_JSPP_RESOLVER_H
