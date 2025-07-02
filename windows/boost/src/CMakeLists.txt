set(
    SRC_FILES
    ./main.cpp
    ./06.cpp
)

#add_executable(boost ${SRC_FILES})

add_executable(10_server main.cpp 10_server.cpp)

add_executable(10_client 10_client.cpp)

set(COMMON_LIBS
    #Boost::system
    ws2_32
    mswsock
    advapi32
)

target_link_libraries(10_server PRIVATE ${COMMON_LIBS})
target_link_libraries(10_client PRIVATE ${COMMON_LIBS})



#target_link_libraries(boost ws2_32)