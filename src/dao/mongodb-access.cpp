///
/// \file    mongodb-access.cpp
/// \brief
///
/// \author  shaonge@gmail.com
/// \date    11:47 AM 1/8/18
///

#include "mongodb-access.h"

mongocxx::instance MongodbAccesser::instance{};


MongodbAccesser::MongodbAccesser() noexcept : server_uri_(mongocxx::uri{}), client_(mongocxx::uri{}) {}


MongodbAccesser::MongodbAccesser(const std::string &ip_and_port) noexcept {
    server_uri_ = std::move(mongocxx::uri{std::string{"mongodb://"} + ip_and_port});
    /// \todo exception handle
    client_ = std::move(mongocxx::client{server_uri_});
}
