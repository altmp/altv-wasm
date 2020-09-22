#include "WasmResource.hpp"

WasmResource::WasmResource(alt::IResource* resource)
    : resource(resource)
{
}

bool WasmResource::Start()
{
    Utilities::LogInfo("[WASM] Starting resource");
    bool result = false;

    try
    {
        // Starting functions for modules
//        this->CallFunction<void>("__wasm_call_ctors");
        this->CallFunction<void>("_start");

        result = this->CallFunction<i32>("altMain", {{ .kind = WASM_I32, .of = { .i32 = this->GetPointerID(&alt::ICore::Instance()) }}});
    }
    catch (std::runtime_error& err)
    {
        Utilities::LogError(std::string(err.what()));
    }

    return result;
}

bool WasmResource::Stop()
{
    Utilities::LogInfo("[WASM] Stopping resource");
    return true;
}

bool WasmResource::OnEvent(const alt::CEvent* ev)
{
    this->CallFunction<void>("altEvent", {{ .kind = WASM_I32, .of = { .i32 = (i32)ev->GetType() }}});

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

wasm_func_t* WasmResource::FindExportedFunction(const std::string& name)
{
    auto iterator = this->funcExportsMap.find(name);

    if (iterator == this->funcExportsMap.end())
    {
        return nullptr;
    }
    else
    {
        return iterator->second;
    }
}

wasm_global_t* WasmResource::FindExportedGlobal(const std::string& name)
{
    auto iterator = this->globalExportsMap.find(name);

    if (iterator == this->globalExportsMap.end())
    {
        return nullptr;
    }
    else
    {
        return iterator->second;
    }
}

wasm_memory_t* WasmResource::FindExportedMemory(const std::string& name)
{
    auto iterator = this->memoryExportsMap.find(name);

    if (iterator == this->memoryExportsMap.end())
    {
        return nullptr;
    }
    else
    {
        return iterator->second;
    }
}

wasm_table_t* WasmResource::FindExportedTable(const std::string& name)
{
    auto iterator = this->tableExportsMap.find(name);

    if (iterator == this->tableExportsMap.end())
    {
        return nullptr;
    }
    else
    {
        return iterator->second;
    }
}
