#include "map.h"
#include "defs.h"

int randomNum(int start, int end) {
	return start + rand() % (end - start + 1);
}

void Map::removeAndSpawn(int offset) {
	if (offset == 0) {
		srand(0);
		if (!height.empty() && !distance.empty()) {
			height.erase(height.begin());
			distance.erase(distance.begin());
		}

		int h = randomNum(1, WINDOW_H / CELL_SIZE - 1);
		int d = randomNum(1, 5);

		height.push_back(h);
		distance.push_back(d + (distance.empty() ? 0 : distance.back()));
	}
}

void Map::render(Object& object, int offset, SDL_Texture* texture)
{
	for (int i = 0; i < height.size(); i++) {
		for (int j = 1; j <= height[i]; j++) {
			object.renderTexture(texture, offset + distance[i] * CELL_SIZE, WINDOW_H - j * CELL_SIZE);
		}
	}
}