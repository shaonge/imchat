///
/// \file    redis-access.cpp
/// \brief
///
/// \author  shaonge@gmail.com
/// \date    4:21 PM 1/8/18
///

#include "redis-access.h"

class RedisReplyDeleter {
public:
    void operator()(redisReply *ptr) noexcept {
        freeReplyObject(ptr);
    }
};

RedisAccesser::RedisAccesser() : RedisAccesser("127.0.0.1", 6379) {}

RedisAccesser::RedisAccesser(const std::string &hostname, uint16_t port) : hostname_(hostname), port_(port) {
    redis_reply_ = std::shared_ptr<redisReply>(nullptr, RedisReplyDeleter{});

    redis_key_ = std::string("user_ip");

    struct timeval timeout
            = {1, 500000};
    redis_context_ = redisConnectWithTimeout(hostname_.c_str(), port_, timeout);
    if (redis_context_ == NULL || redis_context_->err) {
        if (redis_context_) {
            redisFree(redis_context_);
        }

        redis_context_ = nullptr;
    }
}

long long int RedisAccesser::hashSet(const long long int &id, const std::string &ip_addr) {
    std::string id_str = std::to_string(id);

    redisReply *reply = (redisReply *) redisCommand(this->redis_context_, "HSET %s %s %s", redis_key_.c_str(),
                                                    id_str.c_str(), ip_addr.c_str());

    redis_reply_.reset(reply);
    if (redis_reply_->type == REDIS_REPLY_INTEGER) {
        return redis_reply_->integer;
    }
    return -1;
}

bool RedisAccesser::hashDel(const long long int &id){
    bool res = false;
    std::string id_str = std::to_string(id);

    redisReply* reply = (redisReply*)redisCommand(this->redis_context_,"HDEL %s %s",redis_key_.c_str(),id_str.c_str());

    redis_reply_.reset(reply);
    if(redis_reply_->type == REDIS_REPLY_INTEGER){
        if(redis_reply_->integer == 1){
            res = true;
        }
    }
    return res;
}

bool RedisAccesser::hashAdd(const long long int &id, const std::string &ip_addr) {
    if (hashSet(id, ip_addr) == 1) {
        return true;
    } else {
        return false;
    }
}

bool RedisAccesser::hashEdit(const long long int &id, const std::string &ip_addr) {
    if (hashSet(id, ip_addr) == 0) {
        return true;
    } else {
        return false;
    }
}

std::optional<std::string> RedisAccesser::hashGetValue(const long long int &id) {
    std::string id_str = std::to_string(id);
    std::string value;

    redisReply *reply = (redisReply *) redisCommand(this->redis_context_, "HGET %s %s", redis_key_.c_str(), id_str.c_str());

    redis_reply_.reset(reply);
    if (redis_reply_->type == REDIS_REPLY_STRING) {
        return redis_reply_->str;
    } else if (redis_reply_->type == REDIS_REPLY_NIL) {
        return {};
    }
}