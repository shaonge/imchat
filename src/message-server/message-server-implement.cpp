#include "message-server-implement.h"

#include "dao-interface.h"

void MessageServer::message_accept(const Message &msg) {}

static void acceptor(const Message &msg) {
    switch (msg.message_type) {
    case MessageType::DEFAULT:
        break;
    case MessageType::CHAT:
        break;
    case MessageType::GROUPCHAT:
        break;
    case MessageType::ERROR:
        break;
    }
}

static void message_transmit(const std::string &from, const std::string &to,
                             const std::string &msg) {}
