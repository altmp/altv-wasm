#pragma once
#pragma once

#include <SDK.h>
#include "util.hpp"

class WasmResource : public alt::IResource::Impl
{
public:
    alt::IResource* resource = nullptr;
    wasm_instance_t *instance = nullptr;
    wasm_module_t *module = nullptr;

    WasmResource(alt::IResource* resource, wasm_instance_t *instance, wasm_module_t *module);
        
    bool Start() override;
    bool Stop() override;

    bool OnEvent(const alt::CEvent* ev) override;
    void OnTick() override;

    void OnCreateBaseObject(alt::Ref<alt::IBaseObject> object) override;
    void OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object) override;
};
