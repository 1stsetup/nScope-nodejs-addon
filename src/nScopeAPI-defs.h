#include "globalnScope.h"

namespace nScope {

    Napi::Object InitDefs(Napi::Env env, Napi::Object exports) {
        napi_status status;
        status = napi_set_named_property(env, exports, "FALLING_EDGE", Napi::Number::New(env, 1));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "RISING_EDGE", Napi::Number::New(env, 2));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "NOT_CONNECTED", Napi::Number::New(env, -1));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "POWER_OFF", Napi::Number::New(env, 0));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "POWER_ON", Napi::Number::New(env, 1));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "SHORTED", Napi::Number::New(env, 2));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "OVERCURRENT", Napi::Number::New(env, 3));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "SINE_WAVE", Napi::Number::New(env, 0));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "TRIANGLE_WAVE", Napi::Number::New(env, 1));
        assert(status == napi_ok);

        status = napi_set_named_property(env, exports, "SUCCESS", Napi::Number::New(env, 0));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "UNKNOWN_ERROR", Napi::Number::New(env, -100));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "NSCOPE_NOT_OPEN", Napi::Number::New(env, -101));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "NSCOPE_CHANNEL_OFF", Napi::Number::New(env, -102));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "NSCOPE_POWER_OFF", Napi::Number::New(env, -103));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "NO_DATA_AVAILABLE", Napi::Number::New(env, -104));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "INVALID_TRIGGER", Napi::Number::New(env, -105));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "INVALID_REQUEST", Napi::Number::New(env, -106));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "COMM_ERROR", Napi::Number::New(env, -107));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "INTERRUPT_STOPPED", Napi::Number::New(env, -108));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "FW_API_INCOMPATIBLE", Napi::Number::New(env, -109));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "VALUE_ERROR_TOO_SMALL", Napi::Number::New(env, -110));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "VALUE_ERROR_TOO_LARGE", Napi::Number::New(env, -111));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "VALUE_ERROR_OUT_OF_RANGE", Napi::Number::New(env, -112));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "VALUE_WARNING_TOO_SMALL", Napi::Number::New(env, -120));
        assert(status == napi_ok);
        status = napi_set_named_property(env, exports, "VALUE_WARNING_TOO_LARGE", Napi::Number::New(env, -121));
        assert(status == napi_ok);

        return exports;
    }
    
}