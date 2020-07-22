#include "nScopeAPI-pulseGenerators.h"

namespace nScope {

CALL_NSCOPE_GET_SET_BY_HANDLE_CH(PX_on, bool, Boolean)
CALL_NSCOPE_GET_SET_BY_HANDLE_CH(PX_duty_percentage, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE_CH(PX_frequency_in_hz, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE_CH(PX_period_in_ms, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE_CH(PX_period_in_us, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE_CH(PX_pulse_width_in_ms, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE_CH(PX_pulse_width_in_us, double, Number)

Napi::Boolean send_PX_oneshot_pulse(const Napi::CallbackInfo& info) { \
    Napi::Env env = info.Env(); \
    Napi::Number ch = info[0].As<Napi::Number>(); \
    Napi::Number value = info[1].As<Napi::Number>(); \
    CALL_NSCOPE_FUNCTION(nScope_send_PX_oneshot_pulse, getHandle(), ch, value) \
    return Napi::Boolean::New(env, getLastError() == SUCCESS); \
}

Napi::Object InitPulseGenerators(Napi::Env env, Napi::Object exports) {
    NAPI_GET_SET_FUNCTION_EXPORT(PX_on);
    NAPI_GET_SET_FUNCTION_EXPORT(PX_duty_percentage);
    NAPI_GET_SET_FUNCTION_EXPORT(PX_frequency_in_hz);

    NAPI_GET_SET_FUNCTION_EXPORT(PX_period_in_ms);
    NAPI_GET_SET_FUNCTION_EXPORT(PX_period_in_us);
    NAPI_GET_SET_FUNCTION_EXPORT(PX_pulse_width_in_ms);
    NAPI_GET_SET_FUNCTION_EXPORT(PX_pulse_width_in_us);
    NAPI_FUNCTION_EXPORT(send_PX_oneshot_pulse);
    return exports;
}

}

