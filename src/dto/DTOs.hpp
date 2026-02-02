#pragma once

#include "oatpp/data/mapping/ObjectMapper.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class RequestContactCreateDto : public oatpp::DTO
{
    DTO_INIT(RequestContactCreateDto, DTO)

    DTO_FIELD(String, personName);
    DTO_FIELD(String, personPhoneNumber);
    DTO_FIELD(String, personAddress);
};

// Response includes all fields from Request and additionally provide personId
class ResponseContactCreateDto : public RequestContactCreateDto
{
    DTO_INIT(ResponseContactCreateDto, RequestContactCreateDto)

    DTO_FIELD(UInt32, personId);
};

#include OATPP_CODEGEN_END(DTO)