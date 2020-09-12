#include "WasmResource.hpp"

WasmResource::WasmResource(alt::IResource* resource, wasm_instance_t *instance, wasm_module_t *module)
    : resource(resource), instance(instance), module(module)
{
}

bool WasmResource::Start()
{
    util::logi("[WASM] Starting resource");

    std::string func_name = "run";
    int run_index = util::find_export_index_by_name(this->module, func_name);

    wasm_extern_vec_t exports;
    wasm_instance_exports(this->instance, &exports);
    if (exports.size == 0)
    {
        util::loge("Error accessing exports");
        return false;
    }

    wasm_func_t *run_func = wasm_extern_as_func(exports.data[run_index]);
    if (run_func == nullptr)
    {
        util::loge("Error accessing export: " + func_name);
        return false;
    }

    wasmtime_error_t *error = nullptr;
    wasm_trap_t *trap = nullptr;
    error = wasmtime_func_call(run_func, nullptr, 0, nullptr, 0, &trap);
    if (error != nullptr || trap != nullptr)
    {
        util::logwe("Failed to call function: " + func_name, error, trap);
        return false;
    }

    return true;
}

bool WasmResource::Stop()
{
    util::logi("[WASM] Stopping resource");
    return true;
}

bool WasmResource::OnEvent(const alt::CEvent *ev)
{
    return true;
}

void WasmResource::OnTick()
{
}

void WasmResource::OnCreateBaseObject(alt::Ref<alt::IBaseObject> object)
{
}

void WasmResource::OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object)
{
}
