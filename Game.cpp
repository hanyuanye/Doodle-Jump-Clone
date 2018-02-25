#include "Game.h"

colour BACKGROUND_COLOUR(220, 236, 254);

Game::Game()
{
}


Game::~Game()
{
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOUR.r, BACKGROUND_COLOUR.g, BACKGROUND_COLOUR.b, 0);
			SDL_RenderPresent(renderer);
		}

		running = true;
	}
	else {
		return false;
		running = false;
	}
	engine = new PhysicsEngine(renderer, TIME_STEP, 600, 800);

	TTF_Init(); 
	return true;
}


void Game::handle_input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_LEFT) {
				engine->move = left;
			}
			if (e.key.keysym.sym == SDLK_RIGHT) {
				engine->move = right;
			}
			break;
		case SDL_KEYUP:
			engine->move = none;
			break;

		default:
			break;
		}
	}
}

void Game::update()
{
	if (!engine->gameover)
		engine->update();
}

void Game::render()
{
	if (!engine->gameover)
		engine->render();
	else {
		game_over();
	}
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	delete engine;
}

void Game::game_over()
{

	SDL_RenderClear(renderer);
	std::string game_over_string = "Game Over! Final Score: " + std::to_string(engine->score);
	TTF_Font* game_over_font = TTF_OpenFont("arial.ttf", 35);
	SDL_Color text_colour = { 0, 0, 0 };
	SDL_Surface * surface_message = TTF_RenderText_Solid(game_over_font, game_over_string.c_str(), text_colour);
	int text_width = surface_message->w;
	int text_height = surface_message->h;

	SDL_Texture * texture_message = SDL_CreateTextureFromSurface(renderer, surface_message);
	SDL_Rect rect = { 75, 300, text_width, text_height };

	SDL_RenderCopy(renderer, texture_message, NULL, &rect);
	TTF_CloseFont(game_over_font);
	SDL_FreeSurface(surface_message);
	SDL_DestroyTexture(texture_message);
	SDL_RenderPresent(renderer);
}

bool Game::isRunning()
{
	return running;
}
