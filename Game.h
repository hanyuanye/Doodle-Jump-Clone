#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "PhysicsEngine.h"
#include <iostream>
#include <string>

const float TIME_STEP = 1.0 / 60.0;

class Game
{
public:
	Game();
	~Game();
	bool init(const char* , int, int, int, int, bool);
	void handle_input();
	void update();
	void render();
	void clean();
	void game_over();

	bool isRunning();

private:
	bool running;
	SDL_Renderer * renderer;
	SDL_Window * window;
	PhysicsEngine * engine;
};

