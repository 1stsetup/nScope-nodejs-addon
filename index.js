const nScope = require('./build/Release/nscopeapi.node');
console.log('addon',nScope);

var nScopeDevice = new nScope.device();
console.log('addon',nScopeDevice);

try {

    console.log('API version:', nScopeDevice.check_API_version());
    console.log('API build:', nScopeDevice.check_API_build());
    console.log('FW version:', nScopeDevice.check_FW_version());

    var opened = nScopeDevice.open(true);
    console.log('nScopeAPI opened:',opened);
    if (!opened) {
        console.log("\tlastError:",nScope.lastErrorStr());
    }
    else {
        console.log("get_power_state:",nScopeDevice.get_power_state());
        console.log("get_power_usage:",nScopeDevice.get_power_usage(),"W");

        nScope.set_ChX_on(nScopeDevice, 1, true);

    //    nScope.set_ChX_gain(nScopeDevice, 1, 1.01);
    //    nScope.set_ChX_level(nScopeDevice, 1, 0.0);

        for(var channel=1; channel<5; channel++) {
            console.log("get_Ch"+channel+"_on",nScope.get_ChX_on(nScopeDevice, channel));
            console.log("get_Ch"+channel+"_gain",nScope.get_ChX_gain(nScopeDevice, channel));
            console.log("get_Ch"+channel+"_level",nScope.get_ChX_level(nScopeDevice, channel));
        }
        nScope.set_trigger_edge(nScopeDevice, 1);

        nScope.set_sample_rate_in_hz(nScopeDevice, 10.0);

        var request = new nScope.request(nScopeDevice, 10, false);
        console.log("request:",request);
        request.wait_for_request_finish();
        while (request.has_data()) {
            console.log("Request has data");
            var data = request.read_data(1);
            console.log("Data:",data);
        }
        
    }
}
catch(err) {
    console.error("An error occured:"+err);
    console.log("\tlastError:",nScopeDevice.lastError());
    console.log("\tlastErrorStr:",nScopeDevice.lastErrorStr());
}


