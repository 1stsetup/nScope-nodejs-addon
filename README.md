# nScope-nodejs-addon
Addon for NodeJS for the nScope library

For more information about nScope see https://www.nscope.org/

This repository will create a NodeJS addon based on the nScope library (https://github.com/nLabs-nScope/nScopeAPI.git)

Installation
============
```text
npm install nscope
````

Requirements
============

* [node.js](http://nodejs.org) -- Tested with v12.16.3
* [nScope library](https://github.com/nLabs-nScope/nScopeAPI/tree/develop/lib) -- Tested with v0.8
* Compile tools like make and gcc.

Example
=======

```javascript
const nScope = require('nscope');
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

API Documentation
=================

nScope Module Functions
-----------------------

* < _DeviceObject_ >**device**() - Should be called to create a device object.

* < _RequestObject_ >**request**(< _DeviceObject_ >device, < _Number_ >numSamples, < _Boolean_ >antiAliased) - Should be called to create a request object.
  * < _DeviceObject_ >**device** - a device object required by calling device()
  * < _Number_ >**numSamples** - number of data samples (per channel) to request
  * < _Boolean_ >**antiAliased** - true: turn on anti-aliasing, false: turn it off


< _DeviceObject_ > Functions
-----------------------------------

* < _Boolean_ >**open**(< _Boolean_ >powerOn) - Open a connected nScope device and initialize it.
  * < _Boolean_ >**powerOn** - true turns nScope on when first opened, false leaves nScope in its current state.

* < _Boolean_ >**close**() - Close and clean a connected nScope device. 

* < _Number_ >**check_API_version**() - check the version of this API.

* < _Number_ >**check_API_build**() - check the build number of this API.

* < _Number_ >**check_FW_version**() - check the version of the connected firmware. Will only work when nScope is connected to computer.

* < _Number_ >**get_power_state**() - Read the PowerState of the nScope.

* < _Number_ >**get_power_usage**() - Read how much power is being used by nScope in watts.

* < _Number_ >**find_firmware_loader**() - find the firmware loader.

* < _Number_ >**load_firmware**() - load the nScope with current firmware.

* < _Number_ >**write_to_loader**() - write the firmware to the loader.


