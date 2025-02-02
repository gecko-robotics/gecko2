cmake_minimum_required(VERSION 3.21.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


string(ASCII 27 Esc)
set(Reset      "${Esc}[m")
set(Bold       "${Esc}[1m")
set(Red         "${Esc}[31m")
set(Green       "${Esc}[32m")
set(Yellow      "${Esc}[33m")
set(Blue        "${Esc}[34m")
set(Magenta     "${Esc}[35m")
set(Cyan        "${Esc}[36m")
set(White       "${Esc}[37m")
set(BoldRed     "${Esc}[1;31m")
set(BoldGreen   "${Esc}[1;32m")
set(BoldYellow  "${Esc}[1;33m")
set(BoldBlue    "${Esc}[1;34m")
set(BoldMagenta "${Esc}[1;35m")
set(BoldCyan    "${Esc}[1;36m")
set(BoldWhite   "${Esc}[1;37m")

# PROJECT_VERSION_MAJOR year
# PROJECT_VERSION_MINOR month
# PROJECT_VERSION_PATCH day
# PROJECT_VERSION_TWEAK tweak
project(gecko2 VERSION 2023.01.28.0)

include(FetchContent)

if(PROJECT_IS_TOP_LEVEL)
    cmake_host_system_information(RESULT HOST QUERY HOSTNAME)
    cmake_host_system_information(RESULT OSN QUERY OS_NAME)
    cmake_host_system_information(RESULT OS_VERSION QUERY OS_RELEASE)
    cmake_host_system_information(RESULT PROC QUERY PROCESSOR_DESCRIPTION)

    message(STATUS "-------------------------------------")
    message(STATUS "  Project: ${PROJECT_NAME}")
    message(STATUS "  Version: ${CMAKE_PROJECT_VERSION}")
    message(STATUS "  C++ ${CMAKE_CXX_STANDARD}")
    message(STATUS "  C ${CMAKE_C_STANDARD}")
    message(STATUS "-------------------------------------")
    message(STATUS " ${HOST}")
    message(STATUS " ${OSN}: ${OS_VERSION}")
    message(STATUS " ${PROC}")
    message(STATUS "-------------------------------------")

    set(BUILD_EXAMPLES ON)
    set(BUILD_GTESTS ON)

    FetchContent_Declare(
        gtest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    list(APPEND libs gtest)
else()
    message(STATUS "-> ${Cyan}${PROJECT_NAME} is submodule${Reset}")
    set(BUILD_EXAMPLES OFF)
    set(BUILD_GTESTS OFF)
endif()

# Threads -----------------
# find_package(Threads REQUIRED)
# if(Threads_FOUND)
#     message(STATUS ">> Threads found")
#     if(CMAKE_USE_PTHREADS_INIT)
#         message(STATUS " -> Using pthreads")
#     endif()
# else()
#     message(WARNING "*** Could not find Threads ***")
# endif()

# if(DEFINED USE_MOCK)
#     message(STATUS "Using mock interfaces")
# else()
#     message(STATUS "Not using mock interfaces")
#     set(USE_MOCK OFF)
# endif()

# gciMock -----------------
# if(USE_MOCK)
#     FetchContent_Declare(gcimock
#         GIT_REPOSITORY "https://github.com/the-guild-of-calamitous-intent/gciMock.git"
#         GIT_TAG "origin/main"
#     )
#     LIST(APPEND libs gcimock)
# endif()

# # gunther -----------------
# FetchContent_Declare(
#     gunther
#     GIT_REPOSITORY "https://github.com/gecko-robotics/gunther.git"
#     GIT_TAG "origin/main"
#     SOURCE_SUBDIR "cpp"
# )

# # marko -----------------
# FetchContent_Declare(
#     marko
#     GIT_REPOSITORY "https://github.com/gecko-robotics/marko.git"
#     GIT_TAG "origin/master"
#     SOURCE_SUBDIR "cpp"
# )

# # messages ----------------
# FetchContent_Declare(
#     messages
#     GIT_REPOSITORY "https://github.com/gecko-robotics/messages.git"
#     GIT_TAG "origin/main"
#     SOURCE_SUBDIR "cpp"
# )

# LIST(APPEND libs
#     messages
#     marko
#     gunther
# )

FetchContent_MakeAvailable( ${libs} )

# Library =====================================================================
add_library(${PROJECT_NAME} INTERFACE src)
target_include_directories(${PROJECT_NAME} INTERFACE 
  src
)
# target_link_libraries(${PROJECT_NAME}
#     INTERFACE
#         marko
#         messages
#         gunther
# )

message(STATUS "Building ${PROJECT_NAME} examples is ${BUILD_EXAMPLES}")
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# message(STATUS "Building ${PROJECT_NAME} gtests is ${BUILD_GTESTS}")
# if(BUILD_GTESTS)
#     add_subdirectory(gtests)
# endif()

