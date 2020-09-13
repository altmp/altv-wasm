#pragma once

#include <filesystem>
#include <time.h>
#include <string>
#include <SDK.h>
#include <altv-capi-client.h>
#include "wasmtime.h"

using i32 = int32_t;
using i64 = int64_t;
using f32 = float32_t;
using f64 = float64_t;

namespace Utilities
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

    template<std::size_t N>
    inline void LogInfo(const char (&str)[N])
    {
        alt::StringView stringView {(char*)str, N+1};
        alt::ICore::Instance().LogInfo(stringView);
    }

    inline void LogInfo(const std::string& str)
    {
        alt::StringView stringView {(char*)str.data(), str.length() + 1};
        alt::ICore::Instance().LogInfo(stringView);
    }

    inline void LogInfo(alt::StringView stringView)
    {
        alt::ICore::Instance().LogInfo(stringView);
    }

    template<std::size_t N>
    inline void LogError(const char (&str)[N])
    {
        alt::StringView stringView {(char*)str, N+1};
        alt::ICore::Instance().LogError(stringView);
    }

    inline void LogError(const std::string& str)
    {
        alt::StringView stringView {(char*)str.data(), str.length() + 1};
        alt::ICore::Instance().LogError(stringView);
    }

    inline void LogError(alt::StringView stringView)
    {
        alt::ICore::Instance().LogError(stringView);
    }

    template<std::size_t N>
    inline void LogWarning(const char (&str)[N])
    {
        alt::StringView stringView {(char*)str, N+1};
        alt::ICore::Instance().LogWarning(stringView);
    }

    inline void LogWarning(const std::string& str)
    {
        alt::StringView stringView {(char*)str.data(), str.length() + 1};
        alt::ICore::Instance().LogWarning(stringView);
    }

    inline void LogWarning(alt::StringView stringView)
    {
        alt::ICore::Instance().LogWarning(stringView);
    }

    template<std::size_t N>
    inline void LogColored(const char (&str)[N])
    {
        alt::StringView stringView {(char*)str, N+1};
        alt::ICore::Instance().LogColored(stringView);
    }

    inline void LogColored(const std::string& str)
    {
        alt::StringView stringView {(char*)str.data(), str.length() + 1};
        alt::ICore::Instance().LogColored(stringView);
    }

    inline void LogColored(alt::StringView stringView)
    {
        alt::ICore::Instance().LogColored(stringView);
    }

    template<std::size_t N>
    inline bool FileExists(const char (&str)[N])
    {
        alt_StringView sw{(char*)str, N+1};
        return alt_ICore_FileExists(alt_ICore_Instance(), &sw);
    }

    inline void LogWasmError(const std::string& message, wasmtime_error_t *error, wasm_trap_t *trap)
    {
        LogError(message + ":");
        wasm_byte_vec_t error_message;

        if (error != nullptr) {
            wasmtime_error_message(error, &error_message);
            wasmtime_error_delete(error);
        } else {
            wasm_trap_message(trap, &error_message);
            wasm_trap_delete(trap);
        }

        alt_StringView sw {(char*)error_message.data, error_message.size + 1};
        alt_ICore_LogError(alt_ICore_Instance(), &sw);
    }

    inline std::string boolean_to_string(bool x)
    {
        return x ? "true" : "false";
    }
}
