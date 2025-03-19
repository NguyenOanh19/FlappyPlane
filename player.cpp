#include "player.h"
#include "object.h"
#include "defs.h"

using namespace std;

bool Player::loadPlayer(SDL_Renderer* renderer,const char* folder)
{
    
    for (int i = 0; i < frame_quantity; i++)
    {
        string filePath = folder;
        if (i < 10)
            filePath += '0';
        filePath += to_string(i) + ".png";
        bool load = player[i].loadTexture(renderer, filePath.c_str());
        if (!load)
            return 0;

        player[i].rect.x = 440;
        player[i].rect.y = 480;
    }
    return 1;
}

void Player::renderPlayer()
{
    player[frame].renderTexture(renderer, start_player_x, start_player_y);
}

void Player::tick()
{
    frame = (frame + 1) % frame_quantity;
}

void Player::free() {
    for (int i = 0; i < frame_quantity; i++) {
        player[i].free();
    }
}
