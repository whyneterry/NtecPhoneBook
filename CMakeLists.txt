cmake_minimum_required(VERSION 3.10)
project(NtecPhoneBookApp)

set(CMAKE_CXX_STANDARD 23)

# Прямые пути к библиотекам
set(OATPP_LIB_PATH "${CMAKE_SOURCE_DIR}/libs/oatpp/build/src/Debug/oatpp.lib")
set(OATPP_SWAGGER_LIB_PATH "${CMAKE_SOURCE_DIR}/libs/oatpp-swagger/build/src/Debug/oatpp-swagger.lib")

# Проверяем существование файлов
# Просто добавляем пути
include_directories(
    "${CMAKE_SOURCE_DIR}/libs/oatpp/src"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/libs/oatpp-swagger/src"
)

# Создаем простые targets
add_library(oatpp-lib STATIC IMPORTED)
set_target_properties(oatpp-lib PROPERTIES
    IMPORTED_LOCATION "${OATPP_LIB_PATH}"
)

add_library(oatpp-swagger-lib STATIC IMPORTED)
set_target_properties(oatpp-swagger-lib PROPERTIES
    IMPORTED_LOCATION "${OATPP_SWAGGER_LIB_PATH}"
)

# Ваши поддиректории
add_subdirectory(src)
add_subdirectory(tests)