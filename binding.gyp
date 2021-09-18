{
    "targets": [
    {
        "target_name": "getdpi",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "lib/src/getdpi.cpp",
        ],
        "msvs_settings": {
          "VCCLCompilerTool": {
             "ExceptionHandling": 1,
             "AdditionalOptions": []
          }
         },
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'conditions': [
            ['OS=="linux"', {
            'libraries': ['-lX11'],
            }]
        ],
        'libraries': [ ],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}