#ifndef NSCOPEAPI
#define NSCOPEAPI

#include <napi.h>
#include <node_api.h>
#include <assert.h>
#include "../nScopeAPI/include/nScopeAPI.h"

namespace nScope {

class nScopeAPIClass : public Napi::ObjectWrap<nScopeAPIClass> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        nScopeAPIClass(const Napi::CallbackInfo& info);
        ScopeHandle getHandle();
        ErrorType getLastError();
    private:
        static Napi::FunctionReference constructor;
        Napi::Value open(const Napi::CallbackInfo& info);
        Napi::Value isOpen(const Napi::CallbackInfo& info);
        Napi::Value close(const Napi::CallbackInfo& info);
        Napi::Value get_power_state(const Napi::CallbackInfo& info);
        Napi::Value get_power_usage(const Napi::CallbackInfo& info);
        Napi::Value check_API_version(const Napi::CallbackInfo& info);
        Napi::Value check_API_build(const Napi::CallbackInfo& info);
        Napi::Value check_FW_version(const Napi::CallbackInfo& info);
        Napi::Value load_firmware(const Napi::CallbackInfo& info);
        Napi::Value write_to_loader(const Napi::CallbackInfo& info);
        Napi::Value find_firmware_loader(const Napi::CallbackInfo& info);
        Napi::Value lastError(const Napi::CallbackInfo& info);
        Napi::Value lastErrorStr(const Napi::CallbackInfo& info);
        ScopeHandle _handle;
        bool _opened;
        ErrorType _lastError;
};

}

#endif