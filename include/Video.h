#pragma once
// video class uses SDL to draw and update
#include <SDL.h>

class Video
{
private:
	SDL_Window* m_win;
	SDL_Renderer* m_renderer;
	int m_width, m_height;
	float m_scale;
	// background logo shown while not running a game
	SDL_Texture* m_backGroundLogo;
public:
	Video(void);
	~Video(void);
	bool Initialize();
	void Run();
	void Shutdown();
};

