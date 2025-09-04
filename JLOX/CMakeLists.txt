cmake_minimum_required(VERSION 3.26.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(jlox CXX)

set(CMAKE_CXX_COMPILER "clang++")

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(jlox ${SOURCES})

target_include_directories(jlox PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
)

target_compile_options(jlox PRIVATE -Wall -Wextra -Werror)
