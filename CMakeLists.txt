cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME blockAllocator)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

if(NOT DEFINED POOL_SIZE)
    message( FATAL_ERROR "missing argument POOL_SIZE" )
endif()

if(NOT DEFINED BLOCK_SIZE)
    message( FATAL_ERROR "missing argument BLOCK_SIZE" )
endif()

math(EXPR value "${POOL_SIZE} % ${BLOCK_SIZE}")
if (${value})
    message( FATAL_ERROR "POOL_SIZE % BLOCK_SIZE = ${value}")
endif()

add_definitions(-DPOOL_SIZE=${POOL_SIZE})
add_definitions(-DBLOCK_SIZE=${BLOCK_SIZE})

set(LIBRARY_HEADERS_DIR include)
set(LIBRARY_SOURCE_DIR source)

set(LIBRARY_HEADERS
    ${LIBRARY_HEADERS_DIR}/Allocator.h
)

set(LIBRARY_SOURCE
    ${LIBRARY_SOURCE_DIR}/Allocator.cpp
)

add_library(${PROJECT_NAME} ${LIBRARY_HEADERS} ${LIBRARY_SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC include)