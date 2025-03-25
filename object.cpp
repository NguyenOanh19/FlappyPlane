#include "object.h"
#include "defs.h"

bool Object::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("SDL_Init: %s", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        SDL_Log("CreateWindow: %s", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        SDL_Log("CreateRenderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
    {
        SDL_Log("IMG_Init: %s", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        IMG_Quit();
        return 0;
    }

    return 1;
}

SDL_Texture* Object::loadTexture(const char* file)
{
    SDL_Log("Loading %s", file);

    SDL_Texture *texture = IMG_LoadTexture(renderer, file);
    if (texture == nullptr)
        SDL_Log("Fail to load %s: %s", file, IMG_GetError());

    return texture;
}

void Object::renderTexture(SDL_Texture* texture, int x, int y)
{
    if (texture == nullptr)
    {
        SDL_Log("Texture is nullptr");
        return;
    }

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Object::render(const ScrollingObject& bgr) {
    renderTexture(bgr.texture, bgr.offset - bgr.width, 0);
    renderTexture(bgr.texture, bgr.offset, 0);
}

TTF_Font* Object::loadFont(const char* file, int size) {
    SDL_Log("Load Font: %s", file);
    TTF_Font *font = TTF_OpenFont(file, size);
    if (font == nullptr)
        SDL_Log("OpenFont: %s", TTF_GetError());

    return font;
}

SDL_Texture* Object::renderText(const char* text, TTF_Font* font, SDL_Color textColor) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    if (surface == nullptr) {
        SDL_Log("RenderText: %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
        SDL_Log("CreateTextureFromSurface: %s", SDL_GetError());

    SDL_FreeSurface(surface);
    return texture;
}


void Object::free(SDL_Texture *texture)
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Object::destroy() {
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}