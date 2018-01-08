cmake_minimum_required(VERSION 3.8)
project(imchat)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(src)
include_directories(/usr/local/include)
include_directories(/usr/local/include/mongocxx/v_noabi)
include_directories(/usr/local/include/bsoncxx/v_noabi)

link_directories(/usr/local/lib)
link_libraries(mongocxx bsoncxx)

include_directories(/home/gss/hiredis)
link_directories(/home/gss/hiredis)

aux_source_directory(src/dao SOURCE_FILES)

add_executable(imc src/main.cpp ${SOURCE_FILES})
target_link_libraries(imc mongocxx)
target_link_libraries(imc hiredis)
