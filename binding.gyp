{
    "targets": [{
        "target_name": "nscopeapi",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "src/main.cpp",
            "src/nScopeAPI.cpp",
            "src/nScopeAPI-analogInputs.cpp",
            "src/nScopeAPI-analogOutputs.cpp",
            "src/nScopeAPI-sampleTiming.cpp",
            "src/nScopeAPI-trigger.cpp",
            "src/nScopeAPI-pulseGenerators.cpp",
            "src/nScopeAPI-requests.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "nScopeAPI/include"
        ],
        'libraries': [ "-LnScopeAPI/lib, -lnscopeapi"],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}