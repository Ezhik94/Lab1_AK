cmake_minimum_required(VERSION 3.2)
project(Lab1_AK2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Lab1_AK2_SOURCE_DIR})
set(SOURCE_FILES main.cpp BigInt.h)
add_executable(Lab1_AK2 ${SOURCE_FILES})

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
add_executable(unittest unittest.cpp BigInt.h)

target_link_libraries(unittest
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )

add_test(unittest unittest)