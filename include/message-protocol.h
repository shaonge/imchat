///
/// \file    message-protocol.h
/// \brief   通信协议jspp的内存（二进制）表示形式
///
/// \author  shaonge@gmail.com
/// \date    10:37 PM 1/29/18
///

#ifndef IMCHAT_MESSAGE_PROTOCOL_H
#define IMCHAT_MESSAGE_PROTOCOL_H

#include <boost/variant.hpp>

#include <cstring>
#include <map>

enum class ProtocolType : int { MESSAGE, PRECENCE, SERVICE };

enum class MessageType : int { CHAT, GROUPCHAT, ERROR };

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
using BodyType = std::string;

struct MessageProtocol {
    ProtocolType protocol_type;
    boost::variant<MessageType, PrecenceType, ServiceType> type;
    std::string from;
    std::string to;
    uint64_t id;
    std::string ns;
    boost::variant<ArgsType, ResultType, BodyType, ErrorType> payload;
};

#endif // IMCHAT_MESSAGE_PROTOCOL_H
