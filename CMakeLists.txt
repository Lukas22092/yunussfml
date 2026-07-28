cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_COMPILER $ENV{HOME}/.local/clang-p2996/bin/clang++)

project(template CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/* ${CMAKE_CURRENT_SOURCE_DIR}/include/*)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
    -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wnull-dereference
    -Wdouble-promotion -Wformat=2
    -freflection -fexpansion-statements -stdlib=libc++)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 26)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
