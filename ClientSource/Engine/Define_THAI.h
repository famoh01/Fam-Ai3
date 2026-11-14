// Define_THAI.h - Thai Localization Profile (เซิร์ฟเวอร์ภาษาไทย)
#define LINE_CHANGE_BY_WORD
#define MULTI_CLIENT
#define NO_GAMEGUARD
// Disable legacy XTrap / GameGuard for Windows 10/11 Private Server
#ifdef XTRAP_SECURE_CKBANG_2010_07_20
#undef XTRAP_SECURE_CKBANG_2010_07_20
#endif
