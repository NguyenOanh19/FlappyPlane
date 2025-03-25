#include "defs.h"
#include "collision.h"

RectangleBounds getBounds(const SDL_Rect& r1) {
	int x1 = r1.x / CELL_SIZE;
	int y1 = r1.y / CELL_SIZE;

	int x2 = x1 + r1.w / CELL_SIZE + (r1.w % CELL_SIZE == 0 ? 0 : 1);
	int y2 = y1 + r1.h / CELL_SIZE + (r1.h % CELL_SIZE == 0 ? 0 : 1);

	return { x1,y1,x2,y2 };
}

bool isColliding(const SDL_Rect& r1, const SDL_Rect& r2) {
	RectangleBounds bounds1 = getBounds(r1), bounds2 = getBounds(r2);

	if (bounds1.x1 == bounds2.x2 || bounds1.x2 == bounds2.x1
		|| bounds1.y1 == bounds2.y2 || bounds1.y2 == bounds2.y1)
		return 1;
	return 0;
}