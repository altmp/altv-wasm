#pragma once

#include <SDK.h>
#include <wasmtime.h>

class WasmRuntime : public alt::IScriptRuntime
{
public:
    static WasmRuntime *&Instance()
    {
        static WasmRuntime* instance = nullptr;
        return instance;
    }

    wasm_engine_t *engine = nullptr;
    wasm_store_t *store = nullptr;

    WasmRuntime();
    bool Init();

    virtual bool RequiresMain() const override;

    // Create resource
    virtual alt::IResource::Impl *CreateImpl(alt::IResource *resource) override;
    // Remove resource
    virtual void DestroyImpl(alt::IResource::Impl *impl) override;

    virtual void OnTick() override;
    virtual void OnDispose() override;
};
