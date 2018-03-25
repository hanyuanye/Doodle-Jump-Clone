#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Vec2d.h"
#include <iostream>
class TextureManager
{
public:
	TextureManager(SDL_Renderer*, std::string path, const int&, const int&, const int&, const int&, const int&);
	TextureManager();
	~TextureManager();
	void free();
	void render(const Vec2d&);

	int get_width();
	int get_height();
private:
	SDL_Texture * texture;
	SDL_Renderer * ren;

	int width;
	int height;
};

