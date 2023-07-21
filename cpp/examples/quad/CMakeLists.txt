# gciSensors -----------------
FetchContent_Declare(gcisensors
  GIT_REPOSITORY "git@github.com:the-guild-of-calamitous-intent/gciSensors.git"
  GIT_TAG "origin/main"
  SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/gcisensors"
)

# serialcomm -----------------
FetchContent_Declare(serialcomm
GIT_REPOSITORY "https://github.com/gecko-robotics/serialcomm.git"
GIT_TAG "origin/main"
SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/serialcomm"
)

FetchContent_MakeAvailable( gcisensors serialcomm )

# if(gcisensors_POPULATED)
#     message(STATUS "=> Found gcisensors")
# else()
#     message(STATUS "*** Didn't find gcisensors")
# endif()

set(PROGRAM quad)

add_executable(${PROGRAM} main.cpp)
target_include_directories(${PROGRAM}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${gcisensors_SOURCE_DIR}/src
        ${yivo_SOURCE_DIR}/src
        # ${gcimock_SOURCE_DIR}/include
        ${squaternion_SOURCE_DIR}/src
        ${marko_SOURCE_DIR}/include
        ${serialcomm_SOURCE_DIR}/include
)
target_link_libraries(${PROGRAM}
    PRIVATE
        gecko2
        # ${libs}
        # gcisensors
        serialcomm
        Threads::Threads
)