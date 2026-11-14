@echo off
chcp 65001 >nul
setlocal EnableDelayedExpansion
cd /d "%~dp0"

echo ============================================================================
echo   Last Chaos Thai - อัปโหลดขึ้นเว็บ GitHub เพื่อสั่งคอมไพล์อัตโนมัติ (GitHub Actions)
echo ============================================================================
echo.

where git >nul 2>nul
if errorlevel 1 (
    echo [!] ไม่พบโปรแกรม Git ในเครื่องของคุณ
    echo     ดาวน์โหลด Git for Windows ได้ที่: https://git-scm.com/download/win
    echo     หรือเปิดโฟลเดอร์นี้ด้วยโปรแกรม GitHub Desktop ^(https://desktop.github.com^) ได้เลย!
    pause
    exit /b 1
)

echo กรุณาวางลิงก์ Repository บนเว็บ GitHub ของคุณ
echo ตัวอย่าง: https://github.com/ชื่อผู้ใช้ของคุณ/lastchaos-thai.git
set /p REPO_URL="GitHub Repository URL: "
if "%REPO_URL%"=="" (
    echo [!] คุณยังไม่ได้ใส่ลิงก์ GitHub Repository
    pause
    exit /b 1
)

if not exist ".git" (
    git init
)
git config http.postBuffer 524288000
git branch -M main

echo.
echo [*] กำลังเตรียมไฟล์ทั้งหมดเข้าสู่ระบบ Git...
git add -A
git commit -m "Setup Last Chaos Thai Client & GitHub Actions Cloud Build"
git remote remove origin >nul 2>nul
git remote add origin "%REPO_URL%"

echo.
echo [*] กำลังอัปโหลดขึ้นเว็บ GitHub ^(%REPO_URL%^)...
git push -u origin main

if errorlevel 1 (
    echo.
    echo [!] อัปโหลดไม่สำเร็จ กรุณาตรวจสอบสิทธิ์ล็อกอิน GitHub หรือ URL ของ Repository
    pause
    exit /b 1
)

echo.
echo ============================================================================
echo   [สำเร็จ!] อัปโหลดขึ้นเว็บ GitHub เรียบร้อยแล้ว!
echo   1. เปิดหน้าเว็บ GitHub ของคุณแล้วคลิกที่แท็บ "Actions" ด้านบน
echo   2. ระบบกำลังคอมไพล์ Nksp.exe + Engine.dll + EntitiesMP.dll + GameMP.dll + Shaders.dll ให้อัตโนมัติ!
echo   3. เมื่อขึ้นเครื่องหมายถูกสีเขียว เลื่อนลงไปหัวข้อ "Artifacts" เพื่อดาวน์โหลดไฟล์ไปใช้งานได้เลย!
echo ============================================================================
pause
