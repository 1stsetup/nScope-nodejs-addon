# nScope-nodejs-addon
Addon for NodeJS for the nScope library

For more information about nScope see https://www.nscope.org/

This repository will create a NodeJS addon based on the nScope library (https://github.com/nLabs-nScope/nScopeAPI.git)

Minimal example:
```javascript
const nScope = require('./build/Release/nscope.node');
var nScopeDevice = new nScope.device();
try {
    console.log('API version:', nScopeDevice.check_API_version());
    console.log('API build:', nScopeDevice.check_API_build());
    console.log('FW version:', nScopeDevice.check_FW_version());

    nScopeDevice.open(true);
    console.log("get_power_state:",nScopeDevice.get_power_state());
    console.log("get_power_usage:",nScopeDevice.get_power_usage(),"W");

    for(var channel=1; channel<5; channel++) {
        console.log("get_Ch"+channel+"_on",nScope.get_ChX_on(nScopeDevice, channel));
        console.log("get_Ch"+channel+"_gain",nScope.get_ChX_gain(nScopeDevice, channel));
        console.log("get_Ch"+channel+"_level",nScope.get_ChX_level(nScopeDevice, channel));
    }

    nScope.set_trigger_edge(nScopeDevice, 1);
    nScope.set_sample_rate_in_hz(nScopeDevice, 10.0);
    var request = new nScope.requestClass(nScopeDevice, 10, false);
    request.wait_for_request_finish();
    while (request.has_data()) {
        var data = request.read_data(1);
        console.log("Data:",data);
    }
}
catch(err) {
    console.error(err);
}
```

All functions in nScopeAPI.h are methods in a nScope.device() object.
All function in nScopeAPI-requests.h are methods in a nScope.request() object
All functions in other nScope headers are methods in addOn object.
