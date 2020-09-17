#pragma once

#include <SDK.h>
#include "Utilities.hpp"

class WasmResource : public alt::IResource::Impl
{
public:
    WasmResource(alt::IResource* resource);

    alt::IResource* resource = nullptr;
    wasm_instance_t* instance = nullptr;
    wasm_module_t* module = nullptr;

    std::unordered_map<int32_t, void*> pointerTable32_64;
    std::unordered_map<void*, int32_t> pointerTable64_32;

    std::unordered_map<std::string, wasm_func_t*> funcExportsMap;
    std::unordered_map<std::string, wasm_global_t*> globalExportsMap;
    std::unordered_map<std::string, wasm_memory_t*> memoryExportsMap;
    std::unordered_map<std::string, wasm_table_t*> tableExportsMap;

    bool Start() override;
    bool Stop() override;

    bool OnEvent(const alt::CEvent* ev) override;
    void OnTick() override;

    void OnCreateBaseObject(alt::Ref<alt::IBaseObject> object) override;
    void OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object) override;

    template <typename K, typename T = K>
    T CallFunction(std::string funcName, std::vector<wasm_val_t> args = {})
    {
        wasmtime_error_t* error = nullptr;
        wasm_trap_t* trap = nullptr;

        wasm_func_t* func = this->FindExportedFunction(funcName);
        if (func == nullptr)
        {
            throw std::runtime_error("Exported function not found: " + funcName);
        }

        size_t argsSize = wasm_func_param_arity(func);
        size_t resultsSize = wasm_func_result_arity(func);

        if (argsSize != args.size())
        {
            throw std::runtime_error("[WASM] Arguments length doesn't match");
        }

        std::vector<wasm_val_t> results;
        results.resize(resultsSize);

        error = wasmtime_func_call(func, args.data(), args.size(), results.data(), resultsSize, &trap);
        if (error != nullptr || trap != nullptr)
        {
            Utilities::LogWasmError("Failed to call function: " + funcName, error, trap);
            throw std::runtime_error("");
        }

        if(std::is_same<K, i32>::value)
        {
            return (T)(results[0].of.i32);
        }
        else if(std::is_same<K, i64>::value)
        {
            return (T)(results[0].of.i64);
        }
        else if(std::is_same<K, f32>::value)
        {
            return (T)(results[0].of.f32);
        }
        else if(std::is_same<K, f64>::value)
        {
            return (T)(results[0].of.f64);
        }
    }

    wasm_func_t* FindExportedFunction(const std::string& name);
    wasm_global_t* FindExportedGlobal(const std::string& name);
    wasm_memory_t* FindExportedMemory(const std::string& name);
    wasm_table_t* FindExportedTable(const std::string& name);

    void* GetPointer(int32_t id)
    {
        auto iterator = this->pointerTable32_64.find(id);

        if (iterator == this->pointerTable32_64.end())
        {
            Utilities::LogError("[WASM] Pointer with ID [" + std::to_string(id) + "] was not found in the pointer table");
            return nullptr;
        }

        return iterator->second;
    }

    template <typename T>
    int32_t GetPointerID(T* pointer)
    {
        auto iterator = this->pointerTable64_32.find(pointer);
        auto id = 0;

        if (iterator == this->pointerTable64_32.end())
        {
            id = this->pointerTable64_32.size();

            while(this->pointerTable32_64.find(id) != this->pointerTable32_64.end()) {
                id++;
            }

            this->pointerTable64_32.emplace(pointer, id);
            this->pointerTable32_64.emplace(id, pointer);
        }
        else
        {
            id = iterator->second;
        }

        return id;
    }
};
