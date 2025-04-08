#ifndef _DEFS_H_
#define _DEFS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

const int WINDOW_W = 1200;
const int WINDOW_H = 720;

//file
extern const char* WINDOW_TITLE;
extern const char* BACKGROUND_FILE;
extern const char* PLAYER_FILE;
extern const char* FONT_FILE;
extern const char* MAP_FILE;
extern const char* TILE_FILE;
extern const char* PIPE_UP;
extern const char* PIPE_DOWN;
extern const char* DIE_SOUND;
extern const char* FLAP_SOUND;
extern const char* HIT_SOUND;
extern const char* POINT_SOUND;
extern const char* BACKGROUND_MUSIC;
extern const char* GAME_OVER_TEXT;
extern const char* HIGH_SCORE_FILE;

//player
const int NUM_FRAMES = 3;
const int SPEED = 40;
const int GRAVITY_SPEED = 2;
const int PLAYER_W = 88;
const int PLAYER_H = 73;
const int PLAYER_X = 450;
const int PLAYER_Y = (WINDOW_H - PLAYER_H) / 2;

//pipe 
const int PIPE_H = 653;
const int PIPE_W = 74;
const int PIPE_DISTANCE = 200;
const int NUM_PIPES = 5;

//fps
const int FPS = 60; // frame per second
const int ACCEL = 5;
const int MIN_SCROLL = 5;
const int MAX_SCROLL = 10;

//music
const int NUM_SOUND_EFFECTS = 3;

//button
const int NUM_BUTTONS = 5;
const int BUTTON_W = 40;
const int BUTTON_H = 40;

//color
const SDL_Color TEXT_COLOR = { 93, 163, 189 , 255 };

struct Position
{
	int x, y;

	Position()
	{
		x = y = 0;
	}

	Position(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

struct GameStatus
{
	bool quit, gameOver, sound, paused, restarted, isRunning;
	GameStatus()
	{
		quit = 0, gameOver = 0, sound = 1, paused = 0, restarted = 0, isRunning = 0;
	}
	void reset()
	{
		quit = 0, gameOver = 0, sound = 1, paused = 0, restarted = 0, isRunning = 0;
	}
};

#endif