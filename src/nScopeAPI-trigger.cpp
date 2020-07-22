#include "nScopeAPI-trigger.h"

namespace nScope {

CALL_NSCOPE_GET_SET_BY_HANDLE(trigger_delay_ms, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE(trigger_delay_us, double, Number)
CALL_NSCOPE_GET_BY_HANDLE(trigger_edge, TriggerEdge, Number)

Napi::Boolean set_trigger_edge(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2) {
        std::string s = "Need 2 arguments 'set_trigger_edge'";
        Napi::Error::New(env, s).ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
    else {
        Napi::Object object_parent = info[0].As<Napi::Object>();
        nScopeAPIClass* nScopeAPI = Napi::ObjectWrap<nScopeAPIClass>::Unwrap(object_parent);
        Napi::Number value = info[1].As<Napi::Number>();
        if (value.Int32Value() == 1) {
            CALL_NSCOPE_FUNCTION(nScope_set_trigger_edge, nScopeAPI->getHandle(), FALLING_EDGE)
        }
        else {
            CALL_NSCOPE_FUNCTION(nScope_set_trigger_edge, nScopeAPI->getHandle(), RISING_EDGE)
        }
        return Napi::Boolean::New(env, nScopeAPI->getLastError() == SUCCESS);
    }
}

CALL_NSCOPE_GET_SET_BY_HANDLE(trigger_level, double, Number)
CALL_NSCOPE_GET_SET_BY_HANDLE(trigger_on, bool, Boolean)
CALL_NSCOPE_GET_SET_BY_HANDLE(trigger_source, int, Number)

Napi::Object InitTriggers(Napi::Env env, Napi::Object exports) {
    NAPI_GET_SET_FUNCTION_EXPORT(trigger_delay_ms);
    NAPI_GET_SET_FUNCTION_EXPORT(trigger_delay_us);
    NAPI_GET_SET_FUNCTION_EXPORT(trigger_edge);
    NAPI_GET_SET_FUNCTION_EXPORT(trigger_level);
    NAPI_GET_SET_FUNCTION_EXPORT(trigger_on);
    NAPI_GET_SET_FUNCTION_EXPORT(trigger_source);
    return exports;
}

}