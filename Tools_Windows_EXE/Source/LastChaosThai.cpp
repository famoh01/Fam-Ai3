// LastChaosThai.cpp
// Official Thai Launcher executable name ("LastChaosThai.exe" per Nksp.cpp:1619)
// Native Win32 Unicode Thai GUI Launcher + sl.dta Encryptor + TCP Ping + Nksp.exe Launcher
// Cross-compiles cleanly with: i686-w64-mingw32-g++ -O2 -static -municode -mwindows LastChaosThai.cpp -lws2_32

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <shellapi.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <string>

enum {
    ID_EDT_IP     = 101,
    ID_EDT_PORT   = 102,
    ID_EDT_USER   = 103,
    ID_EDT_PASS   = 104,
    ID_CHK_WIN    = 105,
    ID_BTN_PING   = 201,
    ID_BTN_SAVEIP = 202,
    ID_BTN_PLAY   = 203
};

static HFONT g_fntBanner = NULL;
static HFONT g_fntSub    = NULL;
static HFONT g_fntUI     = NULL;
static HFONT g_fntPlay   = NULL;
static HWND  g_hEdtIP    = NULL;
static HWND  g_hEdtPort  = NULL;
static HWND  g_hEdtUser  = NULL;
static HWND  g_hEdtPass  = NULL;
static HWND  g_hChkWin   = NULL;
static HWND  g_hLblPing  = NULL;
static std::wstring g_appDir;

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

static std::wstring get_text(HWND h) {
    wchar_t b[256] = {};
    GetWindowTextW(h, b, 255);
    return std::wstring(b);
}

static bool read_sldta(const std::wstring& path, std::string& outIP, std::string& outPort) {
    FILE* fp = _wfopen(path.c_str(), L"rb");
    if (!fp) return false;
    uint8_t key = 0;
    for (int i = 0; i < 6; ++i) {
        if (fread(&key, 1, 1, fp) != 1) { fclose(fp); return false; }
    }
    int32_t iKey = 0, iKeyTemp = 0, serverNum = 0;
    if (fread(&iKey, sizeof(int32_t), 1, fp) != 1 ||
        fread(&key, 1, 1, fp) != 1 ||
        fread(&serverNum, sizeof(int32_t), 1, fp) != 1) {
        fclose(fp);
        return false;
    }
    iKeyTemp = serverNum;
    serverNum -= iKey;
    iKey = iKeyTemp;
    if (serverNum <= 0 || serverNum > 50) { fclose(fp); return false; }

    int32_t count = 0;
    if (fread(&count, sizeof(int32_t), 1, fp) != 1) { fclose(fp); return false; }
    count -= iKey;
    if (count <= 0 || count >= 255) { fclose(fp); return false; }

    char buf[256];
    for (int idx = 0; idx < count; ++idx) {
        uint8_t data = 0;
        if (fread(&data, 1, 1, fp) != 1) { fclose(fp); return false; }
        buf[idx] = (char)(data - key);
        key = data;
    }
    buf[count] = '\0';
    fclose(fp);

    char sName[64] = {}, sIP[64] = {}, sPort[32] = {};
    if (sscanf(buf, "%63s %63s %31s", sName, sIP, sPort) >= 3) {
        outIP = sIP;
        outPort = sPort;
        return true;
    }
    return false;
}

static bool write_sldta(const std::wstring& path, const std::string& ip, const std::string& port) {
    CreateDirectoryW((g_appDir + L"Bin").c_str(), NULL);
    FILE* fp = _wfopen(path.c_str(), L"wb");
    if (!fp) return false;
    const uint8_t hdr[6] = {'L', 'C', 'T', 'H', 'A', 'I'};
    fwrite(hdr, 1, 6, fp);
    int32_t iKey = 0x13572468;
    uint8_t key = 0x5A;
    fwrite(&iKey, sizeof(int32_t), 1, fp);
    fwrite(&key, 1, 1, fp);

    int32_t encNum = 1 + iKey;
    fwrite(&encNum, sizeof(int32_t), 1, fp);
    iKey = encNum;

    char buf[256];
    snprintf(buf, sizeof(buf), "LastChaos_TH %s %s 200 150", ip.c_str(), port.c_str());
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

static bool tcp_ping_port(const char* ip, int port, int timeoutMs) {
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) return false;

    u_long nonBlock = 1;
    ioctlsocket(s, FIONBIO, &nonBlock);

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)port);
    addr.sin_addr.s_addr = inet_addr(ip);
    if (addr.sin_addr.s_addr == INADDR_NONE) {
        closesocket(s);
        return false;
    }

    connect(s, (sockaddr*)&addr, sizeof(addr));
    fd_set wfds;
    FD_ZERO(&wfds);
    FD_SET(s, &wfds);
    timeval tv;
    tv.tv_sec = timeoutMs / 1000;
    tv.tv_usec = (timeoutMs % 1000) * 1000;

    bool ok = false;
    if (select(0, NULL, &wfds, NULL, &tv) > 0) {
        int soErr = -1;
        int len = sizeof(soErr);
        getsockopt(s, SOL_SOCKET, SO_ERROR, (char*)&soErr, &len);
        ok = (soErr == 0);
    }
    closesocket(s);
    return ok;
}

static void check_server_online() {
    std::string ip = wstr_to_utf8(get_text(g_hEdtIP));
    int loginPort = atoi(wstr_to_utf8(get_text(g_hEdtPort)).c_str());
    if (loginPort <= 0) loginPort = 4001;

    bool loginUp = tcp_ping_port(ip.c_str(), loginPort, 700);
    bool gameUp  = tcp_ping_port(ip.c_str(), 4101, 700);

    std::wstring status;
    if (loginUp && gameUp) {
        status = L"สถานะเซิร์ฟเวอร์: [ออนไลน์ครบทุกส่วน - พร้อมเข้าเล่น!] (Login:4001 OK / Game:4101 OK)";
    } else if (loginUp) {
        status = L"สถานะเซิร์ฟเวอร์: [Login ออนไลน์ / กำลังโหลดแผนที่ GameServer...]";
    } else {
        status = L"สถานะเซิร์ฟเวอร์: [ออฟไลน์] (ยังไม่พบการเปิดพอร์ต " + utf8_to_wstr(ip) + L":" + get_text(g_hEdtPort) + L")";
    }
    SetWindowTextW(g_hLblPing, status.c_str());
}

static void launch_game(HWND hwnd) {
    std::string ip = wstr_to_utf8(get_text(g_hEdtIP));
    std::string port = wstr_to_utf8(get_text(g_hEdtPort));
    if (ip.empty()) ip = "127.0.0.1";
    if (port.empty()) port = "4001";

    // Always write updated Bin\sl.dta before launching
    write_sldta(g_appDir + L"Bin\\sl.dta", ip, port);

    // Write country/windowed config script for Serious Engine
    bool windowed = (SendMessageW(g_hChkWin, BM_GETCHECK, 0, 0) == BST_CHECKED);
    CreateDirectoryW((g_appDir + L"Scripts").c_str(), NULL);
    FILE* fCfg = _wfopen((g_appDir + L"Scripts\\ThaiClientConfig.cfg").c_str(), L"wb");
    if (fCfg) {
        fprintf(fCfg, "g_iCountry = 3;\r\nsam_bFullScreenActive = %d;\r\n", windowed ? 0 : 1);
        fclose(fCfg);
    }

    std::wstring nkspPath = g_appDir + L"Bin\\Nksp.exe";
    DWORD attr = GetFileAttributesW(nkspPath.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        MessageBoxW(hwnd,
            L"ยังไม่พบไฟล์ Bin\\Nksp.exe ในโฟลเดอร์เกม!\n\n"
            L"วิธีใช้งาน:\n"
            L"1. คอมไพล์โปรเจกต์ในโฟลเดอร์ ClientSource ด้วย Build_Client_TH.bat (โหมด THAILIVE | Win32) เพื่อให้ได้ Bin\\Nksp.exe และ Engine.dll\n"
            L"2. หรือคัดลอกไฟล์ Client_Patch_TH ทั้งหมดไปวางทับในโฟลเดอร์ตัวเกม Last Chaos EP4 ที่มี Bin\\Nksp.exe อยู่แล้ว",
            L"ไม่พบไฟล์ Bin\\Nksp.exe", MB_OK | MB_ICONWARNING);
        return;
    }

    std::wstring user = get_text(g_hEdtUser);
    std::wstring pass = get_text(g_hEdtPass);
    std::wstring args = L"fkzktlfgod!";
    if (!user.empty() && !pass.empty()) {
        args = L"700 th " + user + L" " + pass;
    }

    HINSTANCE res = ShellExecuteW(hwnd, L"open", nkspPath.c_str(), args.c_str(), g_appDir.c_str(), SW_SHOWNORMAL);
    if ((INT_PTR)res > 32) {
        PostQuitMessage(0);
    } else {
        MessageBoxW(hwnd, L"ไม่สามารถรัน Bin\\Nksp.exe ได้ กรุณาคลิกขวา Run as Administrator", L"ข้อผิดพลาด", MB_OK | MB_ICONERROR);
    }
}

