#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "defs.h"
#include "object.h"

#define pause 0
#define restart 1
#define sound_off 2
#define sound_on 3
#define exit 4

const string path[NUM_BUTTONS] = { "pause.png", "restart.png", "sound_off.png",
	"sound_on.png", "exit.png"};
const Position buttonPos[NUM_BUTTONS] = { {100,40},{220,40}, {160,40},
	{160,40},{40,40} };

struct Button
{
	SDL_Texture* texture;
	Position pos;
	bool isRendered;
};

struct GameControls {
	Object* object;
	Button buttons[NUM_BUTTONS];

	void init();
	bool isClicked(Button button, int x_, int y_);
	void loadButtons();
	void render();
	void handleToggle(int i, int j, int x_, int y_);
	void handleEvent(int x_, int y_, GameStatus &gameStatus);
	void destroyTextures();
};

#endif // !_CONTROL_H_
