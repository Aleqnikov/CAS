cmake_minimum_required(VERSION 3.14)
project(cas)

set(CMAKE_CXX_STANDARD 17)

# Библиотека
add_library(cas lib/src/main.cpp)
target_include_directories(cas PUBLIC ${CMAKE_SOURCE_DIR}/lib/src)

# Тесты
add_subdirectory(lib/tests)