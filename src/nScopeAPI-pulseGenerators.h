#include "globalnScope.h"

namespace nScope {

    H_NAPI_GET_SET_FUNCTION(Boolean, PX_on)
    H_NAPI_GET_SET_FUNCTION(Number, PX_duty_percentage)
    H_NAPI_GET_SET_FUNCTION(Number, PX_frequency_in_hz)
    H_NAPI_GET_SET_FUNCTION(Number, PX_period_in_ms)
    H_NAPI_GET_SET_FUNCTION(Number, PX_period_in_us)
    H_NAPI_GET_SET_FUNCTION(Number, PX_pulse_width_in_ms)
    H_NAPI_GET_SET_FUNCTION(Number, PX_pulse_width_in_us)
    H_NAPI_FUNCTION(Boolean, send_PX_oneshot_pulse)

    Napi::Object InitPulseGenerators(Napi::Env env, Napi::Object exports);
    
}