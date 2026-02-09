cmake_minimum_required(VERSION 3.14)
project(cas)

set(CMAKE_CXX_STANDARD 20)

# 1. Собираем все .cpp файлы библиотеки
# GLOB_RECURSE пойдет вглубь lib/src и найдет и токенизатор, и структуры
file(GLOB_RECURSE LIB_SOURCES
        "lib/src/**/*.cpp"
)

# Удаляем main.cpp из списка файлов библиотеки, чтобы не было конфликта при линковке
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_SOURCE_DIR}/lib/src/main.cpp")

# 2. Создаем основную библиотеку нашего CAS
add_library(cas ${LIB_SOURCES})

# 3. Настраиваем пути поиска заголовочных файлов
# Указываем lib/src базовой директорией, чтобы инклюды выглядели логично
target_include_directories(cas PUBLIC
        "${CMAKE_SOURCE_DIR}/lib/src"
)

# 4. Создаем исполняемый файл
add_executable(cas_run "lib/src/main.cpp")

# Привязываем библиотеку к экзешнику
target_link_libraries(cas_run PRIVATE cas)

# 5. Подключаем тесты (они лежат в lib/tests)
add_subdirectory(lib/tests)