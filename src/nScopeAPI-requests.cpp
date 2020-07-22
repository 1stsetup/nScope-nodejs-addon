#include "nScopeAPI-requests.h"

namespace nScope {

Napi::FunctionReference requestClass::constructor;

requestClass::requestClass(const Napi::CallbackInfo& info) : Napi::ObjectWrap<requestClass>(info)  {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 3) {
        Napi::TypeError::New(env, "We expected 3 arguments nScopeAPI (Object), numSamples (Number) , antiAliased (Boolean)").ThrowAsJavaScriptException();
        return;
    }
    else {
        if (!info[0].IsObject()) {
            Napi::TypeError::New(env, "Argument 1 needs to be an nScopeAPI object").ThrowAsJavaScriptException();
            return;
        }
        else {
            if (!info[1].IsNumber()) {
                Napi::TypeError::New(env, "Argument 2 needs to be a number").ThrowAsJavaScriptException();
                return;
            }
            else {
                if (!info[2].IsBoolean()) {
                    Napi::TypeError::New(env, "Argument 3 needs to be a boolean").ThrowAsJavaScriptException();
                    return;
                }
            }
        }
    }

    Napi::Object object_parent = info[0].As<Napi::Object>();
    this->_nScopeAPI = Napi::ObjectWrap<nScopeAPIClass>::Unwrap(object_parent);
    Napi::Number numSamples = info[1].As<Napi::Number>();
    Napi::Boolean antiAliased = info[2].As<Napi::Boolean>();
    CALL_NSCOPE_FUNCTION(nScope_request_data, this->_nScopeAPI->getHandle(), &(this->_request), numSamples, antiAliased)
}

Napi::Value requestClass::release_request(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    CALL_NSCOPE_FUNCTION(nScope_release_request, this->_nScopeAPI->getHandle(), &(this->_request))
    return Napi::Boolean::New(env, this->_nScopeAPI->getLastError() == SUCCESS);
}

Napi::Value requestClass::stop_request(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    CALL_NSCOPE_FUNCTION(nScope_stop_request, this->_nScopeAPI->getHandle(), this->_request)
    return Napi::Boolean::New(env, this->_nScopeAPI->getLastError() == SUCCESS);
}

Napi::Value requestClass::wait_for_request_finish(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    CALL_NSCOPE_FUNCTION(nScope_wait_for_request_finish, this->_nScopeAPI->getHandle(), this->_request)
    return Napi::Boolean::New(env, this->_nScopeAPI->getLastError() == SUCCESS);
}

Napi::Value requestClass::read_data(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    double returnValue = 0.0;

    if (info.Length() < 1 ) {
        Napi::TypeError::New(env, "Expected 1 arguments").ThrowAsJavaScriptException();
    }
    else {
        if (!info[0].IsNumber()) {
            Napi::TypeError::New(env, "Argument 1 needs to be a number").ThrowAsJavaScriptException();
        }
        else {
            Napi::Number channel = info[0].As<Napi::Number>();
            CALL_NSCOPE_FUNCTION(nScope_read_data, this->_nScopeAPI->getHandle(), this->_request, channel, &returnValue)
        }
    }

    return Napi::Number::New(info.Env(), returnValue);
}

Napi::Value requestClass::has_data(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    bool returnValue;
    CALL_NSCOPE_FUNCTION(nScope_request_has_data, this->_nScopeAPI->getHandle(), this->_request, &returnValue)
    return Napi::Boolean::New(env, returnValue);
}

Napi::Value requestClass::xfer_has_completed(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    bool returnValue;
    CALL_NSCOPE_FUNCTION(nScope_request_xfer_has_completed, this->_nScopeAPI->getHandle(), this->_request, &returnValue)
    return Napi::Boolean::New(env, returnValue);
}

Napi::Object requestClass::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "requestClass", {
        InstanceMethod("release_request", &requestClass::release_request),
        InstanceMethod("stop_request", &requestClass::stop_request),
        InstanceMethod("wait_for_request_finish", &requestClass::wait_for_request_finish),
        InstanceMethod("read_data", &requestClass::read_data),
        InstanceMethod("has_data", &requestClass::has_data),
        InstanceMethod("xfer_has_completed", &requestClass::xfer_has_completed),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("requestClass", func);
    return exports;
}

}
