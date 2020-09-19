#include <wasmtime.h>
#include <string>
#include <vector>
#include <iostream>
#include "WasmImport.hpp"

namespace WasmExports
{
    static wasm_trap_t* ICore_Instance(const wasm_val_t args[], wasm_val_t results[])
    {
        std::cout << "ICore_Instance" << std::endl;

        return nullptr;
    }

    static wasm_trap_t* ICore_LogInfo(const wasm_val_t args[], wasm_val_t results[])
    {
        std::cout << "ICore_LogInfo" << std::endl;

        return nullptr;
    }

    static wasm_trap_t* CEvent_GetType(const wasm_val_t args[], wasm_val_t results[])
    {
        std::cout << "CEvent_GetType" << std::endl;

        return nullptr;
    }
}

void logWasmError(const std::string& message, wasmtime_error_t* error, wasm_trap_t* trap)
{
    std::cerr << message << std::endl;
    wasm_byte_vec_t error_message;

    if (error != nullptr)
    {
        wasmtime_error_message(error, &error_message);
        wasmtime_error_delete(error);
    }
    else
    {
        wasm_trap_message(trap, &error_message);
        wasm_trap_delete(trap);
    }

    fprintf(stderr, "%.*s\n", (int) error_message.size, error_message.data);
    wasm_byte_vec_delete(&error_message);
}

int main(int argc, char* argv[])
{
    std::cout << "-- altv-wasm Test Bench --" << std::endl;

    wasm_engine_t* engine = wasm_engine_new();
    if (engine == nullptr)
    {
        std::cerr << "[WASM] Failed to instantiate the wasm engine" << std::endl;
        return 1;
    }

    wasm_store_t* store = wasm_store_new(engine);
    if (store == nullptr)
    {
        std::cerr << "[WASM] Failed to instantiate the wasm store" << std::endl;
        return 1;
    }

    wasmtime_linker_t* linker = wasmtime_linker_new(store);
    if (linker == nullptr)
    {
        std::cerr << "[WASM] Failed to instantiate the wasmtime linker" << std::endl;
        return 1;
    }

    std::cout << "[WASM] Initialized runtime" << std::endl;

    wasmtime_error_t* error = nullptr;
    wasm_trap_t* trap = nullptr;

    std::string modNameS = "env";
    wasm_name_t modName;
    wasm_name_new_from_string(&modName, modNameS.c_str());

    auto MakeImport = [&](const std::string& name, wasm_func_callback_t func, const std::initializer_list<wasm_valkind_enum>& params, const std::initializer_list<wasm_valkind_enum>& results) {
        return WasmImport(store, modNameS, name, nullptr, func, params, results);
    };

    std::vector<WasmImport> imports = {
        MakeImport("alt_ICore_Instance", WasmExports::ICore_Instance, {}, {}),
        MakeImport("alt_ICore_LogInfo", WasmExports::ICore_LogInfo, {}, {}),
        MakeImport("alt_CEvent_GetType", WasmExports::CEvent_GetType, {}, {}),
    };

    wasm_name_t empty;
    wasm_name_new_from_string(&empty, "");

    for (auto& import : imports)
    {
        wasm_name_t moduleName;
        wasm_name_new_from_string(&moduleName, import.module.c_str());

        wasm_name_t importName;
        wasm_name_new_from_string(&importName, import.name.c_str());

        error = wasmtime_linker_define(linker, &moduleName, &importName, wasm_func_as_extern(import.function));
        if (error != nullptr)
        {
            logWasmError("[WASM] Failed to define import: " + import.module + "::" + import.name, error, nullptr);
        }
        else
        {
            std::cout << "[WASM] Defined import: " << import.module << "::" << import.name << std::endl;
        }

        wasm_name_delete(&moduleName);
        wasm_name_delete(&importName);
    }

    wasm_byte_vec_t wasm;
    wasm_instance_t* instance = nullptr;
    wasm_module_t* module = nullptr;

    FILE* file = fopen("resource.wasm", "rb");
    if (!file)
    {
        std::cerr << "[WASM] Could not open file" << std::endl;
        return 1;
    }

    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    wasm_byte_vec_new_uninitialized(&wasm, size);
    fseek(file, 0L, SEEK_SET);
    if (fread(wasm.data, size, 1, file) != 1)
    {
        std::cerr << "[WASM] Could not read wasm file properly" << std::endl;
        return 1;
    }

    std::cout << "[WASM] --- Create the motherfucking module" << std::endl;
    error = wasmtime_module_new(engine, &wasm, &module);
    if (error != nullptr)
    {
        logWasmError("[WASM] Failed to compile module", error, nullptr);
        return 1;
    }
    else
    {
        std::cout << "[WASM] Compiled wasm module" << std::endl;
    }

    std::cout << "[WASM] --- Let's instantiate this motherfucker" << std::endl;

    wasm_name_t icorefunc;
    wasm_name_new_from_string(&icorefunc, "alt_ICore_LogInfo");

    wasm_extern_t* extern_ = nullptr;
    wasmtime_linker_get_one_by_name(linker,  &modName, &icorefunc, &extern_);
    if (extern_ == nullptr)
    {
        std::cerr << "Shit's not there bruh" << std::endl;
    }

    error = wasmtime_linker_instantiate(linker, module, &instance, &trap);
    if (error != nullptr || trap != nullptr)
    {
        logWasmError("[WASM] Failed to instantiate module", error, trap);
        return 1;
    }
    else
    {
        std::cout << "[WASM] Instantiated module" << std::endl;
    }
}