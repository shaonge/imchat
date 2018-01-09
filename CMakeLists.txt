cmake_minimum_required(VERSION 2.8)

project(imchat CXX)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/usr/local/include/mongocxx/v_noabi)
include_directories(/usr/local/include/bsoncxx/v_noabi)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_FILES)

add_subdirectory(test)

add_executable(imc ${SOURCE_FILES})
target_link_libraries(imc mongocxx bsoncxx)
target_link_libraries(imc hiredis)