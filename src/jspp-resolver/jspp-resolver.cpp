#include "jspp-resolver.h"

void JsppResolver::raw_byte_stream_accept(const std::vector<uint8_t> &byte_stream) {
    std::string jdoc(reinterpret_cast<const char *>(byte_stream.data()), byte_stream.size());
    if (!reader_.parse(jdoc, root_, false) || !root_.isObject()) {
        return;
    }

    const Json::Value &protocol_type = root_["jspp"];

    if (protocol_type.asString() == "message") {
        json_to_message_(root_);
    } else if (protocol_type.asString() == "precence") {
        json_to_precence_(root_);
    } else if (protocol_type.asString() == "service") {
        json_to_service_(root_);
    }
}

void JsppResolver::message_accept_resolver(const MessageProtocol &msgp) {}

void JsppResolver::json_to_message_(const Json::Value &value) {
    const Json::Value &message = value["message"];
    if (!message.isObject()) {
        return;
    }

    MessageProtocol msgp;
    msgp.protocol_type = ProtocolType::MESSAGE;
    msgp.from = message["from"].asString();
    msgp.to = message["to"].asString();

    const Json::Value &type = message["type"];
    if (type.asString() == "chat") {
        msgp.type = MessageType::CHAT;
        msgp.id = message["id"].asUInt64();
        msgp.payload = message["body"].asString();
    } else if (type.asString() == "groupchat") {
        msgp.type = MessageType::GROUPCHAT;
    } else if (type.asString() == "error") {
        msgp.type = MessageType::ERROR;
    } else {
        return;
    }

    client_().message_accept_server(msgp);
}

void JsppResolver::json_to_precence_(const Json::Value &value) {
    Json::Value precence = value["precence"];
    if (!precence.isObject()) {
        return;
    }
}

void JsppResolver::json_to_service_(const Json::Value &value) {
    Json::Value service = value["service"];
    if (!service.isObject()) {
        return;
    }
}

void JsppResolver::message_to_json(const MessageProtocol &msgp, const Json::Value &value) {
    if (msgp.protocol_type != ProtocolType::MESSAGE) {
        return;
    }

    value["type"] = "message";
}

void JsppResolver::precence_to_json(const MessageProtocol &msgp, const Json::Value &value) {}

void JsppResolver::service_to_json(const MessageProtocol &msgp, const Json::Value &value) {}

int main() {
    JsppResolver jr(8000, "127.0.0.1", 9000);
    jr.service_start();
}
