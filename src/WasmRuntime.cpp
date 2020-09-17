#include <wasmtime.h>
#include "WasmRuntime.hpp"
#include "WasmResource.hpp"
#include "WasmExports.hpp"
#include "Utilities.hpp"

WasmRuntime::WasmRuntime()
{
    Instance() = this;
}

bool WasmRuntime::Init()
{
    this->engine = wasm_engine_new();
    if (this->engine == nullptr)
    {
        Utilities::LogError("[WASM] Failed to instantiate the wasm engine");
        return false;
    }

    this->store = wasm_store_new(engine);
    if (this->store == nullptr)
    {
        Utilities::LogError("[WASM] Failed to instantiate the wasm store");
        return false;
    }

    alt_ICore_SubscribeEvent(alt_ICore_Instance(), ALT_CEVENT_TYPE_ALL, [](alt_CEvent* event, void* userData) {
        auto resources = WasmRuntime::Instance()->resources;

        for (auto resource: resources)
        {
            resource->CallFunction<bool>("altEvent", {{ .kind = WASM_I32, .of = { .i32 = resource->GetPointerID(event) }}});
        }

        return true;
    }, nullptr);

    Utilities::LogInfo("[WASM] Initialized runtime");
    return true;
}

bool WasmRuntime::RequiresMain() const
{
    return true;
}

alt::IResource::Impl *WasmRuntime::CreateImpl(alt::IResource *resource)
{
//    Utilities::LogColored("~r~■~o~■~y~■~g~■~b~■~p~■~c~■");

    auto name = resource->GetName();
    auto main = resource->GetMain();

    if (main.IsEmpty())
    {
        Utilities::LogError("[WASM] 'client-main' has to be specified in resource.cfg");
        return nullptr;
    }

    auto pkg = resource->GetPackage();
    auto file = pkg->OpenFile(main);
    if (file == nullptr)
    {
        Utilities::LogError("[WASM] Could not open file " + main);
        return nullptr;
    }

    auto size = pkg->GetFileSize(file);
    wasm_byte_vec_t wasm;
    wasm_byte_vec_new_uninitialized(&wasm, size);

    auto readsize = pkg->ReadFile(file, wasm.data, size);
    pkg->CloseFile(file);

    if (readsize != size)
    {
        Utilities::LogError("[WASM] Could not read " + main + " properly");
        return nullptr;
    }

    wasmtime_error_t* error = nullptr;
    wasm_module_t* module = nullptr;
    error = wasmtime_module_new(engine, &wasm, &module);
    if (error != nullptr)
    {
        Utilities::LogWasmError("[WASM] Failed to compile module", error, nullptr);
        return nullptr;
    }

    auto wasmResource = new WasmResource(resource);

    const wasm_extern_t* imports[] = {
        wasm_func_as_extern(this->CreateExportFunction("alt_ICore_Instance", WasmExports::ICore_Instance, wasmResource, {}, {})),
        wasm_func_as_extern(this->CreateExportFunction("alt_ICore_LogInfo", WasmExports::ICore_LogInfo, wasmResource, {}, {})) ,
        wasm_func_as_extern(this->CreateExportFunction("alt_CEvent_GetType", WasmExports::CEvent_GetType, wasmResource, {}, {}))
    };

    wasm_instance_t* instance = nullptr;
    wasm_trap_t* trap = nullptr;

    error = wasmtime_instance_new(store, module, imports, sizeof(imports), &instance, &trap);
    if (error != nullptr)
    {
        Utilities::LogWasmError("[WASM] Failed to instantiate module", error, trap);
        delete wasmResource;
        return nullptr;
    }
    else if (instance == nullptr)
    {
        Utilities::LogError("[WASM] Failed to instantiate module [Instance is null]");
        delete wasmResource;
        return nullptr;
    }

    Utilities::LogInfo("[WASM] Creating a resource instance for " + name + "...");

    wasm_exporttype_vec_t module_exports;
    wasm_extern_vec_t instance_exports;
    wasm_module_exports(module, &module_exports);
    wasm_instance_exports(instance, &instance_exports);

    if (module_exports.size != instance_exports.size)
    {
        Utilities::LogError("[WASM] Module and instance exports don't match");
        delete wasmResource;
        return nullptr;
    }

    for (int i = 0; i < module_exports.size; i++)
    {
        const wasm_name_t* name = wasm_exporttype_name(module_exports.data[i]);
        const wasm_externtype_t* type = wasm_exporttype_type(module_exports.data[i]);

        std::string funcName { name->data, name->size };

        if (wasm_externtype_kind(type) == WASM_EXTERN_FUNC)
        {
            wasmResource->funcExportsMap.emplace(funcName, wasm_extern_as_func(instance_exports.data[i]));
        }
        else if (wasm_externtype_kind(type) == WASM_EXTERN_GLOBAL)
        {
            wasmResource->globalExportsMap.emplace(funcName, wasm_extern_as_global(instance_exports.data[i]));
        }
        else if (wasm_externtype_kind(type) == WASM_EXTERN_MEMORY)
        {
            wasmResource->memoryExportsMap.emplace(funcName, wasm_extern_as_memory(instance_exports.data[i]));
        }
        else if (wasm_externtype_kind(type) == WASM_EXTERN_TABLE)
        {
            wasmResource->tableExportsMap.emplace(funcName, wasm_extern_as_table(instance_exports.data[i]));
        }

        Utilities::LogInfo("Exported function: " + funcName);
    }

    wasmResource->instance = instance;
    wasmResource->module = module;

    this->resources.insert(wasmResource);

    return wasmResource;
}

void WasmRuntime::DestroyImpl(alt::IResource::Impl* impl)
{
    Utilities::LogInfo("[WASM] Removed resource");
}

void WasmRuntime::OnTick()
{
}

void WasmRuntime::OnDispose()
{
    Utilities::LogError("[WASM] Runtime disposed");
}

wasm_func_t* WasmRuntime::CreateExportFunction(const std::string& name, wasm_func_callback_with_env_t func, void* env, wasm_valtype_vec_t* params, wasm_valtype_vec_t* results)
{
    wasm_functype_t* type = wasm_functype_new(params, results);
    wasm_func_t* function = wasm_func_new_with_env(this->store, type, func, env, nullptr);
    wasm_functype_delete(type);

    auto exportType = wasm_exporttype_new(Utilities::WasmNameFromString(name), wasm_extern_type(wasm_func_as_extern(function)));

    return function;
}
