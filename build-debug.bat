@echo off
ECHO "NEEDS FIX, BROKEN"

CD .\deps\altv-capi\
if not exist .\tools\altv-capi-gen.exe call .\tools\get-gen.bat
if not exist cpp-sdk call .\tools\get-cppsdk.bat

CD .\capi\
call .\gen-client.bat

cmake -B BUILD -DCMAKE_BUILD_TYPE=RelWithDebInfo --target altv-capi-client-static .
cmake --build BUILD --config RelWithDebInfo --target altv-capi-client-static

CD ..\..\..\
cmake -B BUILD-DEBUG
cmake --build BUILD-DEBUG
