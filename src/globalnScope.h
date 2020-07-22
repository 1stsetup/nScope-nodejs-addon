#ifndef GLOBAL_NSCOPE
#define GLOBAL_NSCOPE

#include <napi.h>
#include "../nScopeAPI/include/nScopeAPI.h"
#include <string>
#include "nScopeAPI.h"

namespace nScope {

Napi::String lastErrorStr(Napi::Env env, ErrorType _lastError);

#define H_NAPI_FUNCTION(type,name) Napi::type name(const Napi::CallbackInfo& info);

#define H_NAPI_GET_SET_FUNCTION(type,name) H_NAPI_FUNCTION(type,get_ ## name) \
    H_NAPI_FUNCTION(Boolean,set_ ## name)


Napi::Object InitGlobal(Napi::Env env, Napi::Object exports);

#define NAPI_FUNCTION_EXPORT(name) exports.Set(#name, Napi::Function::New(env, name));

#define NAPI_GET_SET_FUNCTION_EXPORT(name) NAPI_FUNCTION_EXPORT(get_ ## name) \
    NAPI_FUNCTION_EXPORT(set_ ## name)

#define CALL_NSCOPE_FUNCTION(name, ...)     ErrorType error = name(__VA_ARGS__); \
    if (error != SUCCESS) { \
        Napi::Error errObj = Napi::Error::New(env); \
        errObj.Set("errorCode", Napi::Number::New(env, error)); \
        errObj.Set("msg", lastErrorStr(env, error)); \
        errObj.ThrowAsJavaScriptException(); \
    }

#define CALL_NSCOPE_GET_BY_HANDLE(name, type, returnType)  Napi::returnType get_ ## name(const Napi::CallbackInfo& info) { \
    Napi::Env env = info.Env(); \
    if (info.Length() < 1) { \
        std::string s = "Need 1 argument '"; \
        s.append(#name); \
        s.append("'"); \
        Napi::Error::New(env, s).ThrowAsJavaScriptException(); \
        return Napi::returnType::New(env, 0); \
    } \
    Napi::Object object_parent = info[0].As<Napi::Object>(); \
    nScopeAPIClass* nScopeAPI = Napi::ObjectWrap<nScopeAPIClass>::Unwrap(object_parent); \
    type returnValue; \
    CALL_NSCOPE_FUNCTION(nScope_get_ ## name, nScopeAPI->getHandle(), &returnValue) \
    return Napi::returnType::New(env, returnValue); \
}

#define CALL_NSCOPE_SET_BY_HANDLE(name, type)  Napi::Boolean set_ ## name(const Napi::CallbackInfo& info) { \
    Napi::Env env = info.Env(); \
    if (info.Length() < 2) { \
        std::string s = "Need 2 arguments '"; \
        s.append(#name); \
        s.append("'"); \
        Napi::Error::New(env, s).ThrowAsJavaScriptException(); \
        return Napi::Boolean::New(env, false); \
    } \
    Napi::Object object_parent = info[0].As<Napi::Object>(); \
    nScopeAPIClass* nScopeAPI = Napi::ObjectWrap<nScopeAPIClass>::Unwrap(object_parent); \
    Napi::type value = info[1].As<Napi::type>(); \
    CALL_NSCOPE_FUNCTION(nScope_set_ ## name, nScopeAPI->getHandle(), value) \
    return Napi::Boolean::New(env, nScopeAPI->getLastError() == SUCCESS); \
}

#define CALL_NSCOPE_GET_SET_BY_HANDLE(name, type, returnType) CALL_NSCOPE_GET_BY_HANDLE(name, type, returnType) \
    CALL_NSCOPE_SET_BY_HANDLE(name, returnType)

#define CALL_NSCOPE_GET_BY_HANDLE_CH(name, type, returnType)  Napi::returnType get_ ## name(const Napi::CallbackInfo& info) { \
    Napi::Env env = info.Env(); \
    if (info.Length() < 2) { \
        std::string s = "Need 2 arguments '"; \
        s.append(#name); \
        s.append("'"); \
        Napi::Error::New(env, s).ThrowAsJavaScriptException(); \
        return Napi::returnType::New(env, 0); \
    } \
    Napi::Object object_parent = info[0].As<Napi::Object>(); \
    nScopeAPIClass* nScopeAPI = Napi::ObjectWrap<nScopeAPIClass>::Unwrap(object_parent); \
    Napi::Number ch = info[1].As<Napi::Number>(); \
    type returnValue; \
    CALL_NSCOPE_FUNCTION(nScope_get_ ## name, nScopeAPI->getHandle(), ch, &returnValue) \
    return Napi::returnType::New(env, returnValue); \
}

#define CALL_NSCOPE_SET_BY_HANDLE_CH(name, type)  Napi::Boolean set_ ## name(const Napi::CallbackInfo& info) { \
    Napi::Env env = info.Env(); \
    if (info.Length() < 3) { \
        std::string s = "Need 3 arguments '"; \
        s.append(#name); \
        s.append("'"); \
        Napi::Error::New(env, s).ThrowAsJavaScriptException(); \
        return Napi::Boolean::New(env, false); \
    } \
    else { \
        Napi::Object object_parent = info[0].As<Napi::Object>(); \
        nScopeAPIClass* nScopeAPI = Napi::ObjectWrap<nScopeAPIClass>::Unwrap(object_parent); \
        Napi::Number ch = info[1].As<Napi::Number>(); \
        Napi::type value = info[2].As<Napi::type>(); \
        CALL_NSCOPE_FUNCTION(nScope_set_ ## name, nScopeAPI->getHandle(), ch, value) \
        return Napi::Boolean::New(env, nScopeAPI->getLastError() == SUCCESS); \
    } \
}

#define CALL_NSCOPE_GET_SET_BY_HANDLE_CH(name, type, returnType) CALL_NSCOPE_GET_BY_HANDLE_CH(name, type, returnType) \
    CALL_NSCOPE_SET_BY_HANDLE_CH(name, returnType)

}

#endif