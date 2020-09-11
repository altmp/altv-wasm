#pragma once

#include "structs.hpp"
#include "util.hpp"

namespace resource {
    CAPI_EXPORT bool start(alt_IResource *resource) {
        WasmResource *wasmres = WasmResource::from(alt_IResource_GetImpl(resource));
//        util::logi("[WASM] Starting resource: " + *wasmres->name);
        util::logi("[WASM] Starting resource");

        std::string func_name = "run";
        int run_index = util::find_export_index_by_name(wasmres->module, func_name);

        wasm_extern_vec_t exports;
        wasm_instance_exports(wasmres->instance, &exports);
        if (exports.size == 0) {
            util::loge("Error accessing exports");
            return false;
        }

        wasm_func_t* run_func = wasm_extern_as_func(exports.data[run_index]);
        if (run_func == nullptr) {
            util::loge("Error accessing export: " + func_name);
            return false;
        }

        wasmtime_error_t *error = nullptr;
        wasm_trap_t *trap = nullptr;

        error = wasmtime_func_call(run_func, nullptr, 0, nullptr, 0, &trap);
        if (error != nullptr || trap != nullptr) {
            util::logwe("Failed to call function: " + func_name, error, trap);
            return false;
        }

        return true;
    }

    CAPI_EXPORT bool stop(alt_IResource *resource) {
        WasmResource *wasmres = WasmResource::from(alt_IResource_GetImpl(resource));
//        util::logi("[WASM] Stopping resource: " + *wasmres->name);
        util::logi("[WASM] Stopping resource");
        return true;
    }

    CAPI_EXPORT bool event(alt_IResource *resource, alt_CEvent *event) {
        return true;
    }

    CAPI_EXPORT void resource_tick(alt_IResource *resource) {}
    CAPI_EXPORT void create_object(alt_IResource *resource, alt_RefBase_RefStore_IBaseObject *object) {}
    CAPI_EXPORT void destroy_object(alt_IResource *resource, alt_RefBase_RefStore_IBaseObject *object) {}
}