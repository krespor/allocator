cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME testBlockAloocator)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

include_directories("../include")
add_executable(${PROJECT_NAME} testBlockAllocator.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/../build/libblockAllocator.a)