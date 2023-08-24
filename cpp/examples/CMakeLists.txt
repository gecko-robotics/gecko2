
list(APPEND examples
    msg
    csv
)


foreach(app ${examples})
    add_executable(${app} ${app}.cpp)
    # target_include_directories(${PROGRAM}
    #     PRIVATE
    #         ${CMAKE_SOURCE_DIR}/src
    #         # ${gcisensors_SOURCE_DIR}/src
    #         # ${yivo_SOURCE_DIR}/src
    #         # ${gcimock_SOURCE_DIR}/include
    #         # ${squaternion_SOURCE_DIR}/src
    #         # ${marko_SOURCE_DIR}/include
    #         # ${serialcomm_SOURCE_DIR}/include
    # )
    target_link_libraries(${app}
        PRIVATE
            ${PROJECT_NAME}
            # ${libs}
            # Threads::Threads
    )
endforeach()

add_custom_command(
        TARGET csv POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/nodes.csv
                ${CMAKE_BINARY_DIR}/nodes.csv )

