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
project(udp_server)
project(udp_client)

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
add_executable(udp_server
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/udp/server.c)
add_executable(udp_client
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/udp/client.c)