#include "dao/dao-implement.h"

#include <gtest/gtest.h>

TEST(DaoInterfaceTest, methodTest) {
    DaoInterface *di = new DaoImplement();

    IMCHAT_ASSERT(di->destroyAllData());
    IMCHAT_ASSERT(!di->isUserExisting("gss"));
    IMCHAT_ASSERT(di->addNewUser("gss"));
    IMCHAT_ASSERT(di->isUserExisting("gss"));
    IMCHAT_ASSERT(di->setUserInfo("gss", "passwd", "0000"));
    IMCHAT_ASSERT(di->getUserInfo("gss", "passwd") == "0000");
    IMCHAT_ASSERT(!di->isOnesBuddy("gss", "shaonge"));
    IMCHAT_ASSERT(di->addNewBuddy("gss", "shaonge"));
    IMCHAT_ASSERT(di->isOnesBuddy("gss", "shaonge"));
    IMCHAT_ASSERT(!di->isUserOnline("gss"));
    IMCHAT_ASSERT(di->setUserOnline("gss", "127.0.0.1"));
    IMCHAT_ASSERT(di->isUserOnline("gss"));
    auto ip1 = di->userJoinIP("gss");
    IMCHAT_ASSERT(*ip1 == "127.0.0.1");
    IMCHAT_ASSERT(di->setUserOnline("gss", "127.0.0.2"));
    auto ip2 = di->userJoinIP("gss");
    IMCHAT_ASSERT(*ip2 == "127.0.0.2");

    delete di;
}

int main(int argc, char **argv) {
    loggerConfigure(argv[0], "./log");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}