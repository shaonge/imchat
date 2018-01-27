///
/// \file    redis-access.h
/// \brief   Redis访问辅助类
/// 
/// \author  shaonge@gmail.com
/// \date    11:20 PM 1/7/18
///

#ifndef IMCHAT_REDIS_ACCESS_H
#define IMCHAT_REDIS_ACCESS_H

#include <boost/noncopyable.hpp>
#include <hiredis/hiredis.h>
#include <optional>
#include <string>
#include <memory>

class RedisAccesser : boost::noncopyable {
public:
    RedisAccesser();

    RedisAccesser(const std::string &hostname, uint16_t port);

    ~RedisAccesser() {
        redisFree(redis_context_);
    }


    bool hashAdd(const long long int &id, const std::string &ip_addr);

    bool hashEdit(const long long int &id, const std::string &ip_addr);

    bool hashDel(const long long int &id);

    std::optional<std::string> hashGetValue(const long long int &id);

private:
    long long int hashSet(const long long int &id, const std::string &ip_addr);


private:
    redisContext *redis_context_ = nullptr;
    std::string redis_key_;
    std::shared_ptr<redisReply> redis_reply_;

    std::string hostname_;
    uint16_t port_;
};

#endif //IMCHAT_REDIS_ACCESS_H
