#ifndef IMCHAT_RCF_SERIALIZE_H
#define IMCHAT_RCF_SERIALIZE_H

#include "message-protocol.h"

#include <SF/map.hpp>
#include <SF/string.hpp>
#include <SF/variant.hpp>

SF_SERIALIZE_ENUM_CLASS(ProtocolType, int)
SF_SERIALIZE_ENUM_CLASS(MessageType, int)
SF_SERIALIZE_ENUM_CLASS(PrecenceType, int)
SF_SERIALIZE_ENUM_CLASS(ServiceType, int)

namespace SF {

void serialize(SF::Archive &ar, ErrorType &et) { ar & et.error_code & et.error_msg; }

void serialize(SF::Archive &ar, MessageProtocol &mp) {
    ar & mp.protocol_type & mp.type & mp.from & mp.to & mp.id & mp.ns & mp.payload;
}

} // namespace SF

#endif // IMCHAT_RCF_SERIALIZE_H
