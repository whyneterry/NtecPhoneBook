#pragma once

#include "dto/DTOs.hpp"
#include "ntecpb/NtecPhoneBook.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/encoding/Url.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
private:
    std::shared_ptr<NTEC::RequestHandler> m_requestHandler;
public:
    MyController(const std::shared_ptr<ObjectMapper>& objectMapper, const std::shared_ptr<NTEC::RequestHandler>& requestHandler)
        : oatpp::web::server::api::ApiController(objectMapper),
        m_requestHandler(requestHandler)
    {}

    static std::shared_ptr<MyController> createShared(const std::shared_ptr<ObjectMapper>& objectMapper, const std::shared_ptr<NTEC::RequestHandler>& requestHandler)
    {
        return std::make_shared<MyController>(objectMapper, requestHandler);
    }

    ENDPOINT_INFO(root)
    {
        info->summary = "Root page with some information about using the app.";
    }
    ENDPOINT("GET", "/", root)
    {
        OATPP_LOGd("ENDPOINT HIT", "GET /");
        return ResponseFactory::createResponse(Status::CODE_200, NTEC::RequestHandler::getRootPage());
    }

    ENDPOINT_INFO(getContactById)
    {
        info->summary = "Get contact information by ID";
        info->queryParams["id"].description = "ID of the person to find in the Phonebook.";
    }
    // Maybe I should rework this with optional query params
    ENDPOINT("GET", "/contact", getContactById,
            QUERY(UInt32, contactId, "id"))
    {
        OATPP_LOGd("ENDPOINT HIT", "GET /contact By ID");
        try
        {
            auto responseContactGetById = m_requestHandler->handleRequestContactGetById(contactId);
            return createDtoResponse(Status::CODE_200, responseContactGetById);
        }
        catch (oatpp::web::protocol::http::HttpError&)
        {
            OATPP_LOGe("ERROR", "GET /contact By ID");
            throw; // rethrow to OATPP DefaultErrorHandler
        }
    }
    
    ENDPOINT_INFO(getContactByName)
    {
        info->summary = "Get contact information by name.";
        info->queryParams["personName"].description = "Name of the person to find in the Phonebook.";
    }
    ENDPOINT("GET", "/contact/byname", getContactByName,
            QUERY(String, contactName, "personName"))
    {
        OATPP_LOGd("ENDPOINT HIT", "GET /contact By Name");
        auto decodedContactName = oatpp::encoding::Url::decode(contactName);
        try
        {
            auto responseContactGetById = m_requestHandler->handleRequestContactGetByName(decodedContactName);
            return createDtoResponse(Status::CODE_200, responseContactGetById);
        }
        catch (oatpp::web::protocol::http::HttpError&)
        {
            OATPP_LOGe("ERROR", "GET /contact By Name");
            throw;
        }
    }

    ENDPOINT_INFO(getContactAll)
    {
        info->summary = "Get information about all persons in the Phonebook.";
    }
    ENDPOINT("GET", "/contact/all", getContactAll)
    {
        OATPP_LOGd("ENDPOINT HIT", "GET /contact/all");
        try
        {
            auto jsonStringResponse = m_requestHandler->handleRequestContactGetAll();
            return ResponseFactory::createResponse(Status::CODE_200, jsonStringResponse->c_str());
        }
        catch(oatpp::web::protocol::http::HttpError&)
        {
            OATPP_LOGe("ERROR", "GET /contact/all");
            throw;
        }
    }
    
    ENDPOINT_INFO(createContact)
    {
        info->summary = "Add information about some person to the Phonebook.";
        info->addConsumes<oatpp::Object<RequestContactCreateDto>>("application/json");
        info->addResponse<oatpp::Object<ResponseContactCreateDto>>(Status::CODE_200, "application/json");
    }
    ENDPOINT("POST", "/create", createContact,
                BODY_DTO(Object<RequestContactCreateDto>, requestContactCreateDto))
    {
        OATPP_LOGd("ENDPOINT HIT", "POST /create");
        try
        {
            auto responseContactCreate = m_requestHandler->handleRequestContactCreate(requestContactCreateDto);
            return createDtoResponse(Status::CODE_201, responseContactCreate);
        }
        catch(oatpp::web::protocol::http::HttpError&)
        {
            OATPP_LOGe("ERROR", "POST /create");
            throw;
        }
    }

    ENDPOINT_INFO(updateContactById)
    {
        info->summary = "Update information about some person in the Phonebook by ID.";
        info->addConsumes<oatpp::Object<RequestContactCreateDto>>("application/json");
        info->addResponse<oatpp::Object<ResponseContactCreateDto>>(Status::CODE_200, "application/json");
        info->queryParams["id"].description = "Information about person with this ID will be updated.";
    }
    ENDPOINT("PATCH", "/update", updateContactById,
                BODY_DTO(Object<RequestContactCreateDto>, requestContactUpdateDto),
                QUERY(UInt32, contactId, "id"))
    {
        OATPP_LOGd("ENDPOINT HIT", "PATCH /update by ID");
        try
        {
            auto responseContactCreateDto = m_requestHandler->handleRequestContactUpdate(contactId, requestContactUpdateDto);
            return createDtoResponse(Status::CODE_200, responseContactCreateDto);
        }
        catch(oatpp::web::protocol::http::HttpError&)
        {
            OATPP_LOGe("ERROR", "PATCH /update by ID");
            throw;
        }
    }

    ENDPOINT_INFO(updateContactByName)
    {
        info->summary = "Update information about some person in the Phonebook by name.";
        info->addConsumes<oatpp::Object<RequestContactCreateDto>>("application/json");
        info->addResponse<oatpp::Object<ResponseContactCreateDto>>(Status::CODE_200, "application/json");
        info->queryParams["personName"].description = "Information about person with this NAME will be updated.";
    }
    ENDPOINT("PATCH", "/update/byname", updateContactByName,
                BODY_DTO(Object<RequestContactCreateDto>, requestContactUpdateDto),
                QUERY(String, contactName, "personName"))
    {
        OATPP_LOGd("ENDPOINT HIT", "PATCH /update By Name");
        try
        {
            auto decodedContactName = oatpp::encoding::Url::decode(contactName);
            auto contactId = m_requestHandler->personNameToId(decodedContactName);
            auto responseContactCreateDto = m_requestHandler->handleRequestContactUpdate(contactId, requestContactUpdateDto);
            return createDtoResponse(Status::CODE_200, responseContactCreateDto);
        }
        catch(oatpp::web::protocol::http::HttpError&)
        {
            OATPP_LOGe("ERROR", "PATCH /update by Name");
            throw;
        }
    }

    ENDPOINT_INFO(deleteContactById)
    {
        info->summary = "Delete information about some person from the Phonebook by ID.";
        info->queryParams["id"].description = "Information about person with this ID will be deleted.";
    }
    ENDPOINT("DELETE", "/delete", deleteContactById,
                QUERY(UInt32, contactId, "id"))
    {
        OATPP_LOGd("ENDPOINT HIT", "DELETE /delete By ID");
        try
        {
            m_requestHandler->handleRequestContactDeleteById(contactId);
            return ResponseFactory::createResponse(Status::CODE_200, "Deleted succesfully.");
        }
        catch(oatpp::web::protocol::http::HttpError&)
        {
            OATPP_LOGe("ERROR", "DELETE /delete By ID");
            throw;
        }
    }

    ENDPOINT_INFO(deleteContactByName)
    {
        info->summary = "Delete information about some person from the Phonebook by name.";
        info->queryParams["personName"].description = "Information about person with this NAME will be deleted.";
    }
    ENDPOINT("DELETE", "/delete/byname", deleteContactByName,
                QUERY(String, contactName, "personName"))
    {
        OATPP_LOGd("ENDPOINT HIT", "DELETE /delete By Name");
        try
        {
            auto decodedContactName = oatpp::encoding::Url::decode(contactName);
            m_requestHandler->handleRequestContactDeleteByName(decodedContactName);
            return ResponseFactory::createResponse(Status::CODE_200, "Deleted succesfully.");
        }
        catch(oatpp::web::protocol::http::HttpError&)
        {
            OATPP_LOGe("ERROR", "DELETE /delete By Name");
            
            throw;
        }
    }
};

#include OATPP_CODEGEN_END(ApiController) ///< End Codegen