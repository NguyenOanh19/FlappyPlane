#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "defs.h"

struct ScrollingObject {
    SDL_Texture* texture;
    int offset = 0;
    int width;

    void setTexture(SDL_Texture* _texture) {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, NULL);
    }

    void scroll(int dist) {
        offset -= dist;
        if (offset < 0) { offset = width; }
    }

    void free() {
        if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
};

struct Object
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool init();
    SDL_Rect getRect(SDL_Texture* texture) {
        SDL_Rect rect;
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
        return rect;
    }
    SDL_Texture* loadTexture(const char* file);
    void renderTexture(SDL_Texture* texture, int x, int y);
    void render(const ScrollingObject &bgr);
    TTF_Font* loadFont(const char* file, int size);
    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor);

    void free(SDL_Texture* texture);
    void destroy();
};

#endif