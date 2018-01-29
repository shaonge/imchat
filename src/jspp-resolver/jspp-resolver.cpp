#include "jspp-resolver.h"

#include "server-configure.h"

void JsppResolver::raw_byte_stream_accept(const std::vector<uint8_t> &byte_stream) {
    std::string jdoc(reinterpret_cast<const char *>(byte_stream.data()), byte_stream.size());
    if (!reader_.parse(jdoc, root_, false) || !root_.isObject()) {
        return;
    }

    MessageProtocol msgp;

    if (root_.isMember("message")) {
        json_to_message_(root_, msgp);
        message_server_client_().message_accept_server(msgp);
    } else if (root_.isMember("presence")) {
        json_to_presence_(root_, msgp);
    } else if (root_.isMember("service")) {
        json_to_service_(root_, msgp);
    } else {
    }
}

void JsppResolver::message_accept_resolver(const MessageProtocol &msgp) {}

void JsppResolver::json_to_message_(const Json::Value &value, MessageProtocol &msgp) {
    const Json::Value &message = value["message"];
    if (!message.isObject()) {
        return;
    }

    msgp.protocol_type = ProtocolType::MESSAGE;

    if (!message.isMember("from") || !message["from"].isString()) {
        return;
    }
    msgp.from = message["from"].asString();

    if (!message.isMember("to") || !message["to"].isString()) {
        return;
    }
    msgp.to = message["to"].asString();

    if (!message.isMember("type") || !message["type"].isString()) {
        return;
    }
    const Json::Value &type = message["type"];

    if (type.asString() == "chat") {
        msgp.type = MessageType::CHAT;

        if (message.isMember("id") && message["id"].isUInt64()) {
            msgp.id = message["id"].asUInt64();
        }

        if (message.isMember("body") && message["body"].isString()) {
            msgp.payload = message["body"].asString();
        }
    } else if (type.asString() == "groupchat") {
        msgp.type = MessageType::GROUPCHAT;
    } else if (type.asString() == "error") {
        msgp.type = MessageType::ERROR;
    } else {
    }
}

void JsppResolver::json_to_presence_(const Json::Value &value, MessageProtocol &msgp) {
    Json::Value precence = value["presence"];
    if (!precence.isObject()) {
        return;
    }
}

void JsppResolver::json_to_service_(const Json::Value &value, MessageProtocol &msgp) {
    const Json::Value &message = value["service"];
    if (!message.isObject()) {
        return;
    }

    msgp.protocol_type = ProtocolType::SERVICE;

    if (!message.isMember("from") || !message["from"].isString()) {
        return;
    }
    msgp.from = message["from"].asString();

    if (!message.isMember("to") || !message["to"].isString()) {
        return;
    }
    msgp.to = message["to"].asString();

    if (message.isMember("id") && message["id"].isUInt64()) {
        msgp.id = message["id"].asUInt64();
    }

    if (!message.isMember("ns") || !message["ns"].isString()) {
        return;
    }

    if (!message.isMember("type") || !message["type"].isString()) {
        return;
    }
    const Json::Value &type = message["type"];

    if (type.asString() == "get") {
        msgp.type = ServiceType::GET;

        if (message.isMember("args") && message["args"].isObject()) {
            const Json::Value &args = message["args"];
            /// 未完待续
        }
    } else if (type.asString() == "result") {
        msgp.type = ServiceType::RESULT;
    } else if (type.asString() == "set") {
        msgp.type = ServiceType::SET;
    } else if (type.asString() == "error") {
        msgp.type = ServiceType::ERROR;
    } else {
    }
}

void JsppResolver::message_to_json_(const MessageProtocol &msgp, Json::Value &value) {
    if (msgp.protocol_type != ProtocolType::MESSAGE) {
        return;
    }

    value.clear();
    value["message"] = Json::Value(Json::ValueType::objectValue);
    Json::Value &message = value["message"];

    message["from"] = msgp.from;
    message["to"] = msgp.to;
    message["id"] = msgp.id;
}

void JsppResolver::presence_to_json_(const MessageProtocol &msgp, Json::Value &value) {}

void JsppResolver::service_to_json_(const MessageProtocol &msgp, Json::Value &value) {}

void JsppResolver::connect_to_server(const std::string &server_ip, uint16_t server_port) {}

int main() {
    JsppResolver jr(RESOLVER_SERVER_PORT);
    jr.service_start();
}
