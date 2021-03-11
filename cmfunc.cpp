#include "cmFunc.h"
void cmfunc::initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
	window = SDL_CreateWindow("Flying Lina", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	TTF_Init();
}
void cmfunc::quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void cmfunc::waitUntilKeyPressed()
{
	SDL_Event e;
	while (true)
	{
		if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_QUIT || e.type == SDL_KEYDOWN))
			return;
		SDL_Delay(100);
	}
}
void cmfunc::loadBG(SDL_Surface*& background, SDL_Texture*& texture, SDL_Renderer* renderer, const char* file_name)
{
	background = IMG_Load(file_name);
	texture = SDL_CreateTextureFromSurface(renderer, background);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
SDL_Texture* cmfunc::loadTexture(SDL_Renderer* renderer, const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	return texture;
}
