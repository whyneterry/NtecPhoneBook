add_executable(${CMAKE_PROJECT_NAME}-tests
    ${CMAKE_CURRENT_SOURCE_DIR}/Tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MyControllerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/app-test/MyApiTestClient.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/app-test/TestComponent.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MyControllerTest.hpp
)

target_include_directories(${CMAKE_PROJECT_NAME}-tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${CMAKE_PROJECT_NAME}-tests
    PRIVATE
        ${CMAKE_PROJECT_NAME}-lib
        oatpp-lib
        oatpp-test-lib
        oatpp-swagger-lib
        wsock32
        ws2_32
)

add_dependencies(${CMAKE_PROJECT_NAME}-tests ${CMAKE_PROJECT_NAME}-lib)