#include "DTOUtils.hpp"

namespace DTOUtils {

// Copies all non-empty field from one Request object to another
bool copyRequestToRequest(const oatpp::Object<RequestContactCreateDto>& source, oatpp::Object<RequestContactCreateDto>& destination) {
    bool nameChange = false;

    if(source->personName && !(source->personName->empty())) {
        destination->personName = source->personName;
        nameChange = true;
    }
    if(source->personPhoneNumber && !(source->personPhoneNumber->empty())) {
        destination->personPhoneNumber = source->personPhoneNumber;
    }
    if(source->personAddress && !(source->personAddress->empty())) {
        destination->personAddress = source->personAddress;
    }
    
    return nameChange;
}

}