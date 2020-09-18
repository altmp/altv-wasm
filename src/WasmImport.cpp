#include "WasmImport.hpp"
#include "Utilities.hpp"

WasmImport::WasmImport(wasm_store_t *store, const std::string &module, const std::string &name, void *env, wasm_func_callback_with_env_t func, const std::initializer_list<wasm_valkind_enum> &params, const std::initializer_list<wasm_valkind_enum> &results)
    : func(func), module(module), name(name), env(env)
{
    auto MakeValtypes = [](const std::initializer_list<wasm_valkind_enum> &_types) {
        wasm_valtype_vec_t types;
        wasm_valtype_vec_new_uninitialized(&types, _types.size());

        auto i = 0;
        for (auto p : _types)
        {
            switch (p)
            {
                case WASM_I32:
                {
                    types.data[i] = wasm_valtype_new_i32();
                    break;
                }
                case WASM_I64:
                {
                    types.data[i] = wasm_valtype_new_i64();
                    break;
                }
                case WASM_F32:
                {
                    types.data[i] = wasm_valtype_new_f32();
                    break;
                }
                case WASM_F64:
                {
                    types.data[i] = wasm_valtype_new_f64();
                    break;
                }

                default:
                {
                    // error
                    break;
                }
            }

            i++;
        }

        return types;
    };

    auto ClearValtypes = [](wasm_valtype_vec_t &types) {
        for (size_t i = 0; i < types.size; i++)
        {
            wasm_valtype_delete(types.data[i]);
        }
    };

    auto wparams = MakeValtypes(params);
    auto wresults = MakeValtypes(results);

    wasm_functype_t *type = wasm_functype_new(&wparams, &wresults);
    function = wasm_func_new_with_env(store, type, func, env, nullptr);

    wasm_functype_delete(type);

    ClearValtypes(wparams);
    ClearValtypes(wresults);
}
