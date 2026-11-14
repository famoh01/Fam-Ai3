@echo off
setlocal enabledelayedexpansion
title Build Last Chaos Thai Client (THAILIVE ^| Win32)
cd /d "%~dp0"

echo ============================================================================
echo   Last Chaos Thailand Client Builder (THAILIVE ^| Win32 -> Bin\Nksp.exe)
echo ============================================================================
echo.

echo [Step 1/2] Running Ecc.exe on .es Entity files...
call "%~dp0pre_compile_es.bat"

echo.
echo [Step 2/2] Locating Visual Studio MSBuild...
set "MSBUILD_EXE="
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
    for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
        set "MSBUILD_EXE=%%i"
    )
)
if "%MSBUILD_EXE%"=="" (
    for %%p in (
        "%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
        "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
        "%ProgramFiles(x86)%\MSBuild\14.0\Bin\MSBuild.exe"
        "%ProgramFiles(x86)%\MSBuild\4.0\Bin\MSBuild.exe"
        "%WINDIR%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe"
    ) do (
        if exist %%~p set "MSBUILD_EXE=%%~p"
    )
)

if "%MSBUILD_EXE%"=="" (
    echo [!] MSBuild not found automatically. Please open Build_2010.sln in Visual Studio,
    echo     select Configuration = THAILIVE and Platform = Win32, and click Build Solution!
    pause
    exit /b 1
)

echo Found MSBuild: "%MSBUILD_EXE%"
set "THAI_LIVE=%~dp0"
"%MSBUILD_EXE%" "%~dp0Build_2010.sln" /p:Configuration=THAILIVE /p:Platform=Win32 /m
if errorlevel 1 (
    echo.
    echo [!] If upgrading from VS2010 v100 toolset on VS2019/2022, open Build_2010.sln once
    echo     in Visual Studio to Retarget Projects or install C++ v100/v142 build tools + DX8 SDK.
    pause
    exit /b 1
)

echo.
echo [SUCCESS] Built Thai Client Binaries in: %~dp0Bin\Nksp.exe
pause
