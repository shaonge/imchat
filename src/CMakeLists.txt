
aux_source_directory(dao DAO_FILES)
add_library(dao STATIC ${DAO_FILES})
target_link_libraries(dao mongocxx bsoncxx hiredis glog)

add_library(rcf STATIC rcf/RCF/RCF.cpp)
target_link_libraries(rcf pthread dl)

aux_source_directory(message-server MESSAGE_SERVER_FILES)
add_executable(message-server ${MESSAGE_SERVER_FILES})
target_link_libraries(message-server dao rcf)

aux_source_directory(jspp-resolver JSPP_RESOLVER_FILES)
add_executable(jspp-resolver ${JSPP_RESOLVER_FILES})
target_link_libraries(jspp-resolver jsoncpp rcf)