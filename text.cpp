#include "text.h"

void Text::loadFont(const char* file, int size) 
{
    SDL_Log("Load Font: %s", file);
    font = TTF_OpenFont(file, size);
    if (font == nullptr)
        SDL_Log("OpenFont: %s", TTF_GetError());
}

void Text::loadText(const char* text) 
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, TEXT_COLOR);
	if (surface == nullptr) 
	{
		SDL_Log("RenderText: %s", TTF_GetError());
		return;
	}
	texture = SDL_CreateTextureFromSurface(object->renderer, surface);
	if (texture == nullptr)
		SDL_Log("CreateTextureFromSurface: %s", SDL_GetError());

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	SDL_FreeSurface(surface);
}

void Text::render(int x, int y) 
{
    object->renderTexture(texture, x, y);
}

void Text::destroyTexture() 
{
    object->destroyTexture(texture);
}