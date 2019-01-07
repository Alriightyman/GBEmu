#pragma once
#include <Windows.h>
#include "SDL.h"
#include "SDL_syswm.h"

#define ID_LOADROM 1
#define ID_ABOUT 2
#define ID_EXIT 3
#define ID_DEBUGGER 4

struct WinUtilities
{

	static HWND GetSDLWinHandle(SDL_Window* win);
	static void ActivateMenu(HWND windowRef);

	static HMENU hHelp;
	static HMENU hEdit;
	static HMENU hFile;
	static HMENU hMenuBar;
};

