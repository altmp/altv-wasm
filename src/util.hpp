#pragma once

#include <filesystem>
#include <time.h>
#include <string>
#include "altv-capi-client.h"
#include "wasmtime.h"

namespace util
{
    inline auto GetTimestamp()
    {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof(buffer),"%d-%m-%Y-%H:%M:%S", timeinfo);
        std::string str(buffer);

        return str;
    }

    alt_ICore *core()
    {
        return alt_ICore_Instance();
    }

    template<std::size_t N>
    inline void logi(const char (&str)[N])
    {
        alt_StringView sw {(char*)str, N+1};
        alt_ICore_LogInfo(core(), &sw);
    }

    inline void logi(const std::string& str)
    {
        alt_StringView sw {(char*)str.data(), str.length()+1};
        alt_ICore_LogInfo(core(), &sw);
    }

    template<std::size_t N>
    inline void loge(const char (&str)[N])
    {
        alt_StringView sw {(char*)str, N+1};
        alt_ICore_LogError(core(), &sw);
    }

    inline void loge(const std::string& str)
    {
        alt_StringView sw {(char*)str.data(), str.length() + 1};
        alt_ICore_LogError(core(), &sw);
    }

    template<std::size_t N>
    inline void logw(const char (&str)[N])
    {
        alt_StringView sw {(char*)str, N+1};
        alt_ICore_LogWarning(core(), &sw);
    }

    inline void logw(const std::string& str)
    {
        alt_StringView sw {(char*)str.data(), str.length() + 1};
        alt_ICore_LogWarning(core(), &sw);
    }

    template<std::size_t N>
    inline bool FileExists(const char (&str)[N])
    {
        alt_StringView sw{(char*)str, N+1};
        return alt_ICore_FileExists(core(), &sw);
    }

    inline std::string from_stringview(alt_StringView sw)
    {
        return std::string(sw.data);
    }

    inline void logwe(const std::string& message, wasmtime_error_t *error, wasm_trap_t *trap)
    {
        loge(message + ":");
        wasm_byte_vec_t error_message;

        if (error != nullptr) {
            wasmtime_error_message(error, &error_message);
            wasmtime_error_delete(error);
        } else {
            wasm_trap_message(trap, &error_message);
            wasm_trap_delete(trap);
        }

        wasm_byte_vec_delete(&error_message);

        alt_StringView sw {(char*)error_message.data, error_message.size};
        alt_ICore_LogError(core(), &sw);
    }

    inline std::string boolean_to_string(bool x)
    {
        return x ? "true" : "false";
    }
}