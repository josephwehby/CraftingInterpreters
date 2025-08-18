cmake_minimum_required(VERSION 3.26.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_SDK_VERSION 10.0.26100.0)

project(jlox)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(jlox ${SOURCES})

target_include_directories(jlox PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
)

if (MSVC) 
  target_compile_options(jlox PRIVATE /W4 /bigobj)
endif()