LRESULT CALLBACK LauncherWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        g_fntBanner = CreateFontW(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, THAI_CHARSET,
                                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Tahoma");
        g_fntSub    = CreateFontW(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, THAI_CHARSET,
                                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Tahoma");
        g_fntUI     = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, THAI_CHARSET,
                                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Tahoma");
        g_fntPlay   = CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, THAI_CHARSET,
                                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Tahoma");

        HWND hBan = CreateWindowExW(0, L"STATIC", L"LAST CHAOS THAILAND (เซิร์ฟเวอร์ภาษาไทย EP4)",
                                    WS_CHILD | WS_VISIBLE, 22, 16, 540, 30, hwnd, NULL, NULL, NULL);
        SendMessageW(hBan, WM_SETFONT, (WPARAM)g_fntBanner, TRUE);

        g_hLblPing = CreateWindowExW(0, L"STATIC", L"สถานะเซิร์ฟเวอร์: กำลังตรวจสอบ...",
                                     WS_CHILD | WS_VISIBLE, 22, 52, 540, 24, hwnd, NULL, NULL, NULL);
        SendMessageW(g_hLblPing, WM_SETFONT, (WPARAM)g_fntSub, TRUE);

        // Server Box
        HWND hGrpSrv = CreateWindowExW(0, L"BUTTON", L" ตั้งค่าการเชื่อมต่อเซิร์ฟเวอร์ (Bin\\sl.dta) ",
                                       WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 84, 540, 86, hwnd, NULL, NULL, NULL);
        SendMessageW(hGrpSrv, WM_SETFONT, (WPARAM)g_fntSub, TRUE);

        auto addLbl = [&](const wchar_t* t, int x, int y, int w) {
            HWND h = CreateWindowExW(0, L"STATIC", t, WS_CHILD | WS_VISIBLE, x, y, w, 22, hwnd, NULL, NULL, NULL);
            SendMessageW(h, WM_SETFONT, (WPARAM)g_fntUI, TRUE);
        };
        addLbl(L"IP เซิร์ฟเวอร์:", 36, 118, 95);
        g_hEdtIP = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"127.0.0.1", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                                   132, 115, 145, 25, hwnd, (HMENU)ID_EDT_IP, NULL, NULL);
        SendMessageW(g_hEdtIP, WM_SETFONT, (WPARAM)g_fntUI, TRUE);

        addLbl(L"Port:", 290, 118, 40);
        g_hEdtPort = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"4001", WS_CHILD | WS_VISIBLE | ES_NUMBER,
                                     332, 115, 65, 25, hwnd, (HMENU)ID_EDT_PORT, NULL, NULL);
        SendMessageW(g_hEdtPort, WM_SETFONT, (WPARAM)g_fntUI, TRUE);

        HWND hBtnPing = CreateWindowExW(0, L"BUTTON", L"เช็คสถานะ", WS_CHILD | WS_VISIBLE,
                                        410, 114, 132, 27, hwnd, (HMENU)ID_BTN_PING, NULL, NULL);
        SendMessageW(hBtnPing, WM_SETFONT, (WPARAM)g_fntUI, TRUE);

        // Login & Display Box
        HWND hGrpLgn = CreateWindowExW(0, L"BUTTON", L" ล็อกอินด่วน (ไม่บังคับ) และโหมดหน้าจอ ",
                                       WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 180, 540, 108, hwnd, NULL, NULL, NULL);
        SendMessageW(hGrpLgn, WM_SETFONT, (WPARAM)g_fntSub, TRUE);

        addLbl(L"ไอดีผู้เล่น:", 36, 214, 90);
        g_hEdtUser = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                                     132, 211, 145, 25, hwnd, (HMENU)ID_EDT_USER, NULL, NULL);
        SendMessageW(g_hEdtUser, WM_SETFONT, (WPARAM)g_fntUI, TRUE);

        addLbl(L"รหัสผ่าน:", 290, 214, 65);
        g_hEdtPass = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_PASSWORD | ES_AUTOHSCROLL,
                                     358, 211, 184, 25, hwnd, (HMENU)ID_EDT_PASS, NULL, NULL);
        SendMessageW(g_hEdtPass, WM_SETFONT, (WPARAM)g_fntUI, TRUE);

        g_hChkWin = CreateWindowExW(0, L"BUTTON", L"เปิดเกมแบบหน้าต่าง (Windowed Mode - แนะนำสำหรับ Windows 10/11)",
                                    WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 36, 250, 500, 24,
                                    hwnd, (HMENU)ID_CHK_WIN, NULL, NULL);
        SendMessageW(g_hChkWin, WM_SETFONT, (WPARAM)g_fntUI, TRUE);
        SendMessageW(g_hChkWin, BM_SETCHECK, BST_CHECKED, 0);

        HWND hBtnSave = CreateWindowExW(0, L"BUTTON", L"บันทึกไฟล์ sl.dta",
                                        WS_CHILD | WS_VISIBLE, 20, 304, 165, 48, hwnd, (HMENU)ID_BTN_SAVEIP, NULL, NULL);
        SendMessageW(hBtnSave, WM_SETFONT, (WPARAM)g_fntSub, TRUE);

        HWND hBtnPlay = CreateWindowExW(0, L"BUTTON", L"เริ่มเกม Last Chaos (ภาษาไทย)",
                                        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 198, 304, 362, 48,
                                        hwnd, (HMENU)ID_BTN_PLAY, NULL, NULL);
        SendMessageW(hBtnPlay, WM_SETFONT, (WPARAM)g_fntPlay, TRUE);

        std::string curIP, curPort;
        if (read_sldta(g_appDir + L"Bin\\sl.dta", curIP, curPort)) {
            SetWindowTextW(g_hEdtIP, utf8_to_wstr(curIP).c_str());
            SetWindowTextW(g_hEdtPort, utf8_to_wstr(curPort).c_str());
        }
        check_server_online();
        return 0;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BTN_PING:
            check_server_online();
            break;
        case ID_BTN_SAVEIP: {
            std::string ip = wstr_to_utf8(get_text(g_hEdtIP));
            std::string port = wstr_to_utf8(get_text(g_hEdtPort));
            if (write_sldta(g_appDir + L"Bin\\sl.dta", ip, port)) {
                MessageBoxW(hwnd, L"เข้ารหัสและบันทึกไฟล์ Bin\\sl.dta สำเร็จแล้ว!", L"สำเร็จ", MB_OK | MB_ICONINFORMATION);
                check_server_online();
            }
            break;
        }
        case ID_BTN_PLAY:
            launch_game(hwnd);
            break;
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int nShow) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    wchar_t exePath[MAX_PATH] = {};
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    std::wstring p(exePath);
    size_t pos = p.find_last_of(L"\\/");
    g_appDir = (pos != std::wstring::npos) ? p.substr(0, pos + 1) : L".\\";

    WNDCLASSEXW wc = {};
    wc.cbSize        = sizeof(wc);
    wc.lpfnWndProc   = LauncherWndProc;
    wc.hInstance     = hInst;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = L"LastChaosThaiLauncherWnd";
    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(0, wc.lpszClassName,
        L"Last Chaos Thailand - ตัวเข้าเกมเซิร์ฟเวอร์ภาษาไทย (LastChaosThai.exe)",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 588, 405, NULL, NULL, hInst, NULL);

    ShowWindow(hwnd, nShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        if (!IsDialogMessageW(hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    WSACleanup();
    return 0;
}
