///
/// \file    mongodb-access.h
/// \brief   Mongodb访问辅助类
///
/// \author  shaonge@gmail.com
/// \date    11:21 PM 1/7/18
///

#ifndef IMCHAT_MONGODB_ACCESS_H
#define IMCHAT_MONGODB_ACCESS_H

#include "imchat.h"

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include <boost/noncopyable.hpp>

template <typename T> using optional = bsoncxx::stdx::optional<T>;

using document_value = bsoncxx::document::value;
using document_view = bsoncxx::document::view;
using document_view_or_value = bsoncxx::document::view_or_value;
using document_element = bsoncxx::document::element;

class MongodbAccesser : boost::noncopyable {
  public:
    MongodbAccesser();

    explicit MongodbAccesser(const std::string &ip_and_port);

    void accessDatabase(const std::string &db_name) {
        database_ = client_[db_name];
        IMCHAT_ASSERT(database_);
    }

    void accessCollection(const std::string &coll_name) {
        collection_ = database_[coll_name];
        IMCHAT_ASSERT(collection_);
    }

    bool deleteDatabase(const std::string &db_name);

    bool deleteCollection(const std::string &coll_name);

    document_value make_document(const std::string &field_name, const std::string &value);

    document_value make_update_document(const std::string &field_name,
                                        const std::string &new_value);

    optional<document_value> make_document_from_json(const std::string &json_str);

    bool create_index(const std::string &field_name, int order);

    optional<document_value> find_one(const std::string &field_name, const std::string &value);

    optional<document_element> find_in_document(const document_view &doc,
                                                const std::string &field_name);

    optional<std::string> field_string_value(const document_view &doc,
                                             const std::string &field_name);

    optional<document_value> field_document_value(const document_view &doc,
                                                  const std::string &field_name);

    bool insert_document(const document_view_or_value &doc);

    bool update_document(const document_view_or_value &doc, const document_view_or_value &update);

  private:
    static inline mongocxx::instance instance{};

  private:
    mongocxx::uri server_uri_;
    mongocxx::client client_;

    mongocxx::database database_;
    mongocxx::collection collection_;
};

#endif // IMCHAT_MONGODB_ACCESS_H
