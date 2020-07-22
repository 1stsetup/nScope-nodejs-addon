#include <napi.h>
#include "globalnScope.h"
#include "nScopeAPI.h"
#include "nScopeAPI-analogInputs.h"
#include "nScopeAPI-trigger.h"
#include "nScopeAPI-pulseGenerators.h"
#include "nScopeAPI-analogOutputs.h"
#include "nScopeAPI-requests.h"
#include "nScopeAPI-sampleTiming.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  nScope::nScopeAPIClass::Init(env, exports);
  nScope::InitTriggers(env, exports);
  nScope::InitPulseGenerators(env, exports);
  nScope::InitAnalogOutputs(env, exports);
  nScope::InitAnalogInputs(env, exports);
  nScope::InitSampleTiming(env, exports);
  nScope::requestClass::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)