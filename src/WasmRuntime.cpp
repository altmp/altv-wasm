#include <wasmtime.h>
#include "WasmRuntime.hpp"
#include "WasmResource.hpp"
#include "WasmExports.hpp"
#include "Utilities.hpp"
#include "WasmImport.hpp"

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

    this->store = wasm_store_new(this->engine);
    if (this->store == nullptr)
    {
        Utilities::LogError("[WASM] Failed to instantiate the wasm store");
        return false;
    }

    this->linker = wasmtime_linker_new(this->store);
    if (this->linker == nullptr)
    {
        Utilities::LogError("[WASM] Failed to instantiate the wasmtime linker");
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

alt::IResource::Impl *WasmRuntime::CreateImpl(alt::IResource* resource)
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

    auto readSize = pkg->ReadFile(file, wasm.data, size);
    pkg->CloseFile(file);

    if (readSize != size)
    {
        Utilities::LogError("[WASM] Could not read " + main + " properly");
        return nullptr;
    }

    wasmtime_error_t* error = nullptr;
    wasm_trap_t* trap = nullptr;
    auto wasmResource = new WasmResource(resource);

    std::string moduleNameS = "env";
    wasm_name_t moduleName;
    wasm_name_new_from_string(&moduleName, moduleNameS.c_str());

    auto MakeImport = [&](const std::string& name, wasm_func_callback_with_env_t func, const std::initializer_list<wasm_valkind_enum>& params, const std::initializer_list<wasm_valkind_enum>& results) {
        return WasmImport(this->store, moduleNameS, name, wasmResource, func, params, results);
    };

    std::vector<WasmImport> imports = {
        MakeImport("alt_ICore_Instance", WasmExports::ICore_Instance, {}, { WASM_I32 }),
        MakeImport("alt_ICore_LogInfo", WasmExports::ICore_LogInfo, { WASM_I32, WASM_I32 }, {}),
        MakeImport("alt_CEvent_GetType", WasmExports::CEvent_GetType, { WASM_I32 }, { WASM_I32 }),
    };

    for (auto& import : imports)
    {
        wasm_name_t moduleName;
        wasm_name_new_from_string(&moduleName, import.module.c_str());

        wasm_name_t importName;
        wasm_name_new_from_string(&importName, import.name.c_str());

        error = wasmtime_linker_define(this->linker, &moduleName, &importName, wasm_func_as_extern(import.function));
        if (error != nullptr)
        {
            Utilities::LogWasmError("[WASM] Failed to define import: " + import.module + "::" + import.name, error, nullptr);
        }
        else
        {
            Utilities::LogInfo("[WASM] Defined import: " + import.module + "::" + import.name);
        }

        wasm_name_delete(&moduleName);
        wasm_name_delete(&importName);
    }

    wasm_module_t* module = nullptr;
    error = wasmtime_module_new(this->engine, &wasm, &module);
    if (error != nullptr)
    {
        Utilities::LogWasmError("[WASM] Failed to compile module", error, nullptr);
        return nullptr;
    }

    wasm_instance_t* instance = nullptr;
    error = wasmtime_linker_module(this->linker, &moduleName, module);
//    error = wasmtime_linker_instantiate(this->linker, module, &instance, &trap);
    if (error != nullptr)
    {
        Utilities::LogWasmError("[WASM] Failed to instantiate module", error, nullptr);
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

wasm_func_t* WasmRuntime::CreateImportFunction(const std::string& name, wasm_func_callback_with_env_t func, void* env, const std::initializer_list<wasm_valkind_enum>& params, const std::initializer_list<wasm_valkind_enum>& results)
{
    auto MakeValtypes = [](const std::initializer_list<wasm_valkind_enum>& _types){
        wasm_valtype_vec_t types;
        wasm_valtype_vec_new_uninitialized(&types, _types.size());
        for (auto p : _types)
        {
            static auto i = 0;
            switch (p)
            {
            case WASM_I32:{
                types.data[i] = wasm_valtype_new_i32();
                break;
            }
            case WASM_I64:{
                types.data[i] = wasm_valtype_new_i64();
                break;
            }
            case WASM_F32:{
                types.data[i] = wasm_valtype_new_f32();
                break;
            }
            case WASM_F64:{
                types.data[i] = wasm_valtype_new_f64();
                break;
            }
            
            default:
            {
                // error
                break;
            }
            }

            i++;
        }
        return types;
    };
    auto ClearValtypes = [](wasm_valtype_vec_t& types){
        for (size_t i = 0; i < types.size; i++)
        {
            wasm_valtype_delete(types.data[i]);
        }
    };
    
    auto wparams = MakeValtypes(params);
    auto wresults = MakeValtypes(results);

    wasm_functype_t* type = wasm_functype_new(&wparams, &wresults);
    wasm_func_t* function = wasm_func_new_with_env(this->store, type, func, env, nullptr);
    
    wasm_functype_delete(type);
    ClearValtypes(wparams);
    ClearValtypes(wresults);

    

    return function;
}
