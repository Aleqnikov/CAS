cmake_minimum_required(VERSION 3.14)
project(cas)

set(CMAKE_CXX_STANDARD 17)

# Собираем все .cpp из lib/src рекурсивно
file(GLOB_RECURSE LIB_SOURCES "${CMAKE_SOURCE_DIR}/lib/src/**/*.cpp")

add_library(cas ${LIB_SOURCES})
target_include_directories(cas PUBLIC ${CMAKE_SOURCE_DIR}/lib/src)

add_subdirectory(lib/tests)