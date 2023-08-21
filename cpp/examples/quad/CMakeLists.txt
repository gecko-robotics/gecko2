cmake_minimum_required(VERSION 3.25.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PROJECT_VERSION_MAJOR year
# PROJECT_VERSION_MINOR month
# PROJECT_VERSION_PATCH day
# PROJECT_VERSION_TWEAK tweak
project(gecko2 VERSION 2023.01.28.0)

if(PROJECT_IS_TOP_LEVEL)
    cmake_host_system_information(RESULT HOST QUERY HOSTNAME)
    cmake_host_system_information(RESULT OSN QUERY OS_NAME)
    cmake_host_system_information(RESULT OS_VERSION QUERY OS_RELEASE)
    cmake_host_system_information(RESULT PROC QUERY PROCESSOR_DESCRIPTION)

    message(STATUS "-------------------------------------")
    message(STATUS "  Project: ${PROJECT_NAME}")
    message(STATUS "  Version: ${CMAKE_PROJECT_VERSION}")
    message(STATUS "  C++ ${CMAKE_CXX_STANDARD}")
    message(STATUS "-------------------------------------")
    message(STATUS " ${HOST}")
    message(STATUS " ${OSN}: ${OS_VERSION}")
    message(STATUS " ${PROC}")
    message(STATUS "-------------------------------------")

    set(BUILD_EXAMPLES ON)
    set(BUILD_GTESTS ON)
else()
    message(STATUS "-> ${PROJECT_NAME} is submodule")
    set(BUILD_EXAMPLES OFF)
    set(BUILD_GTESTS OFF)
endif()

include(FetchContent)

FetchContent_Declare(gecko2
    GIT_REPOSITORY "https://github.com/gecko-robotics/gecko2.git"
    GIT_TAG "origin/main"
    # SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/gecko2"
    SOURCE_SUBDIR "cpp"
)

# gciSensors -----------------
# FetchContent_Declare(gcisensors
#   GIT_REPOSITORY "git@github.com:the-guild-of-calamitous-intent/gciSensors.git"
#   GIT_TAG "origin/main"
#   SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/gcisensors"
# )

# serialcomm -----------------
FetchContent_Declare(serialcomm
    GIT_REPOSITORY "https://github.com/gecko-robotics/serialcomm.git"
    GIT_TAG "origin/main"
    # SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/serialcomm"
)

# yivo -----------------
FetchContent_Declare(yivo
  GIT_REPOSITORY "https://github.com/MomsFriendlyRobotCompany/yivo.git"
  GIT_TAG "origin/main"
#   SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/yivo"
  SOURCE_SUBDIR "c++"
)

# squaternion -----------------
FetchContent_Declare(squaternion
    GIT_REPOSITORY "https://github.com/MomsFriendlyRobotCompany/squaternion.git"
    GIT_TAG "origin/master"
    # SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/squaternion"
    SOURCE_SUBDIR "cpp"
)

FetchContent_MakeAvailable( squaternion yivo gecko2 serialcomm )

message(STATUS "${gecko2_SOURCE_DIR} ${gecko2_BINARY_DIR} ${gecko2_POPULATED}")
message(STATUS "${yivo_SOURCE_DIR}")
message(STATUS "${squaternion_SOURCE_DIR}")
message(STATUS "${serialcomm_SOURCE_DIR}")

# if(gcisensors_POPULATED)
#     message(STATUS "=> Found gcisensors")
# else()
#     message(STATUS "*** Didn't find gcisensors")
# endif()

add_executable(quad main.cpp)
# target_include_directories(quad
#     PRIVATE
#         # ${CMAKE_SOURCE_DIR}/src
#         # ${gcisensors_SOURCE_DIR}/src
#         ${yivo_SOURCE_DIR}/cpp/src
#         ${gecko2_SOURCE_DIR}/cpp/src
#         ${squaternion_SOURCE_DIR}/cpp/src
#         # ${marko_SOURCE_DIR}/include
#         ${serialcomm_SOURCE_DIR}/include
# )
target_link_libraries(quad
    PRIVATE
        gecko2
        serialcomm
        yivo
        squaternion
        # Threads::Threads
)