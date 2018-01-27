#include "dao/mongodb-access.h"

#include <gtest/gtest.h>

TEST(MongodbAccesserTest, methodTest) {
    MongodbAccesser m1;
    MongodbAccesser m2("127.0.0.1:27017");

    IMCHAT_ASSERT(m1.deleteDatabase("db1"));
    m1.accessDatabase("db1");
    m1.accessCollection("col1");
    m2.accessDatabase("db1");
    m2.accessCollection("col1");

    IMCHAT_ASSERT(m1.insert_document(m1.make_document("user_name", "gss")));
    IMCHAT_ASSERT(m1.insert_document(m1.make_document("user_name", "yyb")));

    auto jdoc = m1.make_document_from_json(R"( { "user_name" : "hwk" } )");
    IMCHAT_ASSERT(jdoc);
    IMCHAT_ASSERT(m1.insert_document(jdoc->view()));

    IMCHAT_ASSERT(m1.create_index("user_name", 1));

    auto fr1 = m1.find_one("user_name", "gss");
    IMCHAT_ASSERT(fr1);
    auto fr2 = m2.find_one("user_name", "lch");
    IMCHAT_ASSERT(!fr2);

    auto frd1 = m1.find_in_document(fr1->view(), "user_name");
    IMCHAT_ASSERT(frd1);
    auto frd2 = m2.field_string_value(fr1->view(), "user_name");
    IMCHAT_ASSERT(frd2);
    IMCHAT_ASSERT(*frd2 == "gss");
    auto frd3 = m1.field_document_value(fr1->view(), "user_name");
    IMCHAT_ASSERT(!frd3);

    auto alterdoc = m1.make_update_document("user_name", "shaonge");
    IMCHAT_ASSERT(m1.update_document(fr1->view(), alterdoc.view()));

    auto fr3 = m1.find_one("user_name", "gss");
    IMCHAT_ASSERT(!fr3);

    auto fr4 = m1.find_one("user_name", "shaonge");
    IMCHAT_ASSERT(fr4);

    auto adddoc = m2.make_update_document("passwd", "0000");
    IMCHAT_ASSERT(m1.update_document(fr1->view(), adddoc.view()));

    IMCHAT_ASSERT(m1.deleteDatabase("db1"));
    IMCHAT_ASSERT(m1.deleteDatabase("db2"));
}

int main(int argc, char **argv) {
    loggerConfigure(argv[0], ".");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}