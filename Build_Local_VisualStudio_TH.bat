@echo off
chcp 65001 >nul
setlocal
cd /d "%~dp0"

echo ============================================================================
echo   คอมไพล์ Last Chaos Thai (THAILIVE ^| Win32) บนเครื่องตัวเองด้วย Visual Studio 2022
echo ============================================================================

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo [!] ไม่พบ Visual Studio 2022 ในเครื่อง (แนะนำให้อัปขึ้นเว็บ GitHub เพื่อคอมไพล์ฟรีผ่าน GitHub Actions!)
    pause
    exit /b 1
)

for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
    set "MSBUILD_EXE=%%i"
)

if "%MSBUILD_EXE%"=="" (
    echo [!] ไม่พบ MSBuild.exe กรุณาติดตั้ง Desktop development with C++ + MFC
    pause
    exit /b 1
)

echo [*] ใช้ MSBuild: "%MSBUILD_EXE%"
echo [*]หมายเหตุ: หากคอมไพล์บนเครื่องตัวเอง ต้องติดตั้ง Boost x86 และตั้งค่าตัวแปร BOOST_ROOT ก่อน
echo.

"%MSBUILD_EXE%" "ClientSource\Ecc\Ecc_2010.vcxproj" /p:Configuration=Release /p:Platform=Win32 /m /v:minimal || goto :err
"%MSBUILD_EXE%" "ClientSource\3rdparty\3rdparty.sln" /p:Configuration=Release /p:Platform=Win32 /m /v:minimal || goto :err
"%MSBUILD_EXE%" "ClientSource\SharedMemory\SharedMemory.sln" /p:Configuration=Release /p:Platform=Win32 /m /v:minimal || goto :err
"%MSBUILD_EXE%" "ClientSource\Build_2010.sln" /p:Configuration=THAILIVE /p:Platform=Win32 /m /v:minimal || goto :err

echo.
echo [สำเร็จ!] ไฟล์ที่คอมไพล์เสร็จแล้วอยู่ในโฟลเดอร์ ClientSource\Bin\
dir "ClientSource\Bin\*.exe" "ClientSource\Bin\*.dll"
pause
exit /b 0

:err
echo.
echo [!] เกิดข้อผิดพลาดในการคอมไพล์ (ตรวจสอบว่าติดตั้ง Boost x86 และ C++ MFC x86 ครบถ้วนแล้ว)
pause
exit /b 1
