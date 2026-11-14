@echo off
title Pre-Compile Serious Engine .es Entities (Ecc.exe)
cd /d "%~dp0"
echo Compiling Engine\Classes\*.es with Ecc.exe...
for %%i in (Engine\Classes\*.es) do (
    "%~dp0Ecc.exe" "%%i"
)
echo Compiling EntitiesMP\*.es with Ecc.exe...
for %%i in (EntitiesMP\*.es) do (
    "%~dp0Ecc.exe" "%%i"
)
echo Done! All 108 .es entity files compiled to .cpp / .h / _tables.h.
