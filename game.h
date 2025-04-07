#ifndef _GAME_H_
#define _GAME_H_

#include "defs.h"
#include "object.h"
#include "player.h"
#include "pipe.h"
#include "music.h"
#include "control.h"
#include "text.h"

struct Game
{
	Object object;
	Scrolling background;
	Player plane;
	Move move;
	Pipe pipe;
	Music music;
	GameControls gameControls;
	Text gameOverText, scoreText, highScoreText;
	SDL_Event event;
	GameStatus gameStatus;
	int score = 0, highScore = 0;

	void saveHighScore();
	void loadHighScore();
	void init();
	void handleEvents();
	void update(int distScroll);
	void renderAndPlayMusic();
	void reset();
	void clean();
};

#endif // !_GAME_H_
