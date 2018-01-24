///
/// \file    redis-access.cpp
/// \brief
///
/// \author  shaonge@gmail.com
/// \date    4:21 PM 1/8/18
///

#include "redis-access.h"
#include "imchat.h"

RedisAccesser::RedisAccesser(const std::string &hostname, uint16_t port)
    : hostname_(hostname), port_(port) {
    struct timeval timeout = {1, 500000};
    redis_context_ = redisConnectWithTimeout(hostname_.c_str(), port_, timeout);
    if (redis_context_ == NULL || redis_context_->err) {
        if (redis_context_) {
            redisFree(redis_context_);
        }

        redis_context_ = nullptr;
    }
    IMCHAT_ASSERT(redis_context_);
}

long long int RedisAccesser::_hashSet(const std::string &hash_key, const std::string &hash_field,
                                      const std::string &field_value) {
    void *vr = redisCommand(this->redis_context_, "HSET %s %s %s", hash_key.c_str(),
                            hash_field.c_str(), field_value.c_str());
    if (!vr) {
        return -1;
    }
    auto reply = static_cast<redisReply *>(vr);
    long long int result = -1;
    if (reply->type == REDIS_REPLY_INTEGER) {
        result = reply->integer;
    }

    freeReplyObject(reply);
    return result;
}

bool RedisAccesser::keyDel(const std::string &key) {
    void *vr = redisCommand(this->redis_context_, "DEL %s", key.c_str());
    if (!vr) {
        return false;
    }
    auto reply = static_cast<redisReply *>(vr);
    bool result = false;
    if (reply->type == REDIS_REPLY_INTEGER && reply->integer > 0) {
        result = true;
    }

    freeReplyObject(reply);
    return result;
}

bool RedisAccesser::keyExists(const std::string &key) {
    void *vr = redisCommand(this->redis_context_, "EXISTS %s", key.c_str());
    if (!vr) {
        return false;
    }
    auto reply = static_cast<redisReply *>(vr);
    bool result = false;
    if (reply->type == REDIS_REPLY_INTEGER && reply->integer > 0) {
        result = true;
    }

    freeReplyObject(reply);
    return result;
}

bool RedisAccesser::hashExists(const std::string &hash_key, const std::string &hash_field) {
    void *vr =
        redisCommand(this->redis_context_, "HEXISTS %s %s", hash_key.c_str(), hash_field.c_str());
    if (!vr) {
        return false;
    }
    auto reply = static_cast<redisReply *>(vr);
    bool result = false;
    if (reply->type == REDIS_REPLY_INTEGER && reply->integer > 0) {
        result = true;
    }

    freeReplyObject(reply);
    return result;
}

bool RedisAccesser::hashAdd(const std::string &hash_key, const std::string &hash_field,
                            const std::string &field_value) {
    if (hashExists(hash_key, hash_field)) {
        return false;
    }
    return (_hashSet(hash_key, hash_field, field_value) == 1);
}

bool RedisAccesser::hashEdit(const std::string &hash_key, const std::string &hash_field,
                             const std::string &field_value) {
    if (!hashExists(hash_key, hash_field)) {
        return false;
    }
    return (_hashSet(hash_key, hash_field, field_value) == 0);
}

bool RedisAccesser::hashDel(const std::string &hash_key, const std::string &hash_field) {
    void *vr =
        redisCommand(this->redis_context_, "HDEL %s %s", hash_key.c_str(), hash_field.c_str());
    if (!vr) {
        return false;
    }
    auto reply = static_cast<redisReply *>(vr);
    bool result = false;
    if (reply->type == REDIS_REPLY_INTEGER && reply->integer == 1) {
        result = true;
    }

    freeReplyObject(reply);
    return result;
}

std::optional<std::string> RedisAccesser::hashGet(const std::string &hash_key,
                                                  const std::string &hash_field) {
    void *vr =
        redisCommand(this->redis_context_, "HGET %s %s", hash_key.c_str(), hash_field.c_str());
    if (!vr) {
        return std::optional<std::string>();
    }
    auto reply = static_cast<redisReply *>(vr);

    if (reply->type != REDIS_REPLY_STRING) {
        freeReplyObject(reply);
        return std::optional<std::string>();
    }

    std::string rstr(reply->str);
    freeReplyObject(reply);
    return std::optional<std::string>(std::move(rstr));
}
