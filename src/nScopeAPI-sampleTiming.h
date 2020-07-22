#include "globalnScope.h"


namespace nScope {

    H_NAPI_GET_SET_FUNCTION(Number, sample_rate_in_hz)
    H_NAPI_GET_SET_FUNCTION(Number, time_between_samples_in_minutes)
    H_NAPI_GET_SET_FUNCTION(Number, time_between_samples_in_ms)
    H_NAPI_GET_SET_FUNCTION(Number, time_between_samples_in_seconds)
    H_NAPI_GET_SET_FUNCTION(Number, time_between_samples_in_us)

    Napi::Object InitSampleTiming(Napi::Env env, Napi::Object exports);
    
}