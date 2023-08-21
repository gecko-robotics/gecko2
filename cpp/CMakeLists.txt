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

if(DEFINED USE_MOCK)
    message(STATUS "Using mock interfaces")
else()
    message(STATUS "Not using mock interfaces")
    set(USE_MOCK OFF)
endif()

include(FetchContent)

# gciMock -----------------
if(USE_MOCK)
    FetchContent_Declare(gcimock
        GIT_REPOSITORY "git@github.com:the-guild-of-calamitous-intent/gciMock.git"
        GIT_TAG "origin/main"
        SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/gcimock"
    )
    LIST(APPEND libs gcimock)
endif()

# yivo -----------------
# FetchContent_Declare(yivo
#   GIT_REPOSITORY "git@github.com:MomsFriendlyRobotCompany/yivo.git"
#   GIT_TAG "origin/main"
#   SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/yivo"
#   SOURCE_SUBDIR "cpp"
# )

# # gciSensors -----------------
# FetchContent_Declare(gcisensors
#   GIT_REPOSITORY "git@github.com:the-guild-of-calamitous-intent/gciSensors.git"
#   GIT_TAG "origin/main"
#   SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/gcisensors"
# )

# squaternion -----------------
# FetchContent_Declare(squaternion
#   GIT_REPOSITORY "git@github.com:MomsFriendlyRobotCompany/squaternion.git"
#   GIT_TAG "origin/master"
#   SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/squaternion"
#   SOURCE_SUBDIR "cpp"
# )

# marko -----------------
FetchContent_Declare(marko
    GIT_REPOSITORY "https://github.com/gecko-robotics/marko.git"
    GIT_TAG "origin/master"
    SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/marko"
    SOURCE_SUBDIR "cpp"
)

# messages ----------------
FetchContent_Declare(messages
    GIT_REPOSITORY "https://github.com/gecko-robotics/messages.git"
    GIT_TAG "origin/main"
    SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/messages"
    SOURCE_SUBDIR "cpp"
)

LIST(APPEND libs
    messages
    marko
)

FetchContent_MakeAvailable( ${libs} )

foreach(lib ${libs})
    if(${lib}_POPULATED)
        message(STATUS "=> Found ${lib}")
    else()
        message(STATUS "*** Didn't find ${lib}")
    endif()
endforeach()


# Library =====================================================================
add_library(${PROJECT_NAME} INTERFACE src)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        # ${CMAKE_SOURCE_DIR}/src
        # ${marko_SOURCE_DIR}cpp/src/include
        # ${gcimock_SOURCE_DIR}/include
        # ${yivo_SOURCE_DIR}/src
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:cpp/src>  # <prefix>/include/mylib
)
target_link_libraries(${PROJECT_NAME}
INTERFACE
        marko
        messages
        # yivo
        # Threads::Threads
)

message(STATUS "Building ${PROJECT_NAME} examples is ${BUILD_EXAMPLES}")
if(BUILD_EXAMPLES)
    add_subdirectory(examples/messages)
    # add_subdirectory(examples/quad)
endif()

# message(STATUS "Building ${PROJECT_NAME} gtests is ${BUILD_GTESTS}")
# if(BUILD_GTESTS)
#     add_subdirectory(gtests)
# endif()

