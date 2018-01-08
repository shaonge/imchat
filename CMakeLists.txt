cmake_minimum_required(VERSION 3.8)
project(imchat)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(/home/gss/hiredis)
include_directories(/usr/local/include)
include_directories(/usr/local/include/mongocxx/v_noabi)
include_directories(/usr/local/include/bsoncxx/v_noabi)

link_directories(/usr/local/lib)
link_directories(/home/gss/hiredis)

link_libraries(mongocxx bsoncxx)

aux_source_directory(src/dao SOURCE_FILES)

add_subdirectory(test)

add_executable(imc ${SOURCE_FILES} src/main.cpp src/dao/easy-dao-implement.cpp src/main.cpp)
target_link_libraries(imc mongocxx)
target_link_libraries(imc hiredis)