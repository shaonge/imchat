#ifndef IMCHAT_MESSAGE_PROTOCOL_H
#define IMCHAT_MESSAGE_PROTOCOL_H

#include <map>

enum class ProtocolType : int { MESSAGE, PRECENCE, SERVICE };

enum class MessageType : int { DEFAULT, CHAT, GROUPCHAT, ERROR };

enum class ServiceType : int { GET, RESULT, SET, ERROR };

enum class PrecenceType : int {
    PROBE,
    AVAILABLE,
    UNAVAILABLE,
    SUBSCRIBE,
    UNSUBSCRIBE,
    SUBSCRIBED,
    UNSUBSCRIBED,
    ERROR
};

struct ErrorType {
    uint16_t error_code;
    std::string error_msg;
};

using ArgsType = std::map<std::string, std::string>;
using ResultType = std::map<std::string, std::string>;

struct MessageProtocol {
    ProtocolType protocol_type;
    union {
        MessageType message_type;
        PrecenceType precence_type;
        ServiceType service_type;
    };
    std::string from;
    std::string to;
    uint64_t id;
    std::string ns;
    union {
        ArgsType args;
        ResultType result;
        std::string body;
        ErrorType error;
    };
};

#endif // IMCHAT_MESSAGE_PROTOCOL_H
