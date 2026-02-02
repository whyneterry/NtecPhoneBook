#pragma once

#include "dto/DTOs.hpp"

namespace DTOUtils {
    
bool copyRequestToRequest(const oatpp::Object<RequestContactCreateDto>& source, oatpp::Object<RequestContactCreateDto>& destination);

}