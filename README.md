# 🇹🇭 Last Chaos เซิร์ฟเวอร์ภาษาไทย (Windows `.exe`) + ระบบคอมไพล์อัตโนมัติบนเว็บ GitHub (GitHub Actions)

ชุดไฟล์เซิร์ฟเวอร์และซอร์สโค้ดตัวเกมจริงจาก **`OllyBaru/Last-Chaos` (`ServerRelease`)** และ **`openlastchaos/lastchaos-source-client` (`Serious Engine 1 / Nksp`)** ที่ถูกแปลงและปรับแต่งโปรเจกต์ทั้งหมดให้สามารถ **สั่งคอมไพล์บนเว็บ GitHub (`GitHub Actions` บนเครื่อง `windows-latest` / Visual Studio 2022 `v143`+) ได้ทันทีโดยไม่ต้องลง Visual Studio ในเครื่องตัวเอง!**

---

## 🚀 ส่วนที่ 1: วิธีอัปโหลดและสั่งคอมไพล์บนเว็บ GitHub (ไม่ต้องลง Visual Studio!)

เมื่อแตกไฟล์ **`Last-Chaos-Thai-Windows-Server-Pack.zip`** ออกมาแล้ว จะเห็นโฟลเดอร์ `.github/workflows/build-lastchaos-thai.yml` อยู่ด้านในพร้อมใช้งานทันที

