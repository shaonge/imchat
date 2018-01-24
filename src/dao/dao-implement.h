///
/// \file    easy-dao-implement.h
/// \brief   DAO层接口类的一个实现
///
/// \author  shaonge@gmail.com
/// \date    11:06 PM 1/7/18
///

#ifndef IMCHAT_DAO_IMPLEMENT_H
#define IMCHAT_DAO_IMPLEMENT_H

#include "dao-interface.h"
#include "imchat.h"
#include "mongodb-access.h"
#include "redis-access.h"

class DaoImplement : public DaoInterface {
  public:
    DaoImplement() : mongodb_(), redis_() { _init(); };

    explicit DaoImplement(const std::string &mongodb_ip_and_port)
        : mongodb_(mongodb_ip_and_port), redis_() {
        _init();
    }

    DaoImplement(const std::string &redis_host_name, uint16_t redis_port)
        : mongodb_(), redis_(redis_host_name, redis_port) {
        _init();
    }

    DaoImplement(const std::string &mongodb_ip_and_port, const std::string &redis_host_name,
                 uint16_t redis_port)
        : mongodb_(mongodb_ip_and_port), redis_(redis_host_name, redis_port) {
        _init();
    }

  public:
    bool isUserExisting(const std::string &user_name) override;

    bool isUserOnline(const std::string &user_name) override;

    std::optional<std::string> userJoinIP(const std::string &user_name) override;

    bool isOnesBuddy(const std::string &user_name, const std::string &buddy_name) override;

    std::optional<std::string> getUserInfo(const std::string &user_name,
                                           const std::string &field_name) override;

    bool addNewUser(const std::string &user_name) override;

    bool setUserOnline(const std::string &user_name, const std::string& ip_addr) override;

    bool addNewBuddy(const std::string &user_name, const std::string &buddy_name) override;

    bool setUserInfo(const std::string &user_name, const std::string &field_name,
                     const std::string &value) override;

    bool setUserInfoFromJson(const std::string &user_name, const std::string &json_str) override;

    bool destroyAllData() override;

  private:
    void _init();

  private:
    MongodbAccesser mongodb_;
    RedisAccesser redis_;
};

#endif // IMCHAT_DAO_IMPLEMENT_H
