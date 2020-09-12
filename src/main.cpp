#include <SDK.h>
#include "WasmRuntime.hpp"
#include "wasmtime.h"
#include "util.hpp"

CAPI_EXPORT alt::IScriptRuntime* altMain(alt::ICore* core)
{
    alt::ICore::SetInstance(core);

    // util::logi("[WASM] Initializing runtime...");
    core->LogError("ok");

    auto runtime = new WasmRuntime();
    if(!runtime->Init())
        throw std::runtime_error("WasmRuntime was not successfully initialized");
        
    return runtime;
}

// hack for debug build
extern "C" void __imp_clock()
{

}
