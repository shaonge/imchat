
add_executable(redis-accesser redis-accesser-test.cpp
        ${PROJECT_SOURCE_DIR}/src/dao/redis-access.cpp)
target_link_libraries(redis-accesser gtest pthread hiredis)

add_executable(mongodb-accesser mongodb-accesser-test.cpp
        ${PROJECT_SOURCE_DIR}/src/dao/mongodb-access.cpp)
target_link_libraries(mongodb-accesser gtest pthread mongocxx bsoncxx)

add_test(mytest redis-accesser mongodb-accesser)
enable_testing()