cmake_minimum_required(VERSION 3.14)
project(cas)

set(CMAKE_CXX_STANDARD 20)

# 1. Поиск всех исходников библиотеки (исключая main.cpp, чтобы не было конфликта двух main)
file(GLOB_RECURSE LIB_SOURCES 
    "${CMAKE_SOURCE_DIR}/lib/src/**/*.cpp"
)
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_SOURCE_DIR}/lib/src/main.cpp")

# 2. Создание библиотеки
add_library(cas ${LIB_SOURCES})

# Пробрасываем пути так, чтобы корень поиска был в lib/src
target_include_directories(cas PUBLIC 
    "${CMAKE_SOURCE_DIR}/lib/src"
)

# 3. Создание исполняемого файла из твоего main.cpp
add_executable(cas_run "${CMAKE_SOURCE_DIR}/lib/src/main.cpp")

# Линкуем библиотеку к экзешнику
target_link_libraries(cas_run PRIVATE cas)

# 4. Подключаем тесты
add_subdirectory(lib/tests)