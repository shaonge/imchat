cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=gnu++0x -Wall")

include_directories(../src)

add_executable(redis-accesser redis-accesser-test.cpp ../src/dao/redis-access.cpp)
target_link_libraries(redis-accesser gtest pthread hiredis)

add_executable(mongodb-accesser mongodb-accesser-test.cpp ../src/dao/mongodb-access.cpp)
target_link_libraries(mongodb-accesser gtest pthread mongocxx bsoncxx)

add_test(Test gtest)
enable_testing()

