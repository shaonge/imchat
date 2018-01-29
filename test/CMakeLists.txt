include_directories(${PROJECT_SOURCE_DIR}/src)

set(TEST_LIBS gtest pthread dao)

add_executable(redis-accesser redis-accesser-test.cpp)
target_link_libraries(redis-accesser ${TEST_LIBS})

add_executable(mongodb-accesser mongodb-accesser-test.cpp)
target_link_libraries(mongodb-accesser ${TEST_LIBS})

add_executable(dao-interface dao-interface-test.cpp)
target_link_libraries(dao-interface ${TEST_LIBS})

add_test(mytest redis-accesser mongodb-accesser dao-interface)
enable_testing()