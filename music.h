#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "defs.h"
#include "object.h"
#include "player.h"
#include "pipe.h"

struct Music
{
	Move* move;
	Pipe* pipe;
	
	Mix_Music* backgroundMusic;
	Mix_Chunk* sounds[NUM_SOUND_EFFECTS];

    Mix_Music* loadMusic(const char* path);
    void play(Mix_Music* gMusic);
	Mix_Chunk* loadSound(const char* path);
	void play(Mix_Chunk* gChunk);
	void load();
	void playMusic();
	void free();
};

#endif // !_MUSIC_H_
