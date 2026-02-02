#pragma once

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "dto/DTOs.hpp"
#include "hash/djb2.hpp"
#include "ThreadSafeMap.hpp"
#include <iostream>
#include <string>
#include <map>
#include <regex> // TODO: Perform validation for user input

namespace NTEC
{
class RequestHandler
{
public:
    RequestHandler() = default;
    // Public methods for handling requests
    oatpp::Object<ResponseContactCreateDto> handleRequestContactCreate(const oatpp::Object<RequestContactCreateDto>& requestContactCreateDto);
    oatpp::Object<ResponseContactCreateDto> handleRequestContactUpdate(unsigned contactId, const oatpp::Object<RequestContactCreateDto>& requestContactUpdateDto);
    oatpp::Object<ResponseContactCreateDto> handleRequestContactGetById(unsigned contactId) const;
    oatpp::Object<ResponseContactCreateDto> handleRequestContactGetByName(const oatpp::String& contactName) const;
    oatpp::String handleRequestContactGetAll() const;
    void handleRequestContactDeleteById(unsigned contactId);
    void handleRequestContactDeleteByName(const oatpp::String& contactName);

    // Public helper methods
    static std::shared_ptr<RequestHandler> createShared();
    unsigned personNameToId(const std::string& personName) const;

    // Public helper static methods
    static const char* const getRootPage();

private:
    ThreadSafeMapPhoneBook m_phoneBook{};

    // Pure text root page
    static const char* rootPage;
    // Private helper methods
    void fillResponse(oatpp::Object<ResponseContactCreateDto>& response, const unsigned id, const oatpp::Object<RequestContactCreateDto>& responseFiller) const;
    const unsigned updateContact(unsigned contactId, const oatpp::Object<RequestContactCreateDto>& requestContactUpdateDto);
};
}