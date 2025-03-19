#ifndef _DEFS_H_
#define _DEFS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static SDL_Event event;

const int WINDOW_W = 1280;
const int WINDOW_H = 720;
extern const char* WINDOW_TITLE;
extern const char* BACKGROUND_FILE;
extern const char* PLAYER_FILE;

const int start_player_x = 440;
const int start_player_y = 480;

#endif