#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "defs.h"

struct RectangleBounds {
	int x1, y1;
	int x2, y2;
};

RectangleBounds getBounds(const SDL_Rect& r1);
bool isColliding(const SDL_Rect &obj1, const SDL_Rect &obj2);

#endif // !_COLLISION_H_
