# Threads -----------------
find_package(Threads REQUIRED)
if(Threads_FOUND)
    message(STATUS ">> Threads found")
    if(CMAKE_USE_PTHREADS_INIT)
        message(STATUS " -> Using pthreads")
    endif()
else()
    message(WARNING "*** Could not find Threads ***")
endif()

list(APPEND examples
    msg
    csv
    node_udp
    node_uds
    config
)


foreach(app ${examples})
    add_executable(${app} ${app}.cpp)
    target_link_libraries(${app}
        PRIVATE
            ${PROJECT_NAME}
            Threads::Threads
    )
endforeach()

add_custom_command(
        TARGET csv POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/nodes.csv
                ${CMAKE_BINARY_DIR}/nodes.csv )

add_custom_command(
    TARGET config POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/config.txt
            ${CMAKE_BINARY_DIR}/config.txt )
