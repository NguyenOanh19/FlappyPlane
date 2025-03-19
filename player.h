#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include "defs.h"

using namespace std;

struct Player
{
    vector<Object> player;
    //int x = 0, y = 0;
    //int dx = 0, dy = 0;
    int frame_quantity = 12, frame = 0;

    bool loadPlayer(SDL_Renderer* renderer,const char*folder);
    void renderPlayer();
    void tick();
    void free();
};

#endif