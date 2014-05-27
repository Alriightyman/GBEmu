#include <iostream>
#include <SDL.h>
#include "Emulator.h"
#include "Debug.h"

// sdl test application
int main(int argc, char** argv)
{
	Emulator emu;
	if (!emu.Initialize())
		return -1;

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