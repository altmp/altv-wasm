#pragma once

#include <wasmtime.h>
#include <sstream>
#include "Utilities.hpp"
#include "WasmStructs.hpp"

namespace WasmExports
{
    static wasm_trap_t* ICore_Instance(void* env, const wasm_val_t args[], wasm_val_t results[])
    {
        auto wasmResource = static_cast<WasmResource*>(env);
        auto core = alt_ICore_Instance();

        results[0].kind = WASM_I32;
        results[0].of.i32 = wasmResource->GetPointerID(core);

        return nullptr;
    }

    static wasm_trap_t* ICore_LogInfo(void* env, const wasm_val_t args[], wasm_val_t results[])
    {
        auto wasmResource = static_cast<WasmResource*>(env);
        auto core = static_cast<alt_ICore*>(wasmResource->GetPointer(args[0].of.i32));

        wasm_memory_t* memory = wasmResource->FindExportedMemory("memory");

        auto wasmStringView = WasmPtr<Wasm::alt_StringView>(args[1]).Get(memory);
        char* string = wasmStringView->data.Get(memory);

        alt_StringView stringView { string, wasmStringView->size };
        alt_ICore_LogInfo(core, &stringView);

        return nullptr;
    }

    static wasm_trap_t* CEvent_GetType(void* env, const wasm_val_t args[], wasm_val_t results[])
    {
        auto wasmResource = static_cast<WasmResource*>(env);
        auto event = static_cast<alt::CEvent*>(wasmResource->GetPointer(args[0].of.i32));
        auto eventType = (i32)event->GetType();

        std::ostringstream output;
        output << "Event type is: " << eventType;

        // Log here is incorrect.
        Utilities::LogInfo(output.str());

        results[0].kind = WASM_I32;
        results[0].of.i32 = eventType;

        return nullptr;
    }
}