#ifndef _TEXT_H_
#define _TEXT_H_

#include "defs.h"
#include "object.h"

struct Text {
	Object* object;
	SDL_Texture* texture;
	TTF_Font* font;

	void loadFont(const char* file, int size);
	void loadText(const char* text);
	void renderCentered();
	void destroyTexture();
};

#endif // !_TEXT_H_
