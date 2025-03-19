#include "defs.h"
#include "object.h"
#include "player.h"
#include <iostream>

Object background;
Player wraith;
Scrolling scrolling;

bool initData();
void prepareScene(SDL_Texture* texture);
void close();

int main(int argc, char* argv[])
{
    if (!initData())
        return 0;

    if (!background.loadTexture(renderer, BACKGROUND_FILE))
        return 0;
    background.renderTexture(renderer, 0,0);
    SDL_RenderPresent(renderer);

    wraith.player.resize(12);
    wraith.loadPlayer(renderer, PLAYER_FILE);

    bool quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if(event.type == SDL_KEYDOWN)
                wraith.tick();
            prepareScene(background.texture);
            //
            // 
            // 
            // 
            // 
            // 
            // 
            // 
            // 
            // wraith.renderPlayer();
            SDL_RenderCopy(renderer, wraith.player[wraith.frame].texture, NULL, &wraith.player[wraith.frame].rect);
            SDL_RenderPresent(renderer);

            SDL_Delay(100);
        }
    }

    close();

    return 0;
}

bool initData()
{
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

    return 1;
}

void prepareScene(SDL_Texture* texture) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void close()
{
    background.free();
    wraith.free();

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
}