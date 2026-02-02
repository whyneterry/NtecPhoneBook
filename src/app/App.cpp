#include "AppComponent.hpp"
#include "oatpp-swagger/Controller.hpp"
#include "controller/MyController.hpp"
#include "oatpp/network/Server.hpp"

void run() {
    AppComponent components;
    
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    OATPP_COMPONENT(std::shared_ptr<oatpp::json::ObjectMapper>, objectMapper);
    OATPP_COMPONENT(std::shared_ptr<NTEC::RequestHandler>, requestHandler);
    auto myController = MyController::createShared(objectMapper, requestHandler);
    router->addController(myController);

    oatpp::web::server::api::Endpoints docEndpoints;
    docEndpoints.append(myController->getEndpoints());
    auto swaggerController = oatpp::swagger::Controller::createShared(docEndpoints);
    router->addController(swaggerController);

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    oatpp::network::Server server(connectionProvider, connectionHandler);

    OATPP_LOGi("APP", std::format("Server running on port {}", connectionProvider->getProperty("port").std_str()));

    server.run();
}

int main()
{
	oatpp::Environment::init();

	run();
    
	oatpp::Environment::destroy();
	return 0;
}