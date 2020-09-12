@echo off
ECHO "NEEDS FIX, BROKEN"

CD .\deps\altv-capi\
if not exist .\tools\altv-capi-gen.exe call .\tools\get-gen.bat
if not exist cpp-sdk call .\tools\get-cppsdk.bat

CD .\capi\
call .\gen-client.bat

cmake -B BUILD --target altv-capi-client-static-mtd .
cmake --build BUILD --config Debug --target altv-capi-client-static-mtd

CD ..\..\..\
cmake -B BUILD
cmake --build BUILD --config Debug
