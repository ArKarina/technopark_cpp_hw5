cmake_minimum_required(VERSION 3.16)
project(Set)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Wpedantic -Werror -fprofile-arcs -ftest-coverage -fPIC -O0")

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC})

add_executable(app ${SRC})

enable_testing()
add_subdirectory(test)