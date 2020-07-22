#include "globalnScope.h"

namespace nScope {

    H_NAPI_FUNCTION(Boolean, open)
    H_NAPI_FUNCTION(Boolean, close)
    H_NAPI_FUNCTION(Number, get_power_state)
    H_NAPI_FUNCTION(Number, get_power_usage)
    H_NAPI_FUNCTION(Number, check_API_version)
    H_NAPI_FUNCTION(Number, check_API_build)
    H_NAPI_FUNCTION(Number, check_FW_version)
    H_NAPI_FUNCTION(Boolean, load_firmware);
    H_NAPI_FUNCTION(Boolean, write_to_loader);
    H_NAPI_FUNCTION(Boolean, find_firmware_loader);

    Napi::Object InitAPI(Napi::Env env, Napi::Object exports);
    
}