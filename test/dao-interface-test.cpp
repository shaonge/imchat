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

    delete di;
}

int main(int argc, char **argv) {
    loggerConfigure(argv[0], ".");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}