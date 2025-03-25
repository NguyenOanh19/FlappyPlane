#ifndef _MAP_H_
#define _MAP_H_

#include "defs.h"
#include "object.h"

int randomNum(int start, int end);

struct Map {
	vector<int> height, distance;

	void removeAndSpawn(int offset);
	void render(Object& object, int offset, SDL_Texture* texture);
};

#endif // !_MAP_H

