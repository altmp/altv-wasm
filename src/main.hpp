#include "altv-capi-client.h"
#include "util.hpp"
#include "wasmtime.h"
#include "resource.hpp"
#include "structs.hpp"

CAPI_EXPORT alt_IResource_Impl *create_resource(alt_IScriptRuntime *runtime, alt_IResource *resource);
CAPI_EXPORT void remove_resource(alt_IScriptRuntime *runtime, alt_IResource_Impl *resource_impl);
CAPI_EXPORT void tick(alt_IScriptRuntime *runtime);
CAPI_EXPORT alt_IScriptRuntime *altMain(alt_ICore* core);