### ขั้นตอนที่ 1: สร้าง Repository ใหม่บนเว็บ GitHub
1. เข้าเว็บ [https://github.com/new](https://github.com/new)
2. ตั้งชื่อ Repository เช่น `lastchaos-thai`
3. เลือกเป็น **Private** (ส่วนตัว — แนะนำ!) หรือ **Public**
4. **ไม่ต้องติ๊ก** *Add a README file* (ปล่อยว่างไว้) แล้วกดปุ่มสีเขียว **Create repository**
5. คัดลอกลิงก์ URL ของ Repository เช่น `https://github.com/ชื่อคุณ/lastchaos-thai.git`

### ขั้นตอนที่ 2: อัปโหลดไฟล์ขึ้นเว็บ GitHub (เลือกวิธีที่สะดวกที่สุด 1 วิธี)

#### วิธีที่ A (ง่ายที่สุด — ดับเบิลคลิกไฟล์เดียวบน Windows)
1. แตกไฟล์ `.zip` ลงในโฟลเดอร์ เช่น `D:\LastChaos-Thai\`
2. ดับเบิลคลิกไฟล์ **`Push_To_GitHub_อัปขึ้นเว็บอัตโนมัติ.bat`**
3. กดเลือก **`1`** (*อัปเฉพาะโค้ดตัวเกม `ClientSource` + `Tools` ~90 MB เพื่อคอมไพล์ไวในไม่กี่วินาที* — หรือกด `2` หากต้องการเก็บ `ServerRelease` ไว้บน GitHub ด้วย)
4. วางลิงก์ GitHub Repository ของคุณแล้วกด `Enter` ระบบจะส่งไฟล์ขึ้นเว็บ GitHub ให้อัตโนมัติ!

#### วิธีที่ B (ผ่านโปรแกรม GitHub Desktop — ไม่ต้องพิมพ์คำสั่ง)
1. เปิดโปรแกรม **GitHub Desktop** -> เมนู **File -> Add local repository...**
2. เลือกโฟลเดอร์ที่คุณแตกไฟล์ `.zip` ไว้ (ต้องเป็นระดับโฟลเดอร์ที่มี `.github` และ `ClientSource` อยู่ข้างใน) -> คลิก *create a repository* หากโปรแกรมถาม
3. พิมพ์ Summary ว่า `Initial commit` -> กด **Commit to main** -> กด **Publish repository** ขึ้นเว็บ GitHub!

#### วิธีที่ C (ทำบนเว็บเบราว์เซอร์ 100% ผ่าน GitHub Codespaces — ไม่ต้องลง Git ในเครื่อง)
1. ในหน้าเว็บ Repository ว่างบน GitHub กดคลิก *creating a new file* พิมพ์ชื่อ `init.txt` แล้วกด **Commit changes**
2. กดปุ่มสีเขียว **`<> Code`** -> แท็บ **Codespaces** -> กด **Create codespace on main**
3. ลากไฟล์ `Last-Chaos-Thai-Windows-Server-Pack.zip` จากคอมของคุณวางใส่แถบซ้ายในหน้าเว็บ Codespace แล้วพิมพ์ในช่อง Terminal ด้านล่าง:
   ```bash
   unzip -o Last-Chaos-Thai-Windows-Server-Pack.zip
   rm -f Last-Chaos-Thai-Windows-Server-Pack.zip init.txt
   git add .github .gitignore .gitattributes README.md ClientSource Client_Patch_TH Tools_Windows_EXE Database_SQL
   git commit -m "Upload Last Chaos Thai for GitHub Actions Build"
   git push origin main
   ```

---

### ขั้นตอนที่ 3: ดูผลคอมไพล์และกดดาวน์โหลดไฟล์ `.exe` / `.dll` บนเว็บ GitHub!

1. เปิดหน้าเว็บ Repository ของคุณบน GitHub แล้วคลิกแท็บ **`Actions`** ด้านบนสุด
2. คุณจะเห็นงานชื่อ **`Build Last Chaos Thai (Windows Client & Tools)`** กำลังรันคอมไพล์ให้อัตโนมัติ!
   *(หรือถ้าต้องการสั่งคอมไพล์เองเมื่อไรก็ได้ ให้คลิกชื่อ **`Build Last Chaos Thai (Windows Client & Tools)`** ทางซ้ายมือ -> กดปุ่ม **`Run workflow`** -> เลือกโหมด **`THAILIVE`** -> ติ๊กถูกช่อง **สร้างหน้าดาวน์โหลด Releases** หากต้องการให้ขึ้นหน้า Releases ถาวร -> กดปุ่มสีเขียว **`Run workflow`**)*
3. รอประมาณ **4–7 นาที** จนขึ้นเครื่องหมายถูกสีเขียว ✅
4. คลิกเข้าไปในรายการที่ขึ้น ✅ แล้วเลื่อนลงมาด้านล่างสุดที่หัวข้อ **`Artifacts`**:
   - คลิกดาวน์โหลด **`LastChaos-Thai-Client-Binaries-Win32`** ได้ทันที!
   - ข้างในจะได้ไฟล์ที่เพิ่งคอมไพล์สดๆ จากโค้ด C++ ครบชุด:
     - `Bin/Nksp.exe` (ตัวรันเกมหลักโหมดภาษาไทย `G_THAI`)
     - `Bin/Engine.dll` (เอนจินเกมรองรับฟอนต์/รหัสภาษาไทย TIS-620 / CP874 + Lua 5.1.5 + DirectX 8 + Boost)
     - `Bin/EntitiesMP.dll` (ระบบตัวละคร มอนสเตอร์ สกิล สัตว์เลี้ยง 108 คลาส `.es`)
     - `Bin/GameMP.dll` (ระบบเกมเพลย์หลัก)
     - `Bin/Shaders.dll` (ระบบเรนเดอร์เชดเดอร์ 3D)
     - `LastChaosThai.exe` (Launcher ภาษาไทย), `LastChaosServerManagerTH.exe`, `LastChaosSLDtaToolTH.exe`, `LastChaosLodThaiTool.exe` และไฟล์แพตช์ `sl.dta` / `strClient_th.lod`!

---

## 🛠️ ส่วนที่ 2: รายการสิ่งที่แปลงให้โค้ดต้นฉบับคอมไพล์บนเว็บ GitHub (`VS 2022 v143+`) สำเร็จ

ซอร์สโค้ดต้นฉบับของ Last Chaos ถูกเขียนบน Visual C++ 6.0 / Visual Studio 2010 (`v100`) ซึ่งปกติจะคอมไพล์บน GitHub Actions ไม่ผ่านเลย โดยแพ็กเกจนี้ได้แปลงและแก้ปัญหาครบทุกจุดแล้ว:

1. **ฝังชุด DirectX 8 SDK (`ClientSource/SDK/DX8/{Include,Lib}`)** มาให้ในโปรเจกต์ครบ (`d3d8.h`, `d3dx8*.h`, `d3d8.lib`, `d3dx8.lib`, `dinput8.lib`, `dxguid.lib`) และตัดไฟล์หัวรุ่นเก่า (`basetsd.h`) ที่ชนกับ `POINTER_64` ของ Windows 10/11 SDK ออกเรียบร้อย
2. **อัปเกรดไฟล์ `.sln` และ `.vcxproj` ทั้งหมด** (`Build_2010.sln`, `3rdparty.sln`, `SharedMemory.sln`, `Ecc_2010.vcxproj`) ให้รองรับ `PlatformToolset` สมัยใหม่ (`v143` / `v145` / `$(DefaultPlatformToolset)`), `WindowsTargetPlatformVersion 10.0`, `<ConformanceMode>false</ConformanceMode>`, `/std:c++14`, `/Zc:forScope-`, `/Zc:strictStrings-`, `/Zc:referenceBinding-`, `/Zc:inline-`, `/FS` (ป้องกัน `C1041` เวลาคอมไพล์หลายคอร์พร้อมกัน) และ `/SAFESEH:NO` (ป้องกัน `LNK2026` บนไลบรารี x86)
3. **แก้บั๊ก `UpgradeFromVC60.props` หายบน VS 2022 (`MSB4019`)** ในทุกไฟล์ `.vcxproj` ทั้ง 23 โปรเจกต์ และแก้ `Common.vcxproj` จาก `Application` ที่ไม่มี `main()` (`LNK1561`) เป็น `Utility`
4. **เพิ่มโปรเจกต์ `lua51.vcxproj` (Lua 5.1.5 C Source แท้)** เข้าใน `3rdparty.sln` เพื่อคอมไพล์ `Engine/lua/lua5.1.lib` ใหม่ด้วย Universal CRT (`v143` `/MD`) แก้ปัญหา `LNK2019: unresolved external symbol ___iob_func` ของ `lua5.1.lib` รุ่นเก่า พร้อมเติมไฟล์ `Engine/lua/lauxlib.h` ที่ต้นฉบับขาดหาย
5. **ปรับปรุง `RuntimeLibrary` ให้ตรงกันทั้งหมดเป็น `/MD` (`MultiThreadedDLL`)** ใน `tinyxml`, `zlib`, `libPng`, `OpenAES`, `lua51` และ `SharedMemory` ป้องกัน `LNK2038: RuntimeLibrary mismatch` และแก้ `gzguts.h` เรื่อง `#define snprintf _snprintf` บน VS 2015+ (`C1189`)
6. **รองรับ Modern Boost (1.70 – 1.90+) บน GitHub Actions**:
   - แก้ `Engine/Network/NetClient.h` และ `NetClient.cpp` ให้รองรับ `boost::asio::io_context` และ `_socket.get_executor()` (แทน `io_service` ที่ถูกถอดใน Boost รุ่นใหม่)
   - ป้องกันมาโคร `#define B / D / W / Q / O` ใน `Engine/Math/Matrix12.h` ไปทำลายเทมเพลตของ Boost (`boost/type_traits/is_base_of.hpp`) ด้วย `#pragma push_macro` / `pop_macro`
   - ตั้งค่า `vcpkg` (`x86-windows-static-md`) พร้อมระบบ Cache และสร้าง `Directory.Build.targets` อัตโนมัติ
7. **แก้โค้ด C++14 & `THAILIVE` ที่ต้นฉบับมีบั๊ก**:
   - คอมไพล์ไฟล์เอนทิตี้ `.es` ทั้ง 108 ไฟล์ล่วงหน้าด้วย `Ecc` ที่ขยาย `YYMAXDEPTH=500000` (ไม่ติด Stack Overflow ที่ `Player.es`)
   - แก้ `CEntityID::operator=`, `CDrawPort::operator=`, `CEffectGroupManager.h`, `Matrix.h`, `Vector.h`, `AABBox.h`, `UISiegeWarfareNew.h`, `Statistics_Internal.h`, `UIManager.h` (`_SFunc`), `Util.h` (`LOG_DEBUG`), `GameMP_2010.vcxproj` (`$(IntDir)`) และแปลงสตริง `L"..."` ใน `Nksp.cpp` / `UIOption.cpp` เป็น `\uXXXX` ไม่ให้เพี้ยนบนเครื่อง Windows ภาษาอังกฤษของ GitHub

---

## 🖥️ ส่วนที่ 3: วิธีเปิดเซิร์ฟเวอร์ Last Chaos ภาษาไทยบน Windows (`ServerRelease`)

### โครงสร้างโฟลเดอร์ทั้งหมดในชุดไฟล์
```text
├── .github/workflows/build-lastchaos-thai.yml   # ไฟล์สั่งคอมไพล์อัตโนมัติบนเว็บ GitHub (GitHub Actions)
├── Push_To_GitHub_อัปขึ้นเว็บอัตโนมัติ.bat          # สคริปต์คลิกเดียวอัปโหลดขึ้นเว็บ GitHub
├── Build_Local_VisualStudio_TH.bat              # สคริปต์คอมไพล์บนเครื่องตัวเอง (ถ้ามี VS 2022)
├── ServerRelease/                               # ไฟล์เซิร์ฟเวอร์จริง (.exe ครบทั้ง 7 เซอร์วิส + แผนที่ 43 โซน)
│   ├── Connector/Connector.exe
│   ├── Helper/Helper.exe
│   ├── SubHelper/SubHelper.exe
│   ├── Messenger/Messenger.exe
│   ├── Login/LoginServer.exe
│   ├── Cash/CashServer.exe
│   ├── Gameserver/GameServer.exe
│   ├── Start_Thai_Server.bat                    # สคริปต์เปิดเซิร์ฟไทยครบทั้ง 7 เซอร์วิสตามลำดับ
│   └── Stop_Thai_Server.bat                     # สคริปต์ปิดเซิร์ฟอย่างปลอดภัย
├── Database_SQL/                                # ไฟล์ฐานข้อมูล MySQL / MariaDB (UTF-8 ภาษาไทย + ไอดีทดสอบ)
│   ├── 01_create_thai_databases.sql
│   └── 02_thai_sample_accounts_and_notices.sql
├── Client_Patch_TH/                             # แพตช์ภาษาไทยฝั่งผู้เล่น (sl.dta, strClient_th.lod, local_th.ini)
├── ClientSource/                                # ซอร์สโค้ดตัวเกมจริง (Serious Engine + Nksp แปลงรองรับ GitHub Actions แล้ว)
└── Tools_Windows_EXE/                           # เครื่องมือ .exe พร้อมซอร์สโค้ด C++
    ├── LastChaosServerManagerTH.exe             # โปรแกรม GUI จัดการเซิร์ฟเวอร์ภาษาไทย
    ├── LastChaosThai.exe                        # Launcher เข้าเกมภาษาไทย
    ├── LastChaosSLDtaToolTH.exe                 # เครื่องมือเข้ารหัส/ถอดรหัส sl.dta (IP เซิร์ฟ)
    └── LastChaosLodThaiTool.exe                 # เครื่องมือแปลงไฟล์ข้อความไทย strClient_th.lod (TIS-620/CP874)
```

### ขั้นตอนเปิดเซิร์ฟเวอร์บน Windows (3 ขั้นตอน)
1. **ติดตั้งฐานข้อมูล MySQL 5.7 / 8.0 หรือ MariaDB 10.x (XAMPP / Laragon ก็ใช้ได้)**
   - รันไฟล์ `Database_SQL/01_create_thai_databases.sql` และ `Database_SQL/02_thai_sample_accounts_and_notices.sql`
   - ค่าเริ่มต้นฐานข้อมูลใน `newStobm.bin` ตั้งไว้ที่ `127.0.0.1` (User: `root` / รหัสว่าง — สามารถเปิดแก้ผ่าน **`Tools_Windows_EXE/LastChaosServerManagerTH.exe`** ได้เลย!)
   - ไอดีทดสอบที่สร้างมาให้พร้อมแล้ว:
     - **ไอดีแอดมิน GM**: `admin` / รหัสผ่าน: `1234`
     - **ไอดีผู้เล่นทั่วไป**: `player1` / รหัสผ่าน: `1234`
2. **รันเซิร์ฟเวอร์**
   - เปิดโปรแกรม **`Tools_Windows_EXE/LastChaosServerManagerTH.exe`** แล้วกดปุ่ม **"เปิดเซิร์ฟทั้งหมด"** หรือดับเบิลคลิก **`ServerRelease/Start_Thai_Server.bat`**
   - เซอร์วิสทั้ง 7 ตัวจะรันตามลำดับ: `Connector` -> `Helper` -> `SubHelper` -> `Messenger` -> `CashServer` -> `LoginServer` (พอร์ต `4001`) -> `GameServer` (พอร์ต `4101`)
   - *(แก้บั๊กไฟล์ `.shutdown` ค้างใน `Gameserver/` และปลดบล็อกช่วง IP ประเทศไทยใน `Login/newStobm.bin` ให้เรียบร้อยแล้ว)*
3. **นำไฟล์ Client ที่คอมไพล์จาก GitHub Actions ไปเข้าเล่น**
   - แตกไฟล์ **`LastChaos-Thai-Client-Binaries-Win32.zip`** ที่ดาวน์โหลดจากแท็บ **Actions** บนเว็บ GitHub ไปวางทับในโฟลเดอร์ตัวเกม Last Chaos Episode 4 (ที่มีไฟล์ Data `.tex` / `.smc` / `.lod` ของเกม)
   - ดับเบิลคลิก **`LastChaosThai.exe`** (หรือ `Bin\Nksp.exe`) เพื่อเข้าสู่เซิร์ฟเวอร์ภาษาไทยได้เลย!
