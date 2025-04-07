#ifndef _PIPE_H_
#define _PIPE_H_

#include "defs.h"
#include "object.h"

struct Pipe {
	Object* object;
	vector<Position> pipePos;
	SDL_Texture* up, * down;

	int randMin = PIPE_DISTANCE + 100;
	int randMax = WINDOW_H - randMin;

	void initPosition();
	void render();
	void updatePosition(int dist);
	void destroyTexture();
};

#endif // !_PIPE_H_
