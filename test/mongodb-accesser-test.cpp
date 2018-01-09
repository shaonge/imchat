#include <gtest/gtest.h>
#include "mongodb-access.h"

TEST(MongodbAccesserTest, constructer) {
    MongodbAccesser{};
    MongodbAccesser{"127.0.0.1:27017"};
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}