#include "message-server-implement.h"

#include "dao-interface.h"
#include "resolver-interface.h"

void MessageServer::message_accept_server(const MessageProtocol &msgp) {}

static void acceptor(const MessageProtocol &msgp) {
    switch (msgp.message_type) {
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
