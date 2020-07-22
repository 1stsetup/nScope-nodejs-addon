#include "globalnScope.h"

namespace nScope {

    H_NAPI_GET_SET_FUNCTION(Boolean, ChX_on)
    H_NAPI_GET_SET_FUNCTION(Number, ChX_gain)
    H_NAPI_GET_SET_FUNCTION(Number, ChX_level)

    Napi::Object InitAnalogInputs(Napi::Env env, Napi::Object exports);
    
}