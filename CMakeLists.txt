cmake_minimum_required(VERSION 2.8)
project(irc)

set(SHARED_FLAGS " -Wall -Wextra -Wshadow -Werror -g -D_POSIX_C_SOURCE=200809L")
set(CMAKE_C_FLAGS "-std=c11 ${SHARED_FLAGS}")
set(CMAKE_CXX_FLAGS "-std=c++11 ${SHARED_FLAGS}")

include_directories(include)

add_executable(client src/client/irc_client.c)
add_executable(server src/server/irc_server.c)

install(FILES include/irc_client.h DESTINATION include)
install(FILES include/irc_server.h DESTINATION include)
