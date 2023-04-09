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
project(local_socket_server)
project(local_socket_client)

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
add_executable(local_socket_server
    ${CMAKE_CURRENT_SOURCE_DIR}/system_program/IPC/local_socket_server.c
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/wrap.c)
add_executable(local_socket_client
    ${CMAKE_CURRENT_SOURCE_DIR}/system_program/IPC/local_socket_client.c
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/wrap.c)


## libevent
project(get_supported_methods)
add_executable(get_supported_methods
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/libevent/get_supported_methods.c) 
target_link_libraries(get_supported_methods libevent.so)

project(base_get_method)
add_executable(base_get_method
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/libevent/base_get_method.c) 
target_link_libraries(base_get_method libevent.so)

project(read_fifo)
add_executable(read_fifo
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/libevent/read_fifo.c) 
target_link_libraries(read_fifo libevent.so)

project(write_fifo)
add_executable(write_fifo
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/libevent/write_fifo.c) 
target_link_libraries(write_fifo libevent.so)

project(bufferevent_server)
add_executable(bufferevent_server
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/libevent/bufferevent_server.c) 
target_link_libraries(bufferevent_server libevent.so)

project(bufferevent_client)
add_executable(bufferevent_client
    ${CMAKE_CURRENT_SOURCE_DIR}/network_program/libevent/bufferevent_client.c) 
target_link_libraries(bufferevent_client libevent.so)