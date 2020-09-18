#pragma once

#include <wasmtime.h>
#include <string>

class WasmImport
{
public:
  std::string module;
  std::string name;
  void* env = nullptr;
  wasm_func_callback_with_env_t func;
  wasm_func_t* function = nullptr;

  WasmImport(wasm_store_t* store, const std::string& module, const std::string& name, void* env, wasm_func_callback_with_env_t func, const std::initializer_list<wasm_valkind_enum>& params, const std::initializer_list<wasm_valkind_enum>& results);
};
