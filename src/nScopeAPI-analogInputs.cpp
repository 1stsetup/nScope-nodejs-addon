#include "nScopeAPI-analogInputs.h"

namespace nScope {

CALL_NSCOPE_GET_SET_BY_HANDLE_CH(ChX_on, bool, Boolean)
CALL_NSCOPE_GET_SET_BY_HANDLE_CH(ChX_gain, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE_CH(ChX_level, double, Number)

Napi::Object InitAnalogInputs(Napi::Env env, Napi::Object exports) {
    NAPI_GET_SET_FUNCTION_EXPORT(ChX_on);
    NAPI_GET_SET_FUNCTION_EXPORT(ChX_gain);
    NAPI_GET_SET_FUNCTION_EXPORT(ChX_level);
    return exports;
}

}

