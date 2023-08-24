include(FetchContent)

# # GTest -----------------
# FetchContent_Declare(
#     gtest
#     URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
# )
# FetchContent_Declare(gtest
#   GIT_REPOSITORY "https://github.com/google/googletest"
#   GIT_TAG "origin/main"
#   SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/gtest"
# )

# FetchContent_MakeAvailable(gtest)

# if(gtest_POPULATED)
#     message(STATUS "=> Found gtest")
# else()
#     message(STATUS "*** Didn't find gtest")
# endif()

#----------------------------
enable_testing()

list(APPEND gtests
    fsm.cpp
    blackbox.cpp
    messages.cpp
)

# message(STATUS "gTests ----------------------")
# foreach(src ${gtests})
#     get_filename_component(name ${src} NAME_WE)
#     # message(STATUS " -> ${name}")
#     add_executable(${name} ${name}.cpp)
#     target_link_libraries(${name}
#         GTest::gtest_main
#         ${PROJECT_NAME})
#     add_test(NAME ${name} COMMAND ${name})
# endforeach()

# include(GoogleTest)
# gtest_discover_tests(${gci-gtests})

# run all tests
add_executable(test-all ${gtests})
target_link_libraries(test-all GTest::gtest_main ${PROJECT_NAME})
# add_test(NAME test-all COMMAND test-all)
include(GoogleTest)
gtest_discover_tests(test-all)