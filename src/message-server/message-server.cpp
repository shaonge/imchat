#include "message-server.h"

#include "../dao/dao-implement.h"
#include "server-configure.h"

void MessageServer::message_accept_server(const MessageProtocol &msgp) {
    if (!basic_check_(msgp)) {
        return;
    }

    switch (boost::get<MessageType>(msgp.type)) {
    case MessageType::CHAT:
        if (!chat_check_(msgp)) {
            return;
        }
        chat_message_transmit_(msgp.from, msgp.to, msgp.id, boost::get<BodyType>(msgp.payload));
        break;
    case MessageType::GROUPCHAT:
        break;
    case MessageType::ERROR:
        break;
    }
}

MessageServer::MessageServer(uint16_t server_port, const std::string &connect_server_ip,
                             uint16_t connect_server_port)
    : server_(server_port), resolver_client_(connect_server_ip, connect_server_port) {
    dao_handler_ = new DaoImplement();
    IMCHAT_ASSERT(dao_handler_);
}

bool MessageServer::basic_check_(const MessageProtocol &msgp) {
    return msgp.protocol_type == ProtocolType::MESSAGE;
}

bool MessageServer::chat_check_(const MessageProtocol &msgp) {
    if (boost::get<MessageType>(msgp.type) != MessageType::CHAT) {
        return false;
    }

    if (!dao_handler_->isUserExisting(msgp.from) || !dao_handler_->isUserExisting(msgp.to)) {
        return false;
    }

    if (!dao_handler_->isOnesBuddy(msgp.from, msgp.to)) {
        return false;
    }

    return dao_handler_->isUserOnline(msgp.to);
}

void MessageServer::chat_message_transmit_(const std::string &from, const std::string &to,
                                           uint64_t id, const std::string &msg_body) {
    MessageProtocol send_msg;
    send_msg.protocol_type = ProtocolType::MESSAGE;
    send_msg.type = MessageType::CHAT;
    send_msg.from = from;
    send_msg.to = to;
    send_msg.id = id;
    send_msg.payload = msg_body;
    resolver_client_().message_accept_resolver(send_msg);
}

int main() {
    MessageServer ms(MESSAGE_SERVER_PORT, RESOLVER_SERVER_IP, RESOLVER_SERVER_PORT);
    ms.service_start();
}