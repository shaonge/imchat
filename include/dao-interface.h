///
/// \file    dao-interface.h
/// \brief   DAO层接口类
///
/// \author  shaonge@gmail.com
/// \date    10:29 PM 1/7/18
///

#ifndef IMCHAT_DAO_INTERFACE_H
#define IMCHAT_DAO_INTERFACE_H

#include <boost/optional.hpp>
#include <string>

/// 业务层只能通过此接口类访问数据层
class DaoInterface {
public:
    virtual bool isUserExisting(const std::string &user_name) const = 0;

    virtual bool isUserOnline(const std::string &user_name) const = 0;

    virtual boost::optional<std::string> userJoinIP(const std::string &user_name) const = 0;

    virtual bool isOnesBuddy(const std::string &user_name, const std::string &buddy_name) const = 0;

    virtual boost::optional<std::string> getUserInfo(const std::string &user_name,
                                                     const std::string &field_name) const = 0;

    virtual bool addNewUser(const std::string &user_name) = 0;

    virtual bool setUserOnline(const std::string &user_name) = 0;

    virtual bool addNewBuddy(const std::string &user_name, const std::string &buddy_name) = 0;

    virtual bool setUserInfo(const std::string &user_name,
                             const std::string &field_name,
                             const std::string &value) = 0;

    virtual bool setUserInfoFromJson(const std::string &user_name,
                                     const std::string &field_name,
                                     const std::string &json_str) = 0;
};

#endif //IMCHAT_DAO_INTERFACE_H
