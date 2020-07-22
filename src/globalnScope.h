#ifndef GLOBAL_NSCOPE
#define GLOBAL_NSCOPE

#include <napi.h>
#include "../nScopeAPI/include/nScopeAPI.h"
#include <string>

namespace nScope {

ErrorType getLastError();
void setLastError(ErrorType value);
ScopeHandle getHandle();
void setHandle(ScopeHandle newHandle);

#define H_NAPI_FUNCTION(type,name) Napi::type name(const Napi::CallbackInfo& info);

#define H_NAPI_GET_SET_FUNCTION(type,name) H_NAPI_FUNCTION(type,get_ ## name) \
    H_NAPI_FUNCTION(Boolean,set_ ## name)

H_NAPI_FUNCTION(Number, lastError)
H_NAPI_FUNCTION(String, lastErrorStr)

Napi::Object InitGlobal(Napi::Env env, Napi::Object exports);

#define NAPI_FUNCTION_EXPORT(name) exports.Set(#name, Napi::Function::New(env, name));

#define NAPI_GET_SET_FUNCTION_EXPORT(name) NAPI_FUNCTION_EXPORT(get_ ## name) \
    NAPI_FUNCTION_EXPORT(set_ ## name)

#define CALL_NSCOPE_FUNCTION(name, ...)     ErrorType error = name(__VA_ARGS__); \
    setLastError(SUCCESS); \
    if (error != SUCCESS) { \
        setLastError(error); \
        std::string s = "Error calling nScopeAPI function '"; \
        s.append(#name); \
        s.append("'"); \
        Napi::Error::New(env, s).ThrowAsJavaScriptException(); \
    }

#define CALL_NSCOPE_GET_BY_HANDLE(name, type, returnType)  Napi::returnType get_ ## name(const Napi::CallbackInfo& info) { \
    Napi::Env env = info.Env(); \
    type returnValue; \
    CALL_NSCOPE_FUNCTION(nScope_get_ ## name, getHandle(), &returnValue) \
    return Napi::returnType::New(env, returnValue); \
}

#define CALL_NSCOPE_SET_BY_HANDLE(name, type)  Napi::Boolean set_ ## name(const Napi::CallbackInfo& info) { \
    Napi::Env env = info.Env(); \
    Napi::type value = info[0].As<Napi::type>(); \
    CALL_NSCOPE_FUNCTION(nScope_set_ ## name, getHandle(), value) \
    return Napi::Boolean::New(env, getLastError() == SUCCESS); \
}

#define CALL_NSCOPE_GET_SET_BY_HANDLE(name, type, returnType) CALL_NSCOPE_GET_BY_HANDLE(name, type, returnType) \
    CALL_NSCOPE_SET_BY_HANDLE(name, returnType)

#define CALL_NSCOPE_GET_BY_HANDLE_CH(name, type, returnType)  Napi::returnType get_ ## name(const Napi::CallbackInfo& info) { \
    Napi::Env env = info.Env(); \
    Napi::Number ch = info[0].As<Napi::Number>(); \
    type returnValue; \
    CALL_NSCOPE_FUNCTION(nScope_get_ ## name, getHandle(), ch, &returnValue) \
    return Napi::returnType::New(env, returnValue); \
}

#define CALL_NSCOPE_SET_BY_HANDLE_CH(name, type)  Napi::Boolean set_ ## name(const Napi::CallbackInfo& info) { \
    Napi::Env env = info.Env(); \
    if (info.Length() < 2) { \
        std::string s = "Need 2 arguments '"; \
        s.append(#name); \
        s.append("'"); \
        Napi::Error::New(env, s).ThrowAsJavaScriptException(); \
        return Napi::Boolean::New(env, false); \
    } \
    else { \
        Napi::Number ch = info[0].As<Napi::Number>(); \
        Napi::type value = info[1].As<Napi::type>(); \
        CALL_NSCOPE_FUNCTION(nScope_set_ ## name, getHandle(), ch, value) \
        return Napi::Boolean::New(env, getLastError() == SUCCESS); \
    } \
}

#define CALL_NSCOPE_GET_SET_BY_HANDLE_CH(name, type, returnType) CALL_NSCOPE_GET_BY_HANDLE_CH(name, type, returnType) \
    CALL_NSCOPE_SET_BY_HANDLE_CH(name, returnType)

}

#endif