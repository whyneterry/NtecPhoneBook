# Ваша библиотека
add_library(${CMAKE_PROJECT_NAME}-lib
    ${CMAKE_CURRENT_SOURCE_DIR}/dto/DTOs.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dto/DTOUtils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dto/DTOUtils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ntecpb/NtecPhoneBook.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ntecpb/NtecPhoneBook.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ntecpb/ThreadSafeMap.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/hash/djb2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/hash/djb2.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/controller/MyController.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/app/AppComponent.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/app/SwaggerComponent.hpp
)

# Добавляем заголовочные файлы (они уже в основном файле, но на всякий случай)
target_include_directories(${CMAKE_PROJECT_NAME}-lib
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/libs/oatpp/src
        ${CMAKE_SOURCE_DIR}/libs/oatpp-swagger/src
)

# Линковка в зависимости от опции USE_LOCAL_OATPP
# Используем локальные библиотеки
target_link_libraries(${CMAKE_PROJECT_NAME}-lib
    PUBLIC
        oatpp-lib           # или oatpp::oatpp если создали ALIAS
        oatpp-swagger-lib   # или oatpp::oatpp-swagger
        wsock32
        ws2_32
)


# Исполняемый файл
add_executable(${CMAKE_PROJECT_NAME}-exe)
target_sources(${CMAKE_PROJECT_NAME}-exe
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/app/App.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}-exe
    PUBLIC
        ${CMAKE_PROJECT_NAME}-lib
        oatpp-lib           # или oatpp::oatpp если создали ALIAS
        oatpp-swagger-lib   # или oatpp::oatpp-swagger
)

# Порядок сборки
add_dependencies(${CMAKE_PROJECT_NAME}-exe ${CMAKE_PROJECT_NAME}-lib)