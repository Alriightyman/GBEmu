#include <iostream>
#include <SDL.h>
#include "Emulator.h"
#include "WinUtilities.h"
#include "resource.h"

Emulator emu;

LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}

// sdl test application
int main(int argc, char** argv)
{
	//	const std::string rom = R"(C:\Users\Alrii\Documents\Programming\GitHub\GBEmu\Emulator\Roms\Tetris.gb)";
	//	Emulator emu;
	//	if (!emu.Initialize())
	//		return -1;
	//
	//	emu.LoadROM(rom.c_str());
	//
	//	SDL_Event e;
	//	bool quit = false;
	//// loop
	//	while (!quit)
	//	{
	//		while (SDL_PollEvent(&e))
	//		{
	//		//If user closes the window
	//			if (e.type == SDL_QUIT)
	//				quit = true;
	//		}
	//
	//		emu.Run();		
	//	}
	//
	//	SDL_Quit();
	//
	//	return 0;


	const char* title = "GBemu";
	bool isRunning = true;
	bool isRomLoaded = false;
	SDL_Event mainEvent;
	HWND windowHandler;



	//Initialize the SDL Subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Unable to initialize SDL subsystems: %s", SDL_GetError());
		return 1;
	}

	//Create a window pointer + allocate a window object to it.
	SDL_Window* mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, NULL);
	windowHandler = WinUtilities::GetSDLWinHandle(mainWindow);

	//Activate the menu bar of the window
	WinUtilities::ActivateMenu(windowHandler);

	//Initialize Rendering Device
	SDL_Renderer* mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(mainRenderer);

	const std::string rom = R"(C:\Users\Alrii\Documents\Programming\GitHub\GBEmu\Emulator\Roms\Tetris.gb)";
	
	if (!emu.Initialize())
		return -1;

	//Enable WinAPI Events Processing
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

	while (isRunning)
	{
		SDL_PollEvent(&mainEvent);
		switch (mainEvent.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
			mainEvent.type = SDL_QUIT;
			SDL_PushEvent(&mainEvent);
			break;
		case SDL_SYSWMEVENT:
			if (mainEvent.syswm.msg->msg.win.msg == WM_COMMAND)
			{
				// exit app
				if (LOWORD(mainEvent.syswm.msg->msg.win.wParam) == ID_EXIT)
				{
					isRunning = false;
				}
				// load rom
				if (LOWORD(mainEvent.syswm.msg->msg.win.wParam) == ID_LOADROM)
				{
					emu.LoadROM(rom.c_str());
					isRomLoaded = true;
				}
				// open debugger
				if (LOWORD(mainEvent.syswm.msg->msg.win.wParam) == ID_DEBUGGER)
				{
					auto win = DialogBox(NULL, MAKEINTRESOURCE(IDD_Debugger),
						windowHandler, reinterpret_cast<DLGPROC>(DlgProc));
					/*SendDlgItemMessageA(win, IDD_Debugger, UINT   Msg,
						WPARAM wParam,
						LPARAM lParam*/
				}

			}
			break;
		case SDL_QUIT:
			isRunning = false;
			break;
		};


		if (isRomLoaded)
		{
			emu.Run();
		}
	}

	SDL_Quit();

	return 0;
}

