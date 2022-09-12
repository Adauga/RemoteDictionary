cmake_minimum_required(VERSION 3.20)
project(RemoteDictionary C)

set(CMAKE_C_STANDARD 99)

include(CTest)
add_subdirectory(utest)

include_directories(./src/include)
add_library(remote_dictionary_server src/c/storage.c
        src/c/server_engine.c
        src/c/cJSON.c)

add_library(remote_dictionary_client src/c/client.c
        src/c/client_engine.c
        src/c/cJSON.c)

add_executable(run_server src/c/server.c)
target_link_libraries(run_server remote_dictionary_server)

target_link_libraries(remote_dictionary_server Judy uv)
target_link_libraries(remote_dictionary_client uv)