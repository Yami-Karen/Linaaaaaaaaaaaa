#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
static const int SCREEN_WIDTH = 1024;
static const int SCREEN_HEIGHT = 600;
static SDL_Window* window;
static SDL_Renderer* renderer;
namespace cmfunc
{
	void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
	void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
	void loadBG(SDL_Surface*& background, SDL_Texture*& texture, SDL_Renderer* renderer, const char* file_name);
	void waitUntilKeyPressed();
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
}