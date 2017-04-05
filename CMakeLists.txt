cmake_minimum_required(VERSION 2.8)
project(irc)

set(SHARED_FLAGS " -Wall -Wextra -Wshadow -Werror -g -D_POSIX_C_SOURCE=200809L")
set(CMAKE_C_FLAGS "-std=c11 ${SHARED_FLAGS}")
set(CMAKE_CXX_FLAGS "-std=c++11 ${SHARED_FLAGS}")

include_directories(include)
add_library(irc_client SHARED src/irc_client.c)
add_library(irc_server SHARED src/irc_server.c)

install(TARGETS irc_client DESTINATION lib)
install(TARGETS irc_server DESTINATION lib)
install(FILES include/irc_client.h DESTINATION include)
install(FILES include/irc_server.h DESTINATION include)
