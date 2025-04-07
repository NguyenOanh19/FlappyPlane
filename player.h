#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include "defs.h"

using namespace std;

struct Move
{
    Position pos;
    bool isKeyPressed;
    int pipePassed;

    void init();
    void up();
    void down();
    int checkCollision(const vector<Position>& pipePos);
    bool isPastPipe(const vector<Position>& pipePos);
};

struct Player
{
    Object* object;
    Move* move;
    SDL_Texture* textures[NUM_FRAMES];
    int currentFrame = 0;

    void loadTextures(const char* file);
    void render();
    void destroyTextures();
};

#endif