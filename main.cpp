#include "defs.h"
#include "time.h"
#include "game.h"

using namespace std;

int updateScroll(const int& score) {
	int scroll2 = 2 * ACCEL * score - pow(MIN_SCROLL, 2);
	if (scroll2 <= 0) 
		return MIN_SCROLL;
	if (sqrt(scroll2) < MIN_SCROLL)
		return MIN_SCROLL;
	if (sqrt(scroll2) > MAX_SCROLL) 
		return MAX_SCROLL;
	return sqrt(scroll2);
}

int main(int argc, char* argv[])
{
	Game FlappyPlane;

	FlappyPlane.init();
	srand(time(0));

	while (!FlappyPlane.gameStatus.quit) {
		int realTime = SDL_GetTicks();
		FlappyPlane.handleEvents();

		if (FlappyPlane.gameStatus.restarted) {
			FlappyPlane.reset();
		}
		if (!FlappyPlane.gameStatus.gameOver && !FlappyPlane.gameStatus.paused)
		{
			if(FlappyPlane.gameStatus.isRunning)
				FlappyPlane.update(updateScroll(FlappyPlane.score));
			FlappyPlane.renderAndPlayMusic();
		}

		int frameTime = 1000 / FPS;
		if (realTime < frameTime)
			SDL_Delay(frameTime - realTime);
	}

	FlappyPlane.clean();

	return 0;
}