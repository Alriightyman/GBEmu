#include "WinUtilities.h"


HMENU WinUtilities::hHelp;
HMENU WinUtilities::hEdit;
HMENU WinUtilities::hFile;
HMENU WinUtilities::hMenuBar;

HWND WinUtilities::GetSDLWinHandle(SDL_Window * win)
{
	SDL_SysWMinfo infoWindow;
	SDL_VERSION(&infoWindow.version);
	if (!SDL_GetWindowWMInfo(win, &infoWindow))
	{
		return NULL;
	}
	return (infoWindow.info.win.window);
}

void WinUtilities::ActivateMenu(HWND windowRef)
{
	hMenuBar = CreateMenu();
	hFile = CreateMenu();
	hEdit = CreateMenu();
	hHelp = CreateMenu();

	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile, "File");
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEdit, "Edit");
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelp, "Help");

	AppendMenu(hFile, MF_STRING, ID_LOADROM, "Load ROM");
	AppendMenu(hFile, MF_STRING, ID_EXIT, "Exit");

	AppendMenu(hEdit, MF_STRING, ID_DEBUGGER, "Debugger");

	AppendMenu(hHelp, MF_STRING, ID_ABOUT, "About");

	SetMenu(windowRef, hMenuBar);
}
