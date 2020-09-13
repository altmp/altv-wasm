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
        this->CallFunction<void>("_start");
//        this->CallFunction<void>("__wasm_call_ctors");

        result = this->CallFunction<i32>("altMain", {{ .kind = WASM_I32, .of = { .i32 = this->GetPointerID(&alt::ICore::Instance()) }}});
    }
    catch (std::runtime_error &err)
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

wasm_func_t* WasmResource::FindExportedFunction(std::string func)
{
    auto iterator = this->exportsTable.find(func);

    if (iterator == this->exportsTable.end())
    {
        return nullptr;
    }
    else
    {
        return iterator->second;
    }
}