include_directories(../src/include)

add_executable(utest_libuv_echo_server c/utest_libuv_echo_server.c)
add_executable(utest_libuv_echo_client c/utest_libuv_echo_client.c)
add_executable(utest_storage c/utest_storage.c)
add_executable(utest_client c/utest_client.c)


file(GLOB_RECURSE data resource/*)
file(COPY ${data} DESTINATION .)

target_link_libraries(utest_libuv_echo_server remote_dictionary_server uv)
target_link_libraries(utest_libuv_echo_client remote_dictionary_server uv)
target_link_libraries(utest_storage remote_dictionary_server Judy)
target_link_libraries(utest_client remote_dictionary_client uv)

add_test(NAME utest_libuv_echo_server COMMAND utest_libuv_echo_server)
add_test(NAME utest_libuv_echo_client COMMAND utest_libuv_echo_client)
add_test(NAME utest_storage COMMAND utest_storage)
add_test(NAME utest_client COMMAND utest_client)