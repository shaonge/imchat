#include <gtest/gtest.h>
#include "redis-access.h"

TEST(RedisAccesserTest, constructer) {
    RedisAccesser r1{};
    RedisAccesser r2{"127.0.0.1", 6379};
//    r2.hashSet(0,std::string("127.0.0.1"));
//    r2.hashSet(1,std::string("127.0.0.2"));
//    r2.hashSet(2,std::string("127.0.0.3"));
}

int main(int argc, char **argv) {

//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//    RedisAccesser r1{};

    RedisAccesser r2{"127.0.0.1", 6379};
    bool res = false;

    res = r2.hashAdd(6754,std::string("127.0.0.1"));
    if(res){
        std::cout<<"TRUE1"<<std::endl;
    }
    res = r2.hashAdd(8976,std::string("127.0.0.2"));
    if(res){
        std::cout<<"TRUE2"<<std::endl;
    }

    res = r2.hashEdit(8967,std::string("127.0.0.3"));
    if(res){
        std::cout<<"TRUE3"<<std::endl;
    }

    auto value_string = r2.hashGetValue(6754);
    std::cout<< r2.hashGetValue(6754).value_or("NULL") <<std::endl;
    r2.hashDel(6754);


//    assert(r2.hashSet(1,std::string("127.0.0.2")));
//    assert(r2.hashSet(2,std::string("127.0.0.3")));


}