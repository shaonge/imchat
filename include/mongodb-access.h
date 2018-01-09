///
/// \file    mongodb-access.h
/// \brief   Mongodb访问辅助类
///
/// \author  shaonge@gmail.com
/// \date    11:21 PM 1/7/18
///

#ifndef IMCHAT_MONGODB_ACCESS_H
#define IMCHAT_MONGODB_ACCESS_H

#include <boost/noncopyable.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

class MongodbAccesser : boost::noncopyable {
public:
    MongodbAccesser() noexcept;

    explicit MongodbAccesser(const std::string &ip_and_port) noexcept;

    inline void accessDatabase(const std::string &db_name) {
        database_ = client_[db_name];
    }

    inline void accessCollection(const std::string &coll_name) {
        collection_ = database_[coll_name];
    }

public:
    mongocxx::database database_;
    mongocxx::collection collection_;

private:
    static mongocxx::instance instance;

private:
    mongocxx::uri server_uri_;
    mongocxx::client client_;
};

#endif //IMCHAT_MONGODB_ACCESS_H
