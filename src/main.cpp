#include "main.hpp"

CAPI_EXPORT alt_IResource_Impl *create_resource(alt_IScriptRuntime *runtime, alt_IResource *resource)
{
    alt_StringView name;
    name.data = nullptr;
    name.size = 0;

    alt_StringView main;
    name.data = nullptr;
    name.size = 0;

    alt_IResource_GetName(resource, &name);
    alt_IResource_GetMain(resource, &main);

    if (main.size < 1) {
        util::loge("[WASM] 'client-main' has to be specified in resource.cfg");
        return nullptr;
    }

    alt_IPackage *pkg = alt_IResource_GetPackage(resource);
    alt_IPackage_File *file = alt_IPackage_OpenFile(pkg, &main);

    if (file == nullptr) {
        util::loge("[WASM] Could not open file " + util::from_stringview(main));
        return nullptr;
    }

    unsigned long long int size = alt_IPackage_GetFileSize(pkg, file);
    wasm_byte_vec_t wasm;
    wasm_byte_vec_new_uninitialized(&wasm, size);

    unsigned long long int readsize = alt_IPackage_ReadFile(pkg, file, &wasm, size);
    alt_IPackage_CloseFile(pkg, file);

    if (readsize != size) {
        util::loge("[WASM] Could not read " + util::from_stringview(main) + " appropriately");
        return nullptr;
    }

    wasmtime_error_t *error = NULL;
    wasm_engine_t *engine = wasm_engine_new();
    wasm_store_t *store = wasm_store_new(engine);
    wasm_module_t *module = NULL;

    if (engine == NULL) {
        util::loge("[WASM] Failed to instantiate the wasm engine");
        return nullptr;
    }

    util::logi("[WASM] Creating a wasmtime module");
    error = wasmtime_module_new(engine, &wasm, &module);
    util::logi("[WASM] Creating a wasmtime module [2]");
    wasm_byte_vec_delete(&wasm);
    util::logw("[WASM] [1] is error a nullptr: " + util::boolean_to_string(error != NULL));

    if (error != NULL) {
        util::logwe("[WASM] Failed to compile module", error, NULL);
        return nullptr;
    }

    wasm_trap_t *trap = NULL;
    wasm_instance_t *instance = NULL;
    wasm_extern_t *imports[] = { NULL };

    util::logi("[WASM] Creating a wasmtime instance");
    error = wasmtime_instance_new(store, module, imports, 0, &instance, &trap);

    util::logw("[WASM] [2] is instance a nullptr: " + util::boolean_to_string(instance == NULL));
    if (instance == NULL) {
        util::loge("[WASM] Failed to instantiate module [Instance is null]");
        return nullptr;
    }

    util::logw("[WASM] [3] is error a nullptr: " + util::boolean_to_string(error != NULL));
    if (error != NULL) {
        util::logwe("[WASM] Failed to instantiate module", error, trap);
        return nullptr;
    }

    std::unique_ptr<WasmResource> wasmres;
    wasmres->name = util::from_stringview(main);
    wasmres->instance = instance;

    util::logi("[WASM] Creating a resource instance...");

    alt_IResource_Impl *resource_impl = alt_CAPIResource_Impl_Create(
        resource,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr
    );

    alt_CAPIResource_Impl_SetExtra(resource_impl, wasmres.release());

    return resource_impl;
}

CAPI_EXPORT void remove_resource(alt_IScriptRuntime *runtime, alt_IResource_Impl *resource_impl)
{
    util::logi("[WASM] Removed resource");
}

CAPI_EXPORT void tick(alt_IScriptRuntime *runtime)
{
//    util::logi("Resource tick");
}

CAPI_EXPORT alt_IScriptRuntime *altMain(alt_ICore* core)
{
    alt_ICore_SetInstance(core);

    util::logi("[WASM] Initializing runtime...");

    alt_IScriptRuntime *runtime = alt_CAPIScriptRuntime_Create(create_resource, remove_resource, tick);

    util::logi("[WASM] Initialized runtime");

    return runtime;
}

