#include "game.h"

void Game::saveHighScore() 
{
	if (score >= highScore) 
	{
		highScore = score;
		ofstream myFile(HIGH_SCORE_FILE);
		if (myFile.is_open()) 
		{
			myFile << score;
			myFile.close();
		}
	}
}

void Game::loadHighScore() 
{
	ifstream file(HIGH_SCORE_FILE);
	int highest;
	if (file.is_open()) 
	{
		file >> highest;
		highScore = highest;
		file.close();
	}
}

void Game::init()
{
	object.init();

	music.move = &move;
	music.pipe = &pipe;
	music.load();
	music.play(music.backgroundMusic);

	background.object = &object;
	background.loadAndSetTexture(BACKGROUND_FILE);

	plane.object = &object;
	plane.move = &move;
	plane.loadTextures(PLAYER_FILE);
	move.init();

	pipe.object = &object;
	pipe.up = object.loadTexture(PIPE_UP);
	pipe.down = object.loadTexture(PIPE_DOWN);
	pipe.initPosition();

	gameControls.object = &object;
	gameControls.init();
	gameControls.loadButtons();

	gameOverText.object = &object;
	gameOverText.loadFont(FONT_FILE, 100);
	gameOverText.loadText(GAME_OVER_TEXT);

	scoreText.object = &object;
	scoreText.loadFont(FONT_FILE, 30);

	highScoreText.object = &object;
	highScoreText.loadFont(FONT_FILE, 30);
	loadHighScore();
}

void Game::handleEvents()
{
	int x, y;
	while (SDL_PollEvent(&event))
	{
		SDL_GetMouseState(&x, &y);
		switch (event.type)
		{
		case SDL_QUIT:
			gameStatus.quit = 1;
			break;
		case SDL_KEYDOWN:
			gameStatus.isRunning = 1;
			if (!gameStatus.gameOver && !gameStatus.paused) 
			{
				move.up();
				if (gameStatus.sound)
					music.play(music.sounds[0]);
			}
			break;
		case SDL_KEYUP:
			if (!gameStatus.gameOver && !gameStatus.paused)
				move.isKeyPressed = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			gameControls.handleEvent(x, y, gameStatus);
			break;
		}
	}
}

void Game::update(int distScroll)
{
	background.scroll(distScroll);
	move.down();
	pipe.updatePosition(distScroll);
	if (move.checkCollision(pipe.pipePos))
		gameStatus.gameOver = 1;
	if (move.isPastPipe(pipe.pipePos)) 
	{
		score++;
		saveHighScore();
	}
}

void Game::renderAndPlayMusic()
{
	SDL_RenderClear(object.renderer);
	background.render();
	plane.render();
	pipe.render();
	if (gameStatus.sound)
		music.playMusic();
	gameControls.render();
	if (gameStatus.gameOver) 
	{
		gameOverText.render((WINDOW_W - gameOverText.width) / 2, (WINDOW_H - gameOverText.height) / 2);
	}

	string scoreString = "SCORE: " + to_string(score);
	scoreText.loadText(scoreString.c_str());
	string highScoreString = "HIGH SCORE: " + to_string(highScore);
	highScoreText.loadText(highScoreString.c_str());

	highScoreText.render((WINDOW_W - highScoreText.width) / 2, 100);
	scoreText.render((WINDOW_W - scoreText.width) / 2, 40);

	SDL_RenderPresent(object.renderer);
}

void Game::reset() 
{
	move.init();
	gameControls.init();
	pipe.initPosition();
	gameStatus.reset();
	score = 0;
}

void Game::clean() 
{
	background.destroyTexture();
	plane.destroyTextures();
	pipe.destroyTexture();
	gameControls.destroyTextures();
	gameOverText.destroyTexture();
	scoreText.destroyTexture();
	highScoreText.destroyTexture();
	music.free();
	object.quit();
}