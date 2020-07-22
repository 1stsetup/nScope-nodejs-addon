const nScope = require('./build/Release/nscope.node');
console.log('addon',nScope);

function getValues(channel) {
    console.log("get_Ch"+channel+"_gain",nScope.get_ChX_gain(channel));
    console.log("get_Ch"+channel+"_level",nScope.get_ChX_level(channel));
    setTimeout(getValues,200, channel);
}

try {

console.log('API version:', nScope.check_API_version());
console.log('API build:', nScope.check_API_build());
console.log('FW version:', nScope.check_FW_version());

var opened = nScope.open(true);
console.log('nScope opened:',opened);
if (!opened) {
    console.log("\tlastError:",nScope.lastErrorStr());
}
else {
    console.log("get_power_state:",nScope.get_power_state());
    console.log("get_power_usage:",nScope.get_power_usage(),"W");

    nScope.set_ChX_on(1, true);
//    nScope.set_ChX_gain(1, 1.01);
//    nScope.set_ChX_level(1, 0.0);

    for(var channel=1; channel<5; channel++) {
        console.log("get_Ch"+channel+"_on",nScope.get_ChX_on(channel));
        console.log("get_Ch"+channel+"_gain",nScope.get_ChX_gain(channel));
        console.log("get_Ch"+channel+"_level",nScope.get_ChX_level(channel));
    }
    nScope.set_trigger_edge(1);

    nScope.set_sample_rate_in_hz(10.0);

    var request = new nScope.requestClass(10, false);
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
    console.log("\tlastError:",nScope.lastErrorStr());
}
