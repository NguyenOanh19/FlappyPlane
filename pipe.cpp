#include "defs.h"
#include "pipe.h"

void Pipe::initPosition() {
	pipePos.clear();

	for (int i = 0; i < NUM_PIPES; i++) {
		int x = WINDOW_W + i * (PIPE_W + PIPE_DISTANCE);
		int y = randMin + rand() % (randMax - randMin + 1);

		pipePos.push_back({ x,y });
	}
}

void Pipe::render() {
	for (int i = 0; i < NUM_PIPES; i++) {
		if (pipePos[i].x <= WINDOW_W && pipePos[i].x >= -PIPE_W) {
			object->renderTexture(up, pipePos[i].x, pipePos[i].y);
			object->renderTexture(down, pipePos[i].x, pipePos[i].y - PIPE_DISTANCE - PIPE_H);
		}
	}
}

void Pipe::updatePosition(int dist) {
	for (int i = 0; i < NUM_PIPES; i++) {
		if (pipePos[i].x + PIPE_W <= 0) {
			pipePos[i].x = pipePos[(i == 0 ? NUM_PIPES - 1 : i - 1)].x + PIPE_DISTANCE + PIPE_W;
			pipePos[i].y = randMin + rand() % (randMax - randMin + 1);
		}
		else
			pipePos[i].x -= dist;
	}
}

void Pipe::destroyTexture() {
	object->destroyTexture(up);
	object->destroyTexture(down);
}