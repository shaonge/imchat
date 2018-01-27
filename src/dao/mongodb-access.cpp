///
/// \file    mongodb-access.cpp
/// \brief   Mongodb访问辅助类实现
///
/// \author  shaonge@gmail.com
/// \date    11:47 AM 1/8/18
///

#include "mongodb-access.h"

#include <bsoncxx/exception/exception.hpp>
#include <mongocxx/exception/bulk_write_exception.hpp>
#include <mongocxx/exception/query_exception.hpp>

using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;

MongodbAccesser::MongodbAccesser()
    : server_uri_(mongocxx::uri()), client_(mongocxx::uri()), database_(), collection_() {
    IMCHAT_ASSERT(client_);
}

MongodbAccesser::MongodbAccesser(const std::string &ip_and_port) : database_(), collection_() {
    server_uri_ = std::move(mongocxx::uri(std::string("mongodb://") + ip_and_port));
    client_ = std::move(mongocxx::client(server_uri_));
    IMCHAT_ASSERT(client_);
}

document_value MongodbAccesser::make_document(const std::string &field_name,
                                              const std::string &value) {
    auto doc = document() << field_name << value << finalize;

    return std::move(doc);
}

document_value MongodbAccesser::make_update_document(const std::string &field_name,
                                                     const std::string &new_value) {
    auto doc = document() << "$set" << open_document << field_name << new_value << close_document
                          << finalize;

    return std::move(doc);
}

optional<document_value> MongodbAccesser::make_document_from_json(const std::string &json_str) {
    document_value doc{document_view()};

    try {
        doc = bsoncxx::from_json(json_str);
    } catch (bsoncxx::exception &e) {
        IMCHAT_ERROR(e.what());
        return optional<document_value>();
    }

    return optional<document_value>(std::move(doc));
}

bool MongodbAccesser::deleteDatabase(const std::string &db_name) {
    IMCHAT_ASSERT(client_);

    try {
        client_[db_name].drop();
    } catch (mongocxx::exception &e) {
        IMCHAT_ERROR(e.what());
        return false;
    }

    if (database_ && database_.name().to_string() == db_name) {
        database_ = mongocxx::database();
    }

    return true;
}

bool MongodbAccesser::deleteCollection(const std::string &coll_name) {
    IMCHAT_ASSERT(database_);

    if (!database_.has_collection(coll_name)) {
        return true;
    }

    try {
        database_[coll_name].drop();
    } catch (mongocxx::exception &e) {
        IMCHAT_ERROR(e.what());
        return false;
    }

    if (collection_ && collection_.name().to_string() == coll_name) {
        collection_ = mongocxx::collection();
    }

    return true;
}

bool MongodbAccesser::create_index(const std::string &field_name, int order) {
    IMCHAT_ASSERT(collection_);

    auto index_specification = document() << field_name << order << finalize;

    try {
        collection_.create_index(std::move(index_specification));
    } catch (mongocxx::exception &e) {
        IMCHAT_ERROR(e.what());
        return false;
    }

    return true;
}

optional<document_value> MongodbAccesser::find_one(const std::string &field_name,
                                                   const std::string &value) {
    IMCHAT_ASSERT(collection_);

    auto search_content = document() << field_name << value << finalize;
    optional<document_value> result;

    try {
        result = collection_.find_one(std::move(search_content));
    } catch (mongocxx::query_exception &e) {
        IMCHAT_ERROR(e.what());
        return optional<document_value>();
    }

    return std::move(result);
}

optional<document_element> MongodbAccesser::find_in_document(const document_view &doc,
                                                             const std::string &field_name) {
    auto result = doc[field_name];

    if (result) {
        return optional<document_element>(result);
    }

    return optional<document_element>();
}

optional<std::string> MongodbAccesser::field_string_value(const document_view &doc,
                                                          const std::string &field_name) {
    auto result = doc[field_name];

    if (result && result.type() == bsoncxx::type::k_utf8) {
        bsoncxx::stdx::string_view sv = result.get_utf8();
        return optional<std::string>(sv.to_string());
    }

    return optional<std::string>();
}

optional<document_value> MongodbAccesser::field_document_value(const document_view &doc,
                                                               const std::string &field_name) {
    auto result = doc[field_name];

    if (result && result.type() == bsoncxx::type::k_document) {
        return optional<document_value>(document_value(result.get_document()));
    }

    return optional<document_value>();
}

bool MongodbAccesser::insert_document(const document_view_or_value &doc) {
    IMCHAT_ASSERT(collection_);

    optional<mongocxx::result::insert_one> insert_result;

    try {
        insert_result = collection_.insert_one(doc);
    } catch (mongocxx::bulk_write_exception &e) {
        IMCHAT_ERROR(e.what());
        return false;
    }

    if (insert_result) {
        return true;
    }

    return false;
}

bool MongodbAccesser::update_document(const document_view_or_value &doc,
                                      const document_view_or_value &update) {
    IMCHAT_ASSERT(collection_);

    optional<mongocxx::result::update> update_result;

    try {
        update_result = collection_.update_one(doc, update);
    } catch (mongocxx::exception &e) {
        IMCHAT_ERROR(e.what());
        return false;
    }

    if (update_result) {
        return true;
    }

    return false;
}