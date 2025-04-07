#include "game.h"

void Game::init()
{
	object.init();

	music.move = &move;
	music.pipe = &pipe;
	music.load();

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
			if (!gameStatus.gameOver && !gameStatus.paused) {
				move.up();
				if(gameStatus.sound)
					music.play(music.sounds[1]);
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
	if (move.isPastPipe(pipe.pipePos)) {
		score++;
	}
}

void Game::renderAndPlayMusic()
{
	SDL_RenderClear(object.renderer);
	background.render();
	plane.render();
	pipe.render();
	if(gameStatus.sound)
		music.playMusic();
	gameControls.render();
	if (gameStatus.gameOver) {
		gameOverText.renderCentered();
	}
	SDL_RenderPresent(object.renderer);
}

void Game::reset() {
	move.init();
	gameControls.init();
	pipe.initPosition();
	gameStatus.reset();
	score = 0;
}

void Game::clean() {
	background.destroyTexture();
	plane.destroyTextures();
	pipe.destroyTexture();
	gameControls.destroyTextures();
	gameOverText.destroyTexture();
	music.free();
	object.quit();
}