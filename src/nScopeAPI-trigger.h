#include "globalnScope.h"

namespace nScope {

    H_NAPI_GET_SET_FUNCTION(Number, trigger_delay_ms)
    H_NAPI_GET_SET_FUNCTION(Number, trigger_delay_us)
    H_NAPI_GET_SET_FUNCTION(Number, trigger_edge)
    H_NAPI_GET_SET_FUNCTION(Number, trigger_level)
    H_NAPI_GET_SET_FUNCTION(Boolean, trigger_on)
    H_NAPI_GET_SET_FUNCTION(Number, trigger_source)

    Napi::Object InitTriggers(Napi::Env env, Napi::Object exports);
    
}