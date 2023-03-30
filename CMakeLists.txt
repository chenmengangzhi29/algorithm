cmake_minimum_required(VERSION 3.11...3.13)

set(
    CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} \
    -Wall \
    -g"
)

project(client_socket_ET_LT)
project(erver_socket_ET_LT)
project(no_block_epoll)
project(reactor_epoll)
project(threadpool)

add_executable(client_socket_ET_LT 
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/epoll/client_socket_ET_LT.c)
add_executable(server_socket_ET_LT
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/epoll/server_socket_ET_LT.c) 
add_executable(no_block_epoll
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/epoll/no_block_epoll.c)  
add_executable(reactor_epoll
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/epoll/reactor_epoll.c)
add_executable(threadpool
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/thread_pool/threadpool.c)