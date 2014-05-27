#include "Video.h"
#include <iostream>

Video::Video(void) : m_win(nullptr), m_renderer(nullptr),
	m_height(160),m_width(144),m_scale(1.0f)
{

}


Video::~Video(void)
{
}

bool Video::Initialize()
{
	m_scale = 4.0f;
	// initialize sdl
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "SDL_Init Error " << SDL_GetError() << std::endl;
		return false;
	}
	// create the window
	m_win = SDL_CreateWindow("GBEmu",100,100,m_width*m_scale,m_height*m_scale,SDL_WINDOW_SHOWN);

	if (m_win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error " << SDL_GetError() << std::endl;
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_Surface* bmp = SDL_LoadBMP("data/GBEmu.bmp");
	if (bmp == nullptr)
	{
		std::cout << "SDL_LoadBMP Error " << SDL_GetError() << std::endl;
		return 1;
	}

	m_backGroundLogo = SDL_CreateTextureFromSurface(m_renderer,bmp);
	SDL_FreeSurface(bmp);

	if (m_backGroundLogo == nullptr)
	{
		std::cout << "SDL_CreateTextureFromSurface Error " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(m_renderer,0,32,0,255);

	return true;
}

void Video::Run()
{
	
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer,m_backGroundLogo,0,0);
	SDL_RenderPresent(m_renderer);
}

void Video::Shutdown()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_win);

	SDL_Quit();
}