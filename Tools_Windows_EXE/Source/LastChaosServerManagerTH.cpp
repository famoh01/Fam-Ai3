// LastChaosServerManagerTH.cpp
// Native Win32 Unicode Thai GUI Control Panel for OllyBaru Last Chaos EP4 ServerRelease
// Cross-compiles cleanly with: i686-w64-mingw32-g++ -O2 -static -municode -mwindows

#define UNICODE
#define _UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <shellapi.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <string>
#include <vector>

enum {
    ID_EDT_SRV_IP = 101,
    ID_EDT_DB_IP  = 102,
    ID_EDT_DB_USR = 103,
    ID_EDT_DB_PWD = 104,
    ID_EDT_EXP    = 105,
    ID_BTN_SAVE   = 201,
    ID_BTN_START  = 202,
    ID_BTN_SAFE   = 203,
    ID_BTN_KILL   = 204,
    ID_TIMER_PROC = 301
};

static HFONT g_hFontTitle = NULL;
static HFONT g_hFontUI    = NULL;
static HFONT g_hFontBold  = NULL;
static HWND  g_hEdtSrvIP  = NULL;
static HWND  g_hEdtDbIP   = NULL;
static HWND  g_hEdtDbUsr  = NULL;
static HWND  g_hEdtDbPwd  = NULL;
static HWND  g_hEdtExp    = NULL;
static HWND  g_hLblStatus[7] = {};
static HWND  g_hLblFooter = NULL;
static std::wstring g_baseDir;

struct SvcDef {
    const wchar_t* folder;
    const wchar_t* exeName;
    const wchar_t* labelTH;
};

static const SvcDef kServices[7] = {
    { L"Messenger",  L"Messenger.exe",       L"1. Messenger.exe (ระบบแชท/เพื่อน - Port 4112)" },
    { L"Helper",     L"Helper.exe",          L"2. Helper.exe (จัดการกิลด์/ปาร์ตี้ - Port 3000)" },
    { L"SubHelper",  L"SubHelper.exe",       L"3. SubHelper.exe (ไปรษณีย์/จัดอันดับ - Port 50401)" },
    { L"Billing",    L"ReZasCashServer.exe", L"4. ReZasCashServer.exe (ไอเทมมอลล์ Cash - Port 8888)" },
    { L"Connector",  L"Connector.exe",       L"5. Connector.exe (ตัวเชื่อมแชนแนล - Port 4006)" },
    { L"Login",      L"LoginServer.exe",     L"6. LoginServer.exe (เซิร์ฟเวอร์ล็อกอิน - Port 4001)" },
    { L"Gameserver", L"GameServer.exe",      L"7. GameServer.exe (เซิร์ฟเวอร์หลัก 43 แผนที่ - Port 4101)" }
};

static std::string wstr_to_utf8(const std::wstring& w) {
    if (w.empty()) return "";
    int n = WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), NULL, 0, NULL, NULL);
    std::string s(n, 0);
    WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), &s[0], n, NULL, NULL);
    return s;
}

static std::wstring utf8_to_wstr(const std::string& s) {
    if (s.empty()) return L"";
    int n = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), NULL, 0);
    std::wstring w(n, 0);
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), &w[0], n);
    return w;
}

static std::wstring get_window_text_w(HWND h) {
    wchar_t buf[256] = {};
    GetWindowTextW(h, buf, 255);
    return std::wstring(buf);
}

