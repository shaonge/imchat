#include "dao/redis-access.h"

#include <gtest/gtest.h>

TEST(RedisAccesserTest, constructer) {
    RedisAccesser r1;
    RedisAccesser r2("127.0.0.1", 6379);
}

int main(int argc, char **argv) {
    loggerConfigure(argv[0], ".");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}