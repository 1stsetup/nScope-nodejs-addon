#include "nScopeAPI.h"

#define CALL_NSCOPE_FUNCTION(name, ...)     ErrorType error = name(__VA_ARGS__); \
    this->_lastError = SUCCESS; \
    if (error != SUCCESS) { \
        this->_lastError = error; \
        std::string s = "Error calling nScopeAPI function '"; \
        s.append(#name); \
        s.append("'"); \
        Napi::Error errObj = Napi::Error::New(env, Napi::String::New(env, s)); \
        errObj.ThrowAsJavaScriptException(); \
    }

namespace nScope {

Napi::FunctionReference nScopeAPIClass::constructor;

nScopeAPIClass::nScopeAPIClass(const Napi::CallbackInfo& info) : Napi::ObjectWrap<nScopeAPIClass>(info)  {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    this->_handle = NULL;
    this->_opened = false;
}

ScopeHandle nScopeAPIClass::getHandle() {
    return this->_handle;
}

Napi::Value nScopeAPIClass::isOpen(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Boolean::New(env, this->_opened);
}

Napi::Value nScopeAPIClass::open(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 1 || !info[0].IsBoolean()) {
        Napi::TypeError::New(env, "Boolean expected. PowerOn (Boolean)").ThrowAsJavaScriptException();
    } 

    Napi::Boolean poweron = info[0].As<Napi::Boolean>();
    CALL_NSCOPE_FUNCTION(nScope_open, poweron, &(this->_handle))
    if (this->_lastError == SUCCESS) {
        this->_opened = true;
    }
    return Napi::Boolean::New(env, this->_lastError == SUCCESS);
}

Napi::Value nScopeAPIClass::close(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    this->_opened = false;

    CALL_NSCOPE_FUNCTION(nScope_close, &(this->_handle))
    return Napi::Boolean::New(env, this->_lastError == SUCCESS);
}

Napi::Value nScopeAPIClass::get_power_state(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    PowerState currentState;
    CALL_NSCOPE_FUNCTION(nScope_get_power_state, this->_handle, &currentState)
    return Napi::Number::New(env, currentState);
}

Napi::Value nScopeAPIClass::get_power_usage(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    double currentUsage;
    CALL_NSCOPE_FUNCTION(nScope_get_power_usage, this->_handle, &currentUsage)
    return Napi::Number::New(env, currentUsage);
}

Napi::Value nScopeAPIClass::check_API_version(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    double version;
    CALL_NSCOPE_FUNCTION(nScope_check_API_version, &version);
    return Napi::Number::New(env, version);
}

Napi::Value nScopeAPIClass::check_API_build(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int buildNo;
    CALL_NSCOPE_FUNCTION(nScope_check_API_build, &buildNo);
    return Napi::Number::New(env, buildNo);
}

Napi::Value nScopeAPIClass::check_FW_version(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    double version;
    CALL_NSCOPE_FUNCTION(nScope_check_FW_version, &version);
   return Napi::Number::New(env, version);
}

Napi::Value nScopeAPIClass::find_firmware_loader(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    CALL_NSCOPE_FUNCTION(nScope_find_firmware_loader)
    return Napi::Boolean::New(env, this->_lastError == SUCCESS);
}

Napi::Value nScopeAPIClass::write_to_loader(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    CALL_NSCOPE_FUNCTION(nScope_write_to_loader)
    return Napi::Boolean::New(env, this->_lastError == SUCCESS);
}

Napi::Value nScopeAPIClass::load_firmware(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    CALL_NSCOPE_FUNCTION(nScope_load_firmware)
    return Napi::Boolean::New(env, this->_lastError == SUCCESS);
}

ErrorType nScopeAPIClass::getLastError() {
    return this->_lastError;
}

Napi::Value nScopeAPIClass::lastError(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, this->_lastError);
}

Napi::Value nScopeAPIClass::lastErrorStr(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    switch(this->_lastError) {
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

Napi::Object nScopeAPIClass::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "device", {
        InstanceMethod("check_API_version", &nScopeAPIClass::check_API_version),
        InstanceMethod("check_API_build", &nScopeAPIClass::check_API_build),
        InstanceMethod("check_FW_version", &nScopeAPIClass::check_FW_version),
        InstanceMethod("open", &nScopeAPIClass::open),
        InstanceMethod("isOpen", &nScopeAPIClass::isOpen),
        InstanceMethod("close", &nScopeAPIClass::close),
        InstanceMethod("get_power_state", &nScopeAPIClass::get_power_state),
        InstanceMethod("get_power_usage", &nScopeAPIClass::get_power_usage),
        InstanceMethod("load_firmware", &nScopeAPIClass::load_firmware),
        InstanceMethod("write_to_loader", &nScopeAPIClass::write_to_loader),
        InstanceMethod("find_firmware_loader", &nScopeAPIClass::find_firmware_loader),
        InstanceMethod("lastError", &nScopeAPIClass::lastError),
        InstanceMethod("lastErrorStr", &nScopeAPIClass::lastErrorStr)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("device", func);
    return exports;

}

}