static bool write_sldta_file(const std::wstring& outPath, const std::string& name, const std::string& ip, const std::string& port) {
    FILE* fp = _wfopen(outPath.c_str(), L"wb");
    if (!fp) return false;
    const uint8_t hdr[6] = {'L', 'C', 'T', 'H', 'A', 'I'};
    fwrite(hdr, 1, 6, fp);
    int32_t iKey = 0x13572468;
    uint8_t key = 0x5A;
    fwrite(&iKey, sizeof(int32_t), 1, fp);
    fwrite(&key, 1, 1, fp);

    int32_t serverNum = 1;
    int32_t encServerNum = serverNum + iKey;
    fwrite(&encServerNum, sizeof(int32_t), 1, fp);
    iKey = encServerNum;

    char buf[256];
    snprintf(buf, sizeof(buf), "%s %s %s 200 150", name.c_str(), ip.c_str(), port.c_str());
    int32_t count = (int32_t)strlen(buf);
    int32_t encCount = count + iKey;
    fwrite(&encCount, sizeof(int32_t), 1, fp);
    for (int32_t idx = 0; idx < count; ++idx) {
        uint8_t data = (uint8_t)(((uint8_t)buf[idx] + key) & 0xFF);
        fwrite(&data, 1, 1, fp);
        key = data;
    }
    fclose(fp);
    return true;
}

static bool is_process_running(const wchar_t* exeName) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(pe);
    bool found = false;
    if (Process32FirstW(snap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, exeName) == 0) {
                found = true;
                break;
            }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
    return found;
}

static void kill_process_by_name(const wchar_t* exeName) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return;
    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(pe);
    if (Process32FirstW(snap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, exeName) == 0) {
                HANDLE hp = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                if (hp) {
                    TerminateProcess(hp, 0);
                    CloseHandle(hp);
                }
            }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
}

static void refresh_process_statuses() {
    int onlineCount = 0;
    for (int i = 0; i < 7; ++i) {
        bool up = is_process_running(kServices[i].exeName);
        if (up) onlineCount++;
        std::wstring txt = std::wstring(kServices[i].labelTH) + (up ? L"   [ออนไลน์ - กำลังทำงาน]" : L"   [ออฟไลน์]");
        SetWindowTextW(g_hLblStatus[i], txt.c_str());
    }
    wchar_t summary[256];
    swprintf(summary, 256, L"สถานะระบบ: เปิดทำงานอยู่ %d / 7 เซอร์วิส | โฟลเดอร์: %s", onlineCount, g_baseDir.c_str());
    SetWindowTextW(g_hLblFooter, summary);
}

static void load_current_config() {
    std::wstring gsIni = g_baseDir + L"Gameserver\\newStobm.bin";
    wchar_t srvIP[128] = L"127.0.0.1";
    wchar_t dbIP[128]  = L"127.0.0.1";
    wchar_t dbUsr[128] = L"test";
    wchar_t dbPwd[128] = L"123";
    wchar_t expM[64]   = L"30";

    GetPrivateProfileStringW(L"Server", L"IP", L"127.0.0.1", srvIP, 127, gsIni.c_str());
    GetPrivateProfileStringW(L"Data DB", L"IP", L"127.0.0.1", dbIP, 127, gsIni.c_str());
    GetPrivateProfileStringW(L"Data DB", L"User", L"test", dbUsr, 127, gsIni.c_str());
    GetPrivateProfileStringW(L"Data DB", L"Password", L"123", dbPwd, 127, gsIni.c_str());
    GetPrivateProfileStringW(L"Rates", L"P2Multiplier", L"30", expM, 63, gsIni.c_str());

    SetWindowTextW(g_hEdtSrvIP, srvIP);
    SetWindowTextW(g_hEdtDbIP, dbIP);
    SetWindowTextW(g_hEdtDbUsr, dbUsr);
    SetWindowTextW(g_hEdtDbPwd, dbPwd);
    SetWindowTextW(g_hEdtExp, expM);
}

