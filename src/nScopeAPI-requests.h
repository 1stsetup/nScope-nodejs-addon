#ifndef REQUEST_CLASS
#define REQUEST_CLASS

#include "globalnScope.h"

namespace nScope {


class requestClass : public Napi::ObjectWrap<requestClass> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  requestClass(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;
  Napi::Value release_request(const Napi::CallbackInfo& info);
  Napi::Value stop_request(const Napi::CallbackInfo& info);
  Napi::Value wait_for_request_finish(const Napi::CallbackInfo& info);
  Napi::Value read_data(const Napi::CallbackInfo& info);
  Napi::Value has_data(const Napi::CallbackInfo& info);
  Napi::Value xfer_has_completed(const Napi::CallbackInfo& info);
  Request _request;
  nScopeAPIClass* _nScopeAPI;
};

}
#endif