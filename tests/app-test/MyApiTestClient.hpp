#pragma once

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/macro/codegen.hpp"
#include "dto/DTOs.hpp"

#include OATPP_CODEGEN_BEGIN(ApiClient)

class MyApiTestClient : public oatpp::web::client::ApiClient {

    API_CLIENT_INIT(MyApiTestClient)
    
    API_CALL("GET", "/", root)

    API_CALL("GET", "/contact", getContactById,
            QUERY(UInt32, contactId, "id"))

    API_CALL("GET", "/contact/byname", getContactByName,
        QUERY(String, contactName, "personName"))

    API_CALL("GET", "/contact/all", getContactAll)

    API_CALL("POST", "/create", createContact,
        BODY_DTO(Object<RequestContactCreateDto>, requestContactCreateDto))

    API_CALL("PATCH", "/update", updateContactById,
            BODY_DTO(Object<RequestContactCreateDto>, requestContactUpdateDto),
            QUERY(UInt32, contactId, "id"))

    API_CALL("PATCH", "/update/byname", updateContactByName,
            BODY_DTO(Object<RequestContactCreateDto>, requestContactUpdateDto),
            QUERY(String, contactName, "personName"))

    API_CALL("DELETE", "/delete", deleteContactById,
            QUERY(UInt32, contactId, "id"))

    API_CALL("DELETE", "/delete/byname", deleteContactByName,
            QUERY(String, contactName, "personName"))

    // Raw json api calls
    API_CALL("POST", "/create", createContactRaw,
        HEADER(String, contentType, "Content-Type"),
        BODY_STRING(String, body))
    
    API_CALL("PATCH", "/update", updateContactByIdRaw,
        HEADER(String, contentType, "Content-Type"),
        BODY_STRING(String, body),
        QUERY(UInt32, id, "id"))
    
    API_CALL("PATCH", "/update/byname", updateContactByNameRaw,
        HEADER(String, contentType, "Content-Type"),
        BODY_STRING(String, body),
        QUERY(String, personName, "personName"))
};

#include OATPP_CODEGEN_END(ApiClient)