#include "defs.h"
#include "player.h"

void Move::init() 
{
    pos.x = PLAYER_X;
    pos.y = PLAYER_Y;
    isKeyPressed = 0;
    pipePassed = -1;
}
    
void Move::up() 
{
    pos.y -= SPEED;
    if (pos.y <= 0)
        pos.y = 0;
}

void Move::down() 
{
    if (isKeyPressed == 0) {
        pos.y += GRAVITY_SPEED;
        if (pos.y >= PLAYER_Y)
            pos.y = PLAYER_Y;
    }
}

int Move::checkCollision(const vector<Position>& pipePos) 
{
    int pipe = -1;
    int player_x1 = pos.x, player_x2 = player_x1 + PLAYER_W;
    int player_y1 = pos.y, player_y2 = player_y1 + PLAYER_H;

    int pipe_x1, pipe_x2;
    int pipe_y1 = 0, pipe_y2 = 0;

    for (int i = 0; i < NUM_PIPES; i++) 
    {
        pipe_x1 = pipePos[i].x, pipe_x2 = pipe_x1 + PIPE_W;

        if (player_x2 >= pipe_x1 && player_x1 <= pipe_x2) 
        {
            pipe = i;
            pipe_y1 = pipePos[i].y;
            pipe_y2 = pipe_y1 - PIPE_DISTANCE;
            break;
        }
    }

    if (pipe != -1) 
    {
        if (player_y1 <= pipe_y2 || player_y2 >= pipe_y1)
            return 1;
        pipePassed = pipe;
    }
    return 0;
}

bool Move::isPastPipe(const vector<Position>& pipePos) 
{
    if (pipePassed == -1)
        return 0;
    return pos.x >= pipePos[pipePassed].x + PIPE_W;
}

void Player::loadTextures(const char* file) 
{
    for (int i = 0; i < NUM_FRAMES; i++) 
    {
        string path = file;
        path += to_string(i + 1) + ".png";
        textures[i] = object->loadTexture(path.c_str());
    }
}

void Player::render() 
{
    currentFrame = (currentFrame + 1) % NUM_FRAMES;
    object->renderTexture(textures[currentFrame], move->pos.x, move->pos.y);
}

void Player::destroyTextures() 
{
    for (int i = 0; i < NUM_FRAMES; i++) 
    {
        object->destroyTexture(textures[i]);
    }
}