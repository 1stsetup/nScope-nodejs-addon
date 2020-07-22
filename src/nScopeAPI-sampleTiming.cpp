#include "nScopeAPI-sampleTiming.h"

namespace nScope {

CALL_NSCOPE_GET_SET_BY_HANDLE(sample_rate_in_hz, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE(time_between_samples_in_minutes, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE(time_between_samples_in_ms, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE(time_between_samples_in_seconds, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE(time_between_samples_in_us, double, Number)

Napi::Object InitSampleTiming(Napi::Env env, Napi::Object exports) {
    NAPI_GET_SET_FUNCTION_EXPORT(sample_rate_in_hz)
    NAPI_GET_SET_FUNCTION_EXPORT(time_between_samples_in_minutes)
    NAPI_GET_SET_FUNCTION_EXPORT(time_between_samples_in_ms)
    NAPI_GET_SET_FUNCTION_EXPORT(time_between_samples_in_seconds)
    NAPI_GET_SET_FUNCTION_EXPORT(time_between_samples_in_us)

    return exports;
}

}

