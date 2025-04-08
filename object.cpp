#include "object.h"
#include "defs.h"

void Object::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Object::init() 
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit("SDL_image error:", IMG_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
        logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, WINDOW_W, WINDOW_H);

    if (TTF_Init() == -1) 
    {
        logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        logErrorAndExit("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
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

void Object::destroyTexture(SDL_Texture *texture)
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Object::quit()
{
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Scrolling::loadAndSetTexture(const char* file) 
{
    texture = object->loadTexture(file);
    SDL_QueryTexture(texture, NULL, NULL, &width, NULL);
}

void Scrolling::scroll(int dist) 
{
    offset -= dist;
    if (offset < 0) { offset = width; }
}

void Scrolling::render() 
{
    object->renderTexture(texture, offset - width, 0);
    object->renderTexture(texture, offset, 0);
}

void Scrolling::destroyTexture() 
{
    object->destroyTexture(texture);
}