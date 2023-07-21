
set(PROGRAM msg)

add_executable(${PROGRAM} main.cpp)
target_include_directories(${PROGRAM}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        # ${gcisensors_SOURCE_DIR}/src
        # ${yivo_SOURCE_DIR}/src
        # ${gcimock_SOURCE_DIR}/include
        # ${squaternion_SOURCE_DIR}/src
        # ${marko_SOURCE_DIR}/include
        # ${serialcomm_SOURCE_DIR}/include
)
target_link_libraries(${PROGRAM}
    PRIVATE
        gecko2
        # ${libs}
        # Threads::Threads
)
