#pragma once

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/macro/component.hpp"

/**
 *  Swagger ui is served at
 *  http://host:port/swagger/ui
 */
class SwaggerComponent {
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {
    oatpp::swagger::DocumentInfo::Builder builder;

    builder
        .setTitle("NtecPhoneBook")
        .setDescription("NtecPhoneBook test project with swagger docs")
        .setVersion("1.0")
        .setContactName("Pavel Mochalov")

        .setLicenseName("Apache License, Version 2.0")
        .setLicenseUrl("http://www.apache.org/licenses/LICENSE-2.0")

        .addServer("http://localhost:8000", "server on localhost");
    return builder.build();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
    // Make sure to specify correct full path to oatpp-swagger/res folder !!!
    return oatpp::swagger::Resources::loadResources("C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/res");
    }());
};