static void save_all_configs(HWND hwnd) {
    std::wstring wSrvIP = get_window_text_w(g_hEdtSrvIP);
    std::wstring wDbIP  = get_window_text_w(g_hEdtDbIP);
    std::wstring wDbUsr = get_window_text_w(g_hEdtDbUsr);
    std::wstring wDbPwd = get_window_text_w(g_hEdtDbPwd);
    std::wstring wExp   = get_window_text_w(g_hEdtExp);

    // 1. Messenger/newStobm.bin
    std::wstring fMsg = g_baseDir + L"Messenger\\newStobm.bin";
    WritePrivateProfileStringW(L"Server", L"IP", wSrvIP.c_str(), fMsg.c_str());

    // 2. Helper/newStobm.bin
    std::wstring fHlp = g_baseDir + L"Helper\\newStobm.bin";
    WritePrivateProfileStringW(L"Server", L"IP", wSrvIP.c_str(), fHlp.c_str());
    WritePrivateProfileStringW(L"Char DB", L"IP", wDbIP.c_str(), fHlp.c_str());
    WritePrivateProfileStringW(L"Char DB", L"User", wDbUsr.c_str(), fHlp.c_str());
    WritePrivateProfileStringW(L"Char DB", L"Password", wDbPwd.c_str(), fHlp.c_str());

    // 3. SubHelper/newStobm.bin
    std::wstring fSub = g_baseDir + L"SubHelper\\newStobm.bin";
    WritePrivateProfileStringW(L"Server", L"IP", wSrvIP.c_str(), fSub.c_str());
    WritePrivateProfileStringW(L"Messenger Server", L"IP", wSrvIP.c_str(), fSub.c_str());
    const wchar_t* subDbs[3] = { L"Data DB", L"Char DB", L"Post DB" };
    for (int i = 0; i < 3; ++i) {
        WritePrivateProfileStringW(subDbs[i], L"IP", wDbIP.c_str(), fSub.c_str());
        WritePrivateProfileStringW(subDbs[i], L"User", wDbUsr.c_str(), fSub.c_str());
        WritePrivateProfileStringW(subDbs[i], L"Password", wDbPwd.c_str(), fSub.c_str());
    }

    // 4. Connector/newStobm.bin
    std::wstring fCon = g_baseDir + L"Connector\\newStobm.bin";
    WritePrivateProfileStringW(L"Server", L"IP", wSrvIP.c_str(), fCon.c_str());
    WritePrivateProfileStringW(L"GameServer", L"EX_IP_1", wSrvIP.c_str(), fCon.c_str());
    WritePrivateProfileStringW(L"GameServer", L"EX_IP_2", wSrvIP.c_str(), fCon.c_str());
    WritePrivateProfileStringW(L"GameServer", L"EX_IP_3", wSrvIP.c_str(), fCon.c_str());
    WritePrivateProfileStringW(L"Billing Server", L"IP", wSrvIP.c_str(), fCon.c_str());
    const wchar_t* conDbs[3] = { L"User DB", L"Auth DB", L"Event DB" };
    for (int i = 0; i < 3; ++i) {
        WritePrivateProfileStringW(conDbs[i], L"IP", wDbIP.c_str(), fCon.c_str());
        WritePrivateProfileStringW(conDbs[i], L"User", wDbUsr.c_str(), fCon.c_str());
        WritePrivateProfileStringW(conDbs[i], L"Password", wDbPwd.c_str(), fCon.c_str());
    }

    // 5. Login/newStobm.bin
    std::wstring fLgn = g_baseDir + L"Login\\newStobm.bin";
    WritePrivateProfileStringW(L"Server", L"IP", wSrvIP.c_str(), fLgn.c_str());
    WritePrivateProfileStringW(L"Messenger Server", L"IP", wSrvIP.c_str(), fLgn.c_str());
    WritePrivateProfileStringW(L"Connector_0", L"IP", wSrvIP.c_str(), fLgn.c_str());
    WritePrivateProfileStringW(L"Block Band", L"Number", L"0", fLgn.c_str());
    const wchar_t* lgnDbs[3] = { L"User DB", L"Data DB", L"Auth DB" };
    for (int i = 0; i < 3; ++i) {
        WritePrivateProfileStringW(lgnDbs[i], L"IP", wDbIP.c_str(), fLgn.c_str());
        WritePrivateProfileStringW(lgnDbs[i], L"User", wDbUsr.c_str(), fLgn.c_str());
        WritePrivateProfileStringW(lgnDbs[i], L"Password", wDbPwd.c_str(), fLgn.c_str());
    }

    // 6. Gameserver/newStobm.bin
    std::wstring fGs = g_baseDir + L"Gameserver\\newStobm.bin";
    WritePrivateProfileStringW(L"Server", L"IP", wSrvIP.c_str(), fGs.c_str());
    WritePrivateProfileStringW(L"Rates", L"P2Multiplier", wExp.c_str(), fGs.c_str());
    WritePrivateProfileStringW(L"Connector Server", L"IP", wSrvIP.c_str(), fGs.c_str());
    WritePrivateProfileStringW(L"Messenger Server", L"IP", wSrvIP.c_str(), fGs.c_str());
    WritePrivateProfileStringW(L"Helper Server", L"IP", wSrvIP.c_str(), fGs.c_str());
    WritePrivateProfileStringW(L"SubHelper Server", L"IP", wSrvIP.c_str(), fGs.c_str());
    WritePrivateProfileStringW(L"User Server", L"IP", wSrvIP.c_str(), fGs.c_str());
    const wchar_t* gsDbs[4] = { L"Data DB", L"Char DB", L"Catalog DB", L"Post DB" };
    for (int i = 0; i < 4; ++i) {
        WritePrivateProfileStringW(gsDbs[i], L"IP", wDbIP.c_str(), fGs.c_str());
        WritePrivateProfileStringW(gsDbs[i], L"User", wDbUsr.c_str(), fGs.c_str());
        WritePrivateProfileStringW(gsDbs[i], L"Password", wDbPwd.c_str(), fGs.c_str());
    }

    // 7. Billing/Config.RAWR
    std::wstring fRawr = g_baseDir + L"Billing\\Config.RAWR";
    WritePrivateProfileStringW(L"Database", L"Address", wDbIP.c_str(), fRawr.c_str());
    WritePrivateProfileStringW(L"Database", L"UserName", wDbUsr.c_str(), fRawr.c_str());
    WritePrivateProfileStringW(L"Database", L"Password", wDbPwd.c_str(), fRawr.c_str());
    WritePrivateProfileStringW(L"Server", L"IP", wSrvIP.c_str(), fRawr.c_str());

    // 8. Also update ..\Client_Patch_TH\Bin\sl.dta automatically!
    std::wstring slPath = g_baseDir + L"..\\Client_Patch_TH\\Bin\\sl.dta";
    bool slOk = write_sldta_file(slPath, "LastChaos_TH", wstr_to_utf8(wSrvIP), "4001");

    std::wstring msg = L"บันทึกการตั้งค่าเรียบร้อยแล้ว!\n\n"
                       L"- อัปเดตไฟล์ newStobm.bin ทั้ง 6 เซอร์วิส และ Billing\\Config.RAWR สำเร็จ\n"
                       L"- Server IP: " + wSrvIP + L" | EXP x" + wExp + L"\n";
    if (slOk) {
        msg += L"- อัปเดตไฟล์ไคลเอนต์ Client_Patch_TH\\Bin\\sl.dta ให้ตรงกับ IP นี้แล้ว!";
    }
    MessageBoxW(hwnd, msg.c_str(), L"บันทึกสำเร็จ (Last Chaos Thai Server)", MB_OK | MB_ICONINFORMATION);
}

static void start_all_services(HWND hwnd) {
    // Ensure .shutdown trigger file is removed before starting GameServer.exe!
    std::wstring shutdownFile = g_baseDir + L"Gameserver\\.shutdown";
    DeleteFileW(shutdownFile.c_str());

    for (int i = 0; i < 7; ++i) {
        if (!is_process_running(kServices[i].exeName)) {
            std::wstring dir = g_baseDir + kServices[i].folder;
            std::wstring exe = dir + L"\\" + kServices[i].exeName;
            ShellExecuteW(hwnd, L"open", exe.c_str(), NULL, dir.c_str(), SW_SHOWNORMAL);
            Sleep(450);
        }
    }
    refresh_process_statuses();
}

static void graceful_shutdown_services(HWND hwnd) {
    std::wstring shutdownFile = g_baseDir + L"Gameserver\\.shutdown";
    FILE* fp = _wfopen(shutdownFile.c_str(), L"wb");
    if (fp) fclose(fp);
    MessageBoxW(hwnd,
        L"ส่งคำสั่งบันทึกข้อมูลและปิด GameServer อย่างปลอดภัย (.shutdown) แล้ว!\n"
        L"หากต้องการปิดเซอร์วิสย่อยทั้งหมดทันที สามารถกดปุ่ม 'บังคับปิดทันที' ต่อได้",
        L"สั่งปิดเซิร์ฟเวอร์อย่างปลอดภัย", MB_OK | MB_ICONINFORMATION);
    refresh_process_statuses();
}

static void force_kill_services() {
    for (int i = 6; i >= 0; --i) {
        kill_process_by_name(kServices[i].exeName);
    }
    std::wstring shutdownFile = g_baseDir + L"Gameserver\\.shutdown";
    DeleteFileW(shutdownFile.c_str());
    refresh_process_statuses();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        g_hFontTitle = CreateFontW(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, THAI_CHARSET,
                                   OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Tahoma");
        g_hFontUI    = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, THAI_CHARSET,
                                   OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Tahoma");
        g_hFontBold  = CreateFontW(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, THAI_CHARSET,
                                   OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Tahoma");

        HWND hTitle = CreateWindowExW(0, L"STATIC", L"โปรแกรมจัดการเซิร์ฟเวอร์ Last Chaos ภาษาไทย (EP4 Control Panel)",
                                      WS_CHILD | WS_VISIBLE, 20, 14, 640, 28, hwnd, NULL, NULL, NULL);
        SendMessageW(hTitle, WM_SETFONT, (WPARAM)g_hFontTitle, TRUE);

        // Config Group
        HWND hGrpCfg = CreateWindowExW(0, L"BUTTON", L" ตั้งค่าเครือข่าย ฐานข้อมูล MySQL และอัตราคูณ (newStobm.bin + sl.dta) ",
                                       WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 18, 50, 645, 138, hwnd, NULL, NULL, NULL);
        SendMessageW(hGrpCfg, WM_SETFONT, (WPARAM)g_hFontBold, TRUE);

        auto addLabel = [&](const wchar_t* text, int x, int y, int w) {
            HWND h = CreateWindowExW(0, L"STATIC", text, WS_CHILD | WS_VISIBLE, x, y, w, 22, hwnd, NULL, NULL, NULL);
            SendMessageW(h, WM_SETFONT, (WPARAM)g_hFontUI, TRUE);
            return h;
        };
        auto addEdit = [&](int id, int x, int y, int w) {
            HWND h = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                                     x, y, w, 24, hwnd, (HMENU)(INT_PTR)id, NULL, NULL);
            SendMessageW(h, WM_SETFONT, (WPARAM)g_hFontUI, TRUE);
            return h;
        };

        addLabel(L"Server IP (เครื่อง/VPS):", 34, 80, 145);
        g_hEdtSrvIP = addEdit(ID_EDT_SRV_IP, 180, 78, 145);

        addLabel(L"MySQL Host IP:", 345, 80, 110);
        g_hEdtDbIP = addEdit(ID_EDT_DB_IP, 460, 78, 180);

        addLabel(L"MySQL User:", 34, 114, 145);
        g_hEdtDbUsr = addEdit(ID_EDT_DB_USR, 180, 112, 145);

        addLabel(L"MySQL Password:", 345, 114, 115);
        g_hEdtDbPwd = addEdit(ID_EDT_DB_PWD, 460, 112, 180);

        addLabel(L"อัตราคูณ EXP (x):", 34, 148, 145);
        g_hEdtExp = addEdit(ID_EDT_EXP, 180, 146, 80);

        HWND hBtnSave = CreateWindowExW(0, L"BUTTON", L"บันทึกค่า IP / MySQL / EXP ทั้งเซิร์ฟเวอร์ + สร้าง sl.dta",
                                        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 280, 144, 360, 30,
                                        hwnd, (HMENU)ID_BTN_SAVE, NULL, NULL);
        SendMessageW(hBtnSave, WM_SETFONT, (WPARAM)g_hFontBold, TRUE);

        // Services Group
        HWND hGrpSvc = CreateWindowExW(0, L"BUTTON", L" สถานะการทำงานของเซอร์วิสทั้ง 7 ตัว (Real-Time Monitor) ",
                                       WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 18, 198, 645, 222, hwnd, NULL, NULL, NULL);
        SendMessageW(hGrpSvc, WM_SETFONT, (WPARAM)g_hFontBold, TRUE);

        for (int i = 0; i < 7; ++i) {
            g_hLblStatus[i] = CreateWindowExW(0, L"STATIC", kServices[i].labelTH, WS_CHILD | WS_VISIBLE,
                                              36, 224 + i * 26, 610, 22, hwnd, NULL, NULL, NULL);
            SendMessageW(g_hLblStatus[i], WM_SETFONT, (WPARAM)g_hFontUI, TRUE);
        }

        // Control Buttons
        HWND hBtnStart = CreateWindowExW(0, L"BUTTON", L"เปิดเซิร์ฟเวอร์ทั้งหมด (7 Services)",
                                         WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 18, 432, 225, 38,
                                         hwnd, (HMENU)ID_BTN_START, NULL, NULL);
        HWND hBtnSafe  = CreateWindowExW(0, L"BUTTON", L"ปิดแบบปลอดภัย (Save & Shutdown)",
                                         WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 253, 432, 215, 38,
                                         hwnd, (HMENU)ID_BTN_SAFE, NULL, NULL);
        HWND hBtnKill  = CreateWindowExW(0, L"BUTTON", L"บังคับปิดทันที (Force Stop)",
                                         WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 478, 432, 185, 38,
                                         hwnd, (HMENU)ID_BTN_KILL, NULL, NULL);
        SendMessageW(hBtnStart, WM_SETFONT, (WPARAM)g_hFontBold, TRUE);
        SendMessageW(hBtnSafe,  WM_SETFONT, (WPARAM)g_hFontUI, TRUE);
        SendMessageW(hBtnKill,  WM_SETFONT, (WPARAM)g_hFontUI, TRUE);

        g_hLblFooter = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE, 20, 482, 640, 22, hwnd, NULL, NULL, NULL);
        SendMessageW(g_hLblFooter, WM_SETFONT, (WPARAM)g_hFontUI, TRUE);

        load_current_config();
        refresh_process_statuses();
        SetTimer(hwnd, ID_TIMER_PROC, 1500, NULL);
        return 0;
    }
    case WM_TIMER:
        if (wParam == ID_TIMER_PROC) refresh_process_statuses();
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BTN_SAVE:  save_all_configs(hwnd); break;
        case ID_BTN_START: start_all_services(hwnd); break;
        case ID_BTN_SAFE:  graceful_shutdown_services(hwnd); break;
        case ID_BTN_KILL:  force_kill_services(); break;
        }
        return 0;
    case WM_DESTROY:
        KillTimer(hwnd, ID_TIMER_PROC);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int nShow) {
    wchar_t exePath[MAX_PATH] = {};
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    std::wstring p(exePath);
    size_t pos = p.find_last_of(L"\\/");
    g_baseDir = (pos != std::wstring::npos) ? p.substr(0, pos + 1) : L".\\";

    WNDCLASSEXW wc = {};
    wc.cbSize        = sizeof(wc);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = L"LCThaiServerMgrWnd";
    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(0, wc.lpszClassName,
        L"Last Chaos Thailand - โปรแกรมจัดการเซิร์ฟเวอร์ภาษาไทย (EP4 Server Manager)",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 690, 548, NULL, NULL, hInst, NULL);

    ShowWindow(hwnd, nShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        if (!IsDialogMessageW(hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    return 0;
}
