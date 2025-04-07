#include "music.h"

Mix_Music* Music::loadMusic(const char* path)
{
    Mix_Music* gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
            "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}
void Music::play(Mix_Music* gMusic)
{
    if (gMusic == nullptr) return;

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(gMusic, -1);
    }
    else if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }
}

Mix_Chunk* Music::loadSound(const char* path) {
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
            "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
    }
    return gChunk;
}

void Music::play(Mix_Chunk* gChunk) {
    if (gChunk != nullptr) {
        Mix_PlayChannel(-1, gChunk, 0);
    }
}

void Music::load()
{
	sounds[0] = loadSound(FLAP_SOUND);
	sounds[1] = loadSound(HIT_SOUND);
	sounds[2] = loadSound(POINT_SOUND);

	backgroundMusic = loadMusic(BACKGROUND_MUSIC);
}

void Music::playMusic() {
	if (move->checkCollision(pipe->pipePos)) {
		play(sounds[1]);
	}
	if (move->isPastPipe(pipe->pipePos)) {
		play(sounds[2]);
		move->pipePassed = -1;
	}
}

void Music::free() {
	if (backgroundMusic != nullptr)
		Mix_FreeMusic(backgroundMusic);

	for (int i = 0; i < NUM_SOUND_EFFECTS; i++) {
		if (sounds[i] != nullptr)
			Mix_FreeChunk(sounds[i]);
	}
}