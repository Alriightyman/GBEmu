#include <iostream>
#include <SDL.h>
#include "Emulator.h"


// sdl test application
int main(int argc, char** argv)
{
	const std::string rom = R"(C:\Users\rturner\Documents\GitHub\GBEmu\Debug\Tetris.gb)";
	Emulator emu;
	if (!emu.Initialize())
		return -1;

	emu.LoadROM(rom.c_str());

	SDL_Event e;
	bool quit = false;
// loop
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
		//If user closes the window
			if (e.type == SDL_QUIT)
				quit = true;
		}

		emu.Run();
		
	}

	SDL_Quit();

	return 0;
}