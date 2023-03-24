cmake_minimum_required(VERSION 3.11...3.13)

set(
    CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} \
    -Wall \
    -g"
)

project(epoll_client_socket_ET_LT)
project(epoll_server_socket_ET_LT)

add_executable(epoll_client_socket_ET_LT 
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/epoll/client_socket_ET_LT.c)
add_executable(epoll_server_socket_ET_LT
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/epoll/server_socket_ET_LT.c)   