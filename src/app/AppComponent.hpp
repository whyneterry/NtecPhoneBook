#pragma once

#include "SwaggerComponent.hpp"
#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/macro/component.hpp"
#include "ntecpb/NtecPhoneBook.hpp"

class AppComponent {
public:
    SwaggerComponent swaggerComponent;

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4});
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::handler::DefaultErrorHandler>, errorHandler)([] {
        return std::make_shared<oatpp::web::server::handler::DefaultErrorHandler>();
    }());
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::handler::DefaultErrorHandler>, errorHandler);
        auto serverConnectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
        serverConnectionHandler->setErrorHandler(errorHandler);
        return serverConnectionHandler;
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::json::ObjectMapper>, objectMapper)([] {
        auto objectMapper = std::make_shared<oatpp::json::ObjectMapper>();
        objectMapper->deserializerConfig().mapper.allowUnknownFields = false;
        objectMapper->serializerConfig().mapper.includeNullFields = false;
        objectMapper->serializerConfig().json.useBeautifier = true;
        return objectMapper;
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<NTEC::RequestHandler>, requestHandler)([]{
        return NTEC::RequestHandler::createShared();
    }());
};

class MessageDto;