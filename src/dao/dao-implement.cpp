///
/// \file    easy-dao-implement.cpp
/// \brief   DAO层接口类的一个实现
///
/// \author  shaonge@gmail.com
/// \date    8:31 PM 1/8/18
///

#include "dao-implement.h"

bool DaoImplement::isUserExisting(const std::string &user_name) {
    return static_cast<bool>(mongodb_.find_one(USER_NAME, user_name));
}

bool DaoImplement::isUserOnline(const std::string &user_name) { return false; }

std::optional<std::string> DaoImplement::userJoinIP(const std::string &user_name) {
    return std::optional<std::string>();
}

bool DaoImplement::isOnesBuddy(const std::string &user_name, const std::string &buddy_name) {
    auto doc = mongodb_.find_one(USER_NAME, user_name);
    if (!doc) {
        return false;
    }

    return static_cast<bool>(mongodb_.find_in_document(doc->view(), buddy_name));
}

std::optional<std::string> DaoImplement::getUserInfo(const std::string &user_name,
                                                     const std::string &field_name) {
    auto doc = mongodb_.find_one(USER_NAME, user_name);
    if (!doc) {
        return std::optional<std::string>();
    }

    return std::optional<std::string>(mongodb_.field_string_value(doc->view(), field_name).value());
}

bool DaoImplement::addNewUser(const std::string &user_name) {
    return mongodb_.insert_document(mongodb_.make_document(USER_NAME, user_name));
}

bool DaoImplement::setUserOnline(const std::string &user_name) { return false; }

bool DaoImplement::addNewBuddy(const std::string &user_name, const std::string &buddy_name) {
    auto doc = mongodb_.find_one(USER_NAME, user_name);
    if (!doc) {
        return false;
    }

    auto update_doc = mongodb_.make_update_document(buddy_name, "\0");
    return mongodb_.update_document(doc->view(), update_doc.view());
}

bool DaoImplement::setUserInfo(const std::string &user_name, const std::string &field_name,
                               const std::string &value) {
    auto doc = mongodb_.find_one(USER_NAME, user_name);
    if (!doc) {
        return false;
    }

    auto update_doc = mongodb_.make_update_document(field_name, value);
    return mongodb_.update_document(doc->view(), update_doc.view());
}

bool DaoImplement::setUserInfoFromJson(const std::string &user_name, const std::string &json_str) {
    auto doc = mongodb_.find_one(USER_NAME, user_name);
    if (!doc) {
        return false;
    }

    auto update_doc = mongodb_.make_document_from_json(json_str);

    if (!update_doc) {
        return false;
    }

    return mongodb_.update_document(doc->view(), update_doc->view());
}
