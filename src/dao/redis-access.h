///
/// \file    redis-access.h
/// \brief   Redis访问辅助类
///
/// \author  shaonge@gmail.com
/// \date    11:20 PM 1/7/18
///

#ifndef IMCHAT_REDIS_ACCESS_H
#define IMCHAT_REDIS_ACCESS_H

#include <hiredis/hiredis.h>

#include <boost/noncopyable.hpp>

#include <memory>
#include <optional>
#include <string>

class RedisAccesser : boost::noncopyable {
  public:
    RedisAccesser() : RedisAccesser("127.0.0.1", 6379){};

    RedisAccesser(const std::string &hostname, uint16_t port);

    ~RedisAccesser() { redisFree(redis_context_); }

    bool keyDel(const std::string &key);

    bool keyExists(const std::string &key);

    bool hashExists(const std::string &hash_key, const std::string &hash_field);

    bool hashAdd(const std::string &hash_key, const std::string &hash_field,
                 const std::string &field_value);

    bool hashEdit(const std::string &hash_key, const std::string &hash_field,
                  const std::string &field_value);

    bool hashDel(const std::string &hash_key, const std::string &hash_field);

    std::optional<std::string> hashGet(const std::string &hash_key, const std::string &hash_field);

  private:
    long long int _hashSet(const std::string &hash_key, const std::string &hash_field,
                           const std::string &field_value);

  private:
    redisContext *redis_context_ = nullptr;

    std::string hostname_;
    uint16_t port_;
};

#endif // IMCHAT_REDIS_ACCESS_H
