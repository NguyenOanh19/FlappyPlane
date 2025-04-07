#include "control.h"

void GameControls::init() {
	buttons[exit].isRendered = 1;
	buttons[pause].isRendered = 1;
	buttons[sound_on].isRendered = 1;
	buttons[restart].isRendered = 1;
	buttons[sound_off].isRendered = 0;
}

bool GameControls::isClicked(Button button, int x_, int y_) {
	int x1 = button.pos.x, x2 = x1 + BUTTON_W;
	int y1 = button.pos.y, y2 = y1 + BUTTON_H;

	if (x_ >= x1 && x_ < x2 && y_ >= y1 && y_ < y2)
		return 1;
	return 0;
}

void GameControls::loadButtons() {
	for (int i = 0; i < NUM_BUTTONS; i++) {
		buttons[i].texture = object->loadTexture(("img\\button\\" + path[i]).c_str());

		buttons[i].pos.x = buttonPos[i].x;
		buttons[i].pos.y = buttonPos[i].y;
	}
}

void GameControls::render() {
	for (int i = 0; i < NUM_BUTTONS; i++) {
		if (buttons[i].isRendered)
			object->renderTexture(buttons[i].texture, buttons[i].pos.x, buttons[i].pos.y);
	}
}

void GameControls::handleToggle(int i, int j, int x_, int y_) {
	if (buttons[i].isRendered && isClicked(buttons[i], x_, y_)) {
		buttons[i].isRendered = 0;
		buttons[j].isRendered = 1;
	}
	else if (buttons[j].isRendered && isClicked(buttons[j], x_, y_)) {
		buttons[j].isRendered = 0;
		buttons[i].isRendered = 1;
	}
}

void GameControls::handleEvent(int x_, int y_, GameStatus &gameStatus) {
	handleToggle(sound_on, sound_off, x_, y_);

	if (isClicked(buttons[exit], x_, y_))
		gameStatus.quit = 1;

	if (isClicked(buttons[restart], x_, y_))
		gameStatus.restarted = 1;

	if (!gameStatus.paused && isClicked(buttons[pause], x_, y_))
		gameStatus.paused = 1;
	else if (gameStatus.paused && isClicked(buttons[pause], x_, y_))
		gameStatus.paused = 0;

	if (buttons[sound_on].isRendered)
		gameStatus.sound = 1;
	else if (buttons[sound_off].isRendered)
		gameStatus.sound = 0;
}

void GameControls::destroyTextures() {
	for (int i = 0; i < NUM_BUTTONS; i++) {
		object->destroyTexture(buttons[i].texture);
	}
}
