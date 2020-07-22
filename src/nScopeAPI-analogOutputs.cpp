#include "nScopeAPI-analogOutputs.h"

namespace nScope {

    H_NAPI_GET_SET_FUNCTION(Boolean, AX_on)
    H_NAPI_GET_SET_FUNCTION(Boolean, AX_unipolar)
    H_NAPI_GET_SET_FUNCTION(Number, AX_wave_type)
    H_NAPI_GET_SET_FUNCTION(Number, AX_frequency_in_hz)
    H_NAPI_GET_SET_FUNCTION(Number, AX_amplitude)

CALL_NSCOPE_GET_SET_BY_HANDLE_CH(AX_on, bool, Boolean)
CALL_NSCOPE_GET_SET_BY_HANDLE_CH(AX_unipolar, bool, Boolean)
CALL_NSCOPE_GET_BY_HANDLE_CH(AX_wave_type, WaveType, Number)
Napi::Boolean set_AX_wave_type(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Number ch = info[0].As<Napi::Number>();
    Napi::Number value = info[1].As<Napi::Number>();
    if (value.Int32Value() == 0) {
        CALL_NSCOPE_FUNCTION(nScope_set_AX_wave_type, getHandle(), ch, SINE_WAVE)
    }
    else {
        CALL_NSCOPE_FUNCTION(nScope_set_AX_wave_type, getHandle(), ch, TRIANGLE_WAVE)
    }
    return Napi::Boolean::New(env, getLastError() == SUCCESS);
}

CALL_NSCOPE_GET_SET_BY_HANDLE_CH(AX_frequency_in_hz, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE_CH(AX_amplitude, double, Number)

Napi::Object InitAnalogOutputs(Napi::Env env, Napi::Object exports) {
    NAPI_GET_SET_FUNCTION_EXPORT(AX_on);
    NAPI_GET_SET_FUNCTION_EXPORT(AX_unipolar);
    NAPI_GET_SET_FUNCTION_EXPORT(AX_wave_type);

    NAPI_GET_SET_FUNCTION_EXPORT(AX_frequency_in_hz);
    NAPI_GET_SET_FUNCTION_EXPORT(AX_amplitude);
    return exports;
}

}

