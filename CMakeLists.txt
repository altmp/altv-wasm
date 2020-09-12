cmake_minimum_required(VERSION 3.10)

project(altv-wasm)

set(ALTV_WASM_DEPS ${CMAKE_SOURCE_DIR}/deps)
set(ALTV_WASM_SOURCES
        src/main.cpp
        src/WasmRuntime.cpp
        src/WasmResource.cpp
)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /EHsc /MT /Zi /bigobj")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /EHsc /MTd /bigobj")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG:FULL /OPT:REF /OPT:ICF")

include_directories(
        ${ALTV_WASM_DEPS}/wasmtime/include
        ${ALTV_WASM_DEPS}/altv-capi/capi/BUILD/altv-capi-client-static/include
        ${ALTV_WASM_DEPS}/altv-capi/cpp-sdk
        )
link_directories(
        ${ALTV_WASM_DEPS}/wasmtime/lib/${CMAKE_BUILD_TYPE}
        ${ALTV_WASM_DEPS}/altv-capi/capi/BUILD/altv-capi-client-static$<IF:$<CONFIG:Debug>,-mtd,>/lib/${CMAKE_BUILD_TYPE}
        )
add_definitions(
        -DWASM_API_EXTERN=
        -DWASI_API_EXTERN=
        -D_CRT_SECURE_NO_WARNINGS
        )

# ----------------------------
#           Static
# ----------------------------
add_library(altv-wasm-static STATIC
        ${ALTV_WASM_SOURCES}
        )

target_link_libraries(altv-wasm-static PUBLIC
        # platform libs
        ws2_32.lib
        advapi32.lib
        userenv.lib
        ntdll.lib
        shell32.lib
        ole32.lib

        altv-capi-client-static$<IF:$<CONFIG:Debug>,-mtd,>.lib
        wasmtime.lib
        )

set_target_properties(altv-wasm-static PROPERTIES
        # OUTPUT_NAME "altv-wasm"
        CXX_STANDARD 17
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
        )

# ----------------------------
#           Shared
# ----------------------------
add_library(altv-wasm-shared SHARED
        ${ALTV_WASM_SOURCES}
        )

target_link_libraries(altv-wasm-shared PUBLIC
        # platform libs
        ws2_32.lib
        advapi32.lib
        userenv.lib
        ntdll.lib
        shell32.lib
        ole32.lib

        altv-capi-client-static$<IF:$<CONFIG:Debug>,-mtd,>.lib
        wasmtime.lib

        libvcruntime.lib # __imp_calloc
        # libucrt.lib
        # libcmt.lib
        # libcpmt.lib
        )

set_target_properties(altv-wasm-shared PROPERTIES
        OUTPUT_NAME "altv-wasm"
        CXX_STANDARD 17
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
        )
