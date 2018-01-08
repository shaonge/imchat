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

    struct timeval timeout = {1, 500000};
    redis_context_ = redisConnectWithTimeout(hostname_.c_str(), port_, timeout);
    if (redis_context_ == NULL || redis_context_->err) {
        if (redis_context_) {
            redisFree(redis_context_);
        }

        redis_context_ = nullptr;
    }
}

