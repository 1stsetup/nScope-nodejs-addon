#include "globalnScope.h"

namespace nScope {

    H_NAPI_GET_SET_FUNCTION(Boolean, AX_on)
    H_NAPI_GET_SET_FUNCTION(Boolean, AX_unipolar)
    H_NAPI_GET_SET_FUNCTION(Number, AX_wave_type)
    H_NAPI_GET_SET_FUNCTION(Number, AX_frequency_in_hz)
    H_NAPI_GET_SET_FUNCTION(Number, AX_amplitude)

    Napi::Object InitAnalogOutputs(Napi::Env env, Napi::Object exports);
    
}