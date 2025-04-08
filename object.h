#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "defs.h"

struct Object
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    void logErrorAndExit(const char* msg, const char* error);
    void init();

    SDL_Texture* loadTexture(const char* file);
    void renderTexture(SDL_Texture* texture, int x, int y);

    void destroyTexture(SDL_Texture* texture);
    void quit();
};

struct Scrolling
{
    Object* object;
    SDL_Texture* texture;
    int offset = 0;
    int width;

    void loadAndSetTexture(const char* file);
    void scroll(int dist);
    void render();
    void destroyTexture();
};

#endif