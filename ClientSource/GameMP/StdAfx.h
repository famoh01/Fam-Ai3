
#pragma warning(disable : 4391)		// Platform SDK Warning
#pragma warning(disable : 4996)

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
#include <boost/function.hpp>
#pragma pop_macro("B")
#pragma pop_macro("W")
#pragma pop_macro("D")
#pragma pop_macro("Q")
#pragma pop_macro("O")
#endif	// WORLD_EDITOR
#include <Engine/Engine.h>
#include <GameMP/Game.h>
#include <GameMP/SEColors.h>

/* rcg10042001 protect against Visual C-isms. */
#ifdef _MSC_VER
#define DECL_DLL _declspec(dllimport)
#endif

#ifdef PLATFORM_UNIX
#define DECL_DLL 
#endif

#include <EntitiesMP/Global.h>
#include <EntitiesMP/Common/Common.h>
#include <EntitiesMP/Common/GameInterface.h>
#include <EntitiesMP/Player.h>
#undef DECL_DLL
