#include "nScopeAPI.h"

namespace nScope {

Napi::Boolean open(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsBoolean()) {
        Napi::TypeError::New(env, "Boolean expected").ThrowAsJavaScriptException();
    } 

    Napi::Boolean poweron = info[0].As<Napi::Boolean>();
    ScopeHandle tmpHandle;
    CALL_NSCOPE_FUNCTION(nScope_open, poweron, &tmpHandle)
    setHandle(tmpHandle);
    return Napi::Boolean::New(env, getLastError() == SUCCESS);
}

Napi::Boolean close(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    ScopeHandle tmpHandle = getHandle();
    CALL_NSCOPE_FUNCTION(nScope_close, &tmpHandle)
    setHandle(tmpHandle);
    return Napi::Boolean::New(env, getLastError() == SUCCESS);
}

Napi::Number get_power_state(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    PowerState currentState;
    CALL_NSCOPE_FUNCTION(nScope_get_power_state, getHandle(), &currentState)
    return Napi::Number::New(env, currentState);
}

CALL_NSCOPE_GET_BY_HANDLE(power_usage, double, Number)

Napi::Number check_API_version(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    double version;
    CALL_NSCOPE_FUNCTION(nScope_check_API_version, &version);
    return Napi::Number::New(env, version);
}

Napi::Number check_API_build(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    int buildNo;
    CALL_NSCOPE_FUNCTION(nScope_check_API_build, &buildNo);
    return Napi::Number::New(env, buildNo);
}

Napi::Number check_FW_version(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    double version;
    CALL_NSCOPE_FUNCTION(nScope_check_FW_version, &version);
   return Napi::Number::New(env, version);
}

Napi::Boolean find_firmware_loader(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    CALL_NSCOPE_FUNCTION(nScope_find_firmware_loader)
    return Napi::Boolean::New(env, getLastError() == SUCCESS);
}

Napi::Boolean write_to_loader(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    CALL_NSCOPE_FUNCTION(nScope_write_to_loader)
    return Napi::Boolean::New(env, getLastError() == SUCCESS);
}

Napi::Boolean load_firmware(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    CALL_NSCOPE_FUNCTION(nScope_load_firmware)
    return Napi::Boolean::New(env, getLastError() == SUCCESS);
}

Napi::Object InitAPI(Napi::Env env, Napi::Object exports) {
    NAPI_FUNCTION_EXPORT(check_API_version);
    NAPI_FUNCTION_EXPORT(check_API_build);
    NAPI_FUNCTION_EXPORT(check_FW_version);
    NAPI_FUNCTION_EXPORT(open);
    NAPI_FUNCTION_EXPORT(close);
    NAPI_FUNCTION_EXPORT(get_power_state);
    NAPI_FUNCTION_EXPORT(get_power_usage);
    NAPI_FUNCTION_EXPORT(load_firmware);
    NAPI_FUNCTION_EXPORT(write_to_loader);
    NAPI_FUNCTION_EXPORT(find_firmware_loader);
    return exports;
}

}

