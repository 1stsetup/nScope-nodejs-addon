#include "globalnScope.h"

namespace nScope {

    ScopeHandle handle = NULL;
    ErrorType _lastError = SUCCESS;

ErrorType getLastError() {
    return _lastError;
}

void setLastError(ErrorType value) {
    _lastError = value;
}

ScopeHandle getHandle() {
    return handle;
}

void setHandle(ScopeHandle newHandle) {
    handle = newHandle;
}

Napi::Number lastError(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    return Napi::Number::New(env, _lastError);
}

Napi::String lastErrorStr(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    switch(_lastError) {
        case SUCCESS: return Napi::String::New(env, (std::string)"No error was encountered");
        case UNKNOWN_ERROR: return Napi::String::New(env, (std::string)"An unknown error occurred");
        case NSCOPE_NOT_OPEN: return Napi::String::New(env, (std::string)"nScope is not open, or has been disconnected unexpectedly");
        case NSCOPE_CHANNEL_OFF: return Napi::String::New(env, (std::string)"the desired channel is currently off");
        case NSCOPE_POWER_OFF: return Napi::String::New(env, (std::string)"nScope power is off");
        case NO_DATA_AVAILABLE: return Napi::String::New(env, (std::string)"There is no data available");
        case INVALID_TRIGGER: return Napi::String::New(env, (std::string)"The trigger settings are invalid");
        case INVALID_REQUEST: return Napi::String::New(env, (std::string)"The request is invalid");
        case COMM_ERROR: return Napi::String::New(env, (std::string)"A communication error has occurred");
        case INTERRUPT_STOPPED: return Napi::String::New(env, (std::string)"TODO: no clue");
        case FW_API_INCOMPATIBLE: return Napi::String::New(env, (std::string)"Firmware and API are incompatible");
        case VALUE_ERROR_TOO_SMALL: return Napi::String::New(env, (std::string)"Value error: a parameter is too small");
        case VALUE_ERROR_TOO_LARGE: return Napi::String::New(env, (std::string)"Value error: a parameter is too large");
        case VALUE_ERROR_OUT_OF_RANGE: return Napi::String::New(env, (std::string)"Value error: a parameter is out of range");
        case VALUE_WARNING_TOO_SMALL: return Napi::String::New(env, (std::string)"Value warning: a parameter is very small");
        case VALUE_WARNING_TOO_LARGE: return Napi::String::New(env, (std::string)"Value warning: a parameter is very large");
    }
    return Napi::String::New(env, (std::string)"An unknown error code");
}

Napi::Object InitGlobal(Napi::Env env, Napi::Object exports) {
    NAPI_FUNCTION_EXPORT(lastError);
    NAPI_FUNCTION_EXPORT(lastErrorStr);
    return exports;
}

}