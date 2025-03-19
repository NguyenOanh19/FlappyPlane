#include "object.h"
#include "defs.h"

bool Object::loadTexture(SDL_Renderer* renderer, const char* file)
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Log("Loading %s", file);

    texture = IMG_LoadTexture(renderer, file);
    if (texture == nullptr)
    {
        SDL_Log("Fail to load %s: %s", file, IMG_GetError());
        return 0;
    }

    return 1;
}

void Object::renderTexture(SDL_Renderer* renderer, int x, int y)
{
    if (texture == nullptr)
    {
        SDL_Log("Texture is nullptr");
        return;
    }
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Object::render(const Scrolling& bgr) {
    renderTexture(renderer, bgr.clip.x, bgr.clip.y);
    renderTexture(renderer, bgr.clip.x - bgr.clip.w, bgr.clip.y);
}

void Object::free()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    rect.w = 0;
    rect.h = 0;
}