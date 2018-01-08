#include <gtest/gtest.h>
#include "dao/redis-access.h"

TEST(RedisAccesserTest, constructer) {
    RedisAccesser r1{};
    RedisAccesser r2{"127.0.0.1", 6379};
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}