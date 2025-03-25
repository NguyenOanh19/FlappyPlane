#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include "defs.h"

using namespace std;

struct Move {
    int x = start_player_x;
    int y = start_player_y;
    int dx = 0, dy = 0;

    void position() { 
        y += dy; 
        if (y < 0) { y = start_player_y; }
        if (y > WINDOW_H) { y = 0; }
    }
    void up() { dy = -SPEED; }
    void down() { dy = SPEED; }
    void reset() { dy = 0; }
};

struct Player
{
    vector<SDL_Texture*> textures;
    int frame = 0;

    void loadPlayer(const char* folder, Object& object) {
        textures.resize(FRAME_QUANTITY);
        for (int i = 0; i < FRAME_QUANTITY; i++)
        {
            string filePath = folder;
            if (i < 10)
                filePath += '0';
            filePath += to_string(i) + ".png";
            textures[i] = object.loadTexture(filePath.c_str());
        }
    }

    void tick() {
        frame = (frame + 1) % FRAME_QUANTITY;
    }

    void render(Object &object,const Move &move) {
        object.renderTexture(textures[frame], move.x, move.y);
    }
};

#endif