#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "defs.h"

struct Scrolling {
    SDL_Texture* background;
    SDL_Rect clip = { 0,0,0,0 };

    void setTexture(SDL_Texture* texture) {
        background = texture;
        SDL_QueryTexture(background, NULL, NULL, &clip.w, &clip.h);
    }

    void scroll(int dist) {
        clip.x -= dist;
        if (clip.x < 0) clip.x = clip.w;
    }
};

struct Object
{
    SDL_Texture* texture;
    SDL_Rect rect = { 0, 0, 0, 0 };

    SDL_Texture* getTexture() { return texture; }
    SDL_Rect getRect() { return rect; }

    bool loadTexture(SDL_Renderer* renderer, const char* file);
    void renderTexture(SDL_Renderer* renderer, int x, int y);
    void render(const Scrolling& bgr);
    void free();
};



#endif