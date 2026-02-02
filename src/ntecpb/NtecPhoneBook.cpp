#include "NtecPhoneBook.hpp"

#include "app/AppComponent.hpp"
#include "oatpp/macro/component.hpp"

namespace NTEC {

const char* RequestHandler::rootPage {
    "Welcome to NtecPhoneBook!\n"
    "How to use it:\n"
    "/ - GET root page (you're here right now)\n"
    "/create - POST contact to the database (json format)\n"
    "/update?id=1337 - PATCH contact information\n"
    "/update/byname?personName=Ivan%20Ivanov\n"
    "/contact?id=1337 - GET contact information\n"
    "/contact/byname?personName=Ivan%20Ivanov\n"
    "/contact/all\n"
    "/delete?id=1337 - DELETE contact information\n"
    "/delete/byname?personName=Ivan%20Ivanov\n"
};

oatpp::Object<ResponseContactCreateDto> RequestHandler::handleRequestContactCreate(const oatpp::Object<RequestContactCreateDto>& requestContactCreateDto)
{
    auto id = personNameToId(requestContactCreateDto->personName);
    bool isInserted = m_phoneBook.insert({ id, requestContactCreateDto });
    if (!isInserted)
    {
        throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_409, "ERROR /create.\nPerson already exists. Use /update to update information instead.");
    }

    auto response = oatpp::Object<ResponseContactCreateDto>::createShared();
    fillResponse(response, id, requestContactCreateDto);

    return response;
}

oatpp::Object<ResponseContactCreateDto> RequestHandler::handleRequestContactUpdate(unsigned contactId, const oatpp::Object<RequestContactCreateDto>& requestContactUpdateDto)
{
    auto response = oatpp::Object<ResponseContactCreateDto>::createShared();
    contactId = updateContact(contactId, requestContactUpdateDto);
    fillResponse(response, contactId, requestContactUpdateDto);
    return response;
}

oatpp::Object<ResponseContactCreateDto> RequestHandler::handleRequestContactGetById(unsigned contactId) const
{
    auto contactIterator = m_phoneBook.find(contactId);
    if (!contactIterator.has_value())
    {
        throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_404, "ERROR /update.\nPerson with this ID/Name doesn't exist. Use /create to create one instead.");
    }
    auto response = oatpp::Object<ResponseContactCreateDto>::createShared();
    fillResponse(response, contactId, contactIterator.value().second);
    return response;
}

oatpp::Object<ResponseContactCreateDto> RequestHandler::handleRequestContactGetByName(const oatpp::String& contactName) const
{
    auto response = handleRequestContactGetById(personNameToId(*contactName));
    return response;
}

oatpp::String RequestHandler::handleRequestContactGetAll() const
{
    OATPP_COMPONENT(std::shared_ptr<oatpp::json::ObjectMapper>, objectMapper);
    oatpp::String jsonStringResponse{""};

    auto phoneBookCopy = m_phoneBook.copyAsShared();
    if (phoneBookCopy->empty())
    {
        throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_404, "ERROR /contact/all.\nPhoneBook is empty. Use /create to create contacts.");
    }
    for (const auto& contact : *phoneBookCopy)
    {
        auto response = oatpp::Object<ResponseContactCreateDto>::createShared();
        fillResponse(response, contact.first, contact.second);
        jsonStringResponse->append(objectMapper->writeToString(response));
    }
    return jsonStringResponse;
}

void RequestHandler::handleRequestContactDeleteById(unsigned contactId)
{
    auto isErased = m_phoneBook.erase(contactId);
    if (!isErased)
    {
        throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_404, "ERROR /delete.\nPerson with this ID/Name doesn't exist. Use /create to create one instead.");
    }
}

void RequestHandler::handleRequestContactDeleteByName(const oatpp::String& contactName)
{
    handleRequestContactDeleteById(personNameToId(contactName));
}

std::shared_ptr<RequestHandler> RequestHandler::createShared()
{
    return std::make_shared<RequestHandler>();
}

// Name to Id hash function using djb2 algorithm 
unsigned RequestHandler::personNameToId(const std::string& personName) const
{
    return djb2hash(personName);
}

const char* const RequestHandler::getRootPage()
{
    return RequestHandler::rootPage;
}

void RequestHandler::fillResponse(oatpp::Object<ResponseContactCreateDto>& response, const unsigned id, const oatpp::Object<RequestContactCreateDto>& responseFiller) const
{
    response->personId = id;
    if(responseFiller->personName) { response->personName = responseFiller->personName; }
    if(responseFiller->personPhoneNumber) { response->personPhoneNumber = responseFiller->personPhoneNumber; }
    if(responseFiller->personAddress) { response->personAddress = responseFiller->personAddress; }
}

const unsigned RequestHandler::updateContact(unsigned contactId, const oatpp::Object<RequestContactCreateDto>& requestContactUpdateDto)
{
    try
    {
        auto contactIdToReturn = m_phoneBook.update(contactId, requestContactUpdateDto);
        return contactIdToReturn;
    }
    catch(std::invalid_argument& updateException)
    {
        OATPP_LOGe("RequestHandler", updateException.what());
        throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_400, "ERROR /update.\nPerson is not exist. Use /create to create one instead.");
    }
}

}