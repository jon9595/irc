cmake_minimum_required(VERSION 2.8)
project(irc)

set(SHARED_FLAGS " -Wall -Wextra -Wshadow -Werror -g -D_POSIX_C_SOURCE=200809L -lncurses")
set(CMAKE_C_FLAGS "-std=c11 ${SHARED_FLAGS}")
set(CMAKE_CXX_FLAGS "-std=c++11 ${SHARED_FLAGS}")

include_directories(include)

add_library(client_core SHARED src/client/irc_client.c)

add_executable(client src/client/irc_client_gui.c)
add_executable(server src/server/irc_server.c)

target_link_libraries(client ncurses)

install(FILES include/irc_client.h DESTINATION include)
install(FILES include/irc_server.h DESTINATION include)
