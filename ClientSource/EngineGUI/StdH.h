
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <commdlg.h>

#define ENGINE_INTERNAL 1
#define ENGINEGUI_EXPORTS 1

#if		!defined(WORLD_EDITOR)
#pragma push_macro("O")
#pragma push_macro("Q")
#pragma push_macro("D")
#pragma push_macro("W")
#pragma push_macro("B")
#undef O
#undef Q
#undef D
#undef W
#undef B
#include <boost/bind.hpp>
#include <boost/function.hpp>
#pragma pop_macro("B")
#pragma pop_macro("W")
#pragma pop_macro("D")
#pragma pop_macro("Q")
#pragma pop_macro("O")
#endif	// WORLD_EDITOR

#include <EngineGUI/EngineGUI.h>

#include "Resource.h"
#include "DlgSelectMode.h"
#include "WndDisplayTexture.h"
#include "DlgChooseTextureType.h"
#include "DlgCreateNormalTexture.h"
#include "DlgCreateAnimatedTexture.h"
#include "DlgCreateEffectTexture.h"

// this is needed for resource setting
#ifndef NDEBUG
  #define ENGINEGUI_DLL_NAME "EngineGUID.dll"
#else
  #define ENGINEGUI_DLL_NAME "EngineGUI.dll"
#endif

