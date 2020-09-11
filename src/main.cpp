#include "main.hpp"

static wasm_trap_t *hello_callback(const wasm_val_t args[], wasm_val_t results[])
{
    util::logi("[WASM] hello_callback called");
    return nullptr;
}

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

    unsigned long long int readsize = alt_IPackage_ReadFile(pkg, file, wasm.data, size);
    alt_IPackage_CloseFile(pkg, file);

    if (readsize != size) {
        util::loge("[WASM] Could not read " + util::from_stringview(main) + " appropriately");
        return nullptr;
    }

    wasmtime_error_t *error = nullptr;
    wasm_engine_t *engine = wasm_engine_new();
    wasm_store_t *store = wasm_store_new(engine);
    wasm_module_t *module = nullptr;

    if (engine == nullptr) {
        util::loge("[WASM] Failed to instantiate the wasm engine");
        return nullptr;
    }

    error = wasmtime_module_new(engine, &wasm, &module);

    if (error != nullptr) {
        util::logwe("[WASM] Failed to compile module", error, nullptr);
        return nullptr;
    }

    wasm_functype_t *hello_ty = wasm_functype_new_0_0();
    wasm_func_t *hello = wasm_func_new(store, hello_ty, hello_callback);

    wasm_trap_t *trap = nullptr;
    wasm_instance_t *instance = nullptr;
    wasm_extern_t *imports[] = { wasm_func_as_extern(hello) };

    error = wasmtime_instance_new(store, module, imports, 1, &instance, &trap);

    if (error != nullptr) {
        util::logwe("[WASM] Failed to instantiate module", error, trap);
        return nullptr;
    }

    if (instance == nullptr) {
        util::loge("[WASM] Failed to instantiate module [Instance is null]");
        return nullptr;
    }

    util::logi("[WASM] Creating a resource instance for " + util::from_stringview(name) + "...");

    alt_IResource_Impl *resource_impl = alt_CAPIResource_Impl_Create(
        resource,
        resource::start,
        resource::stop,
        resource::event,
        resource::resource_tick,
        resource::create_object,
        resource::destroy_object
    );

    WasmResource *wasmres = new WasmResource(main.data, instance, module);
    alt_CAPIResource_Impl_SetExtra(resource_impl, wasmres);

    util::logi("[WASM] Created a resource instance");

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

