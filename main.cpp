#include "defs.h"
#include "object.h"
#include "player.h"
#include "map.h"

using namespace std;

Object object;
Move currentMove;
ScrollingObject sBgr, sTile;
Player wraith;
Map gameMap;

void close();

int main(int argc, char* argv[])
{
    if (!object.init())
        return 0;

    SDL_Texture* bgr = object.loadTexture(BACKGROUND_FILE);
    SDL_Texture* icon = object.loadTexture("img\\icon\\6.png");
    SDL_Texture* tile = object.loadTexture("img\\icon\\6.png");
    sBgr.setTexture(bgr);

    wraith.loadPlayer(PLAYER_FILE, object);

    bool quit = 0, gameOver = 0;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                quit = 1;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                    currentMove.up();
            }
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                    currentMove.reset();
            }
        }
        SDL_RenderClear(object.renderer);

        sBgr.scroll(5);
        object.render(sBgr);

        gameMap.removeAndSpawn(sBgr.offset);
        gameMap.render(object, sBgr.offset, tile);

        wraith.tick();
        currentMove.position();
        wraith.render(object, currentMove);

        for (int i = currentMove.y + 80; i <= WINDOW_H; i += CELL_SIZE) {
            object.renderTexture(icon, currentMove.x + 20, i);
        }

        SDL_RenderPresent(object.renderer);

        SDL_Delay(50);
    }

    object.free(bgr);
    object.free(icon);

    close();

    return 0;
}

void close()
{
    sBgr.free();
    object.destroy();
}