#include "dao/redis-access.h"
#include "imchat.h"
#include <gtest/gtest.h>

TEST(RedisAccesserTest, methodTest) {
    RedisAccesser r1;
    RedisAccesser r2("127.0.0.1", 6379);

    constexpr const char *KEY = "user_ip";

    assert(r1.keyDel(KEY));
    assert(!r1.keyExists(KEY));
    assert(!r1.hashExists(KEY, "hwk"));
    assert(r1.hashAdd(KEY, "hwk", "127.0.0.1"));
    assert(r1.hashAdd(KEY, "gss", "127.0.0.2"));
    assert(r1.hashExists(KEY, "hwk"));
    auto res1 = r1.hashGet(KEY, "gss");
    assert(*res1 == "127.0.0.2");
    assert(r1.hashEdit(KEY, "gss", "127.0.0.3"));
    auto res2 = r1.hashGet(KEY, "gss");
    assert(*res2 == "127.0.0.3");
    assert(r1.hashDel(KEY, "hwk"));
    assert(!r1.hashExists(KEY, "hwk"));
}

int main(int argc, char **argv) {
    loggerConfigure(argv[0], "./log");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}