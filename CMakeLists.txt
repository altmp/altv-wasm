cmake_minimum_required (VERSION 3.10)

project(altv-wasm)

include_directories(
  deps/altv-capi/capi/BUILD/altv-capi-client-static/include
)

add_library(altv-wasm-static STATIC
  src/main.cpp
)
target_link_directories(altv-wasm-static PUBLIC
  deps/wasmtime/${CMAKE_BUILD_TYPE}
)
target_link_libraries(altv-wasm-static PUBLIC
  # platform libs
  ws2_32.lib
  advapi32.lib
  userenv.lib
  ntdll.lib
  shell32.lib
  ole32.lib

  deps/altv-capi/capi/BUILD/altv-capi-client-static/lib/Debug/altv-capi-client-static.lib
  # altv-capi-client-static$<$<CONFIG:Debug>:-mtd>
  # wasmtime.lib
)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /Zi")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

set_target_properties(altv-wasm-static PROPERTIES
  # OUTPUT_NAME "altv-wasm"
  CXX_STANDARD 17
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release"
)
