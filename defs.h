#ifndef _DEFS_H_
#define _DEFS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

const int WINDOW_W = 1280;
const int WINDOW_H = 720;

//file
extern const char* WINDOW_TITLE;
extern const char* BACKGROUND_FILE;
extern const char* PLAYER_FILE;
extern const char* FONT_FILE;
extern const char* MAP_FILE;

//player
const int FRAME_QUANTITY = 12;
const int start_player_x = 480;
const int start_player_y = 640;
const int SPEED = 40;
const int CELL_SIZE = 40;

//map
const int MAX_J = 32;
const int MAX_I = 18;
const int TILES_QUANTITY = 5;

#endif