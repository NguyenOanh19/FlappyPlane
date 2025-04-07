#include "defs.h"
#include "time.h"
#include "game.h"

using namespace std;

int main(int argc, char* argv[])
{
	Game FlappyPlane;

	FlappyPlane.init();

	while (!FlappyPlane.gameStatus.quit) {
		int realTime = SDL_GetTicks();
		FlappyPlane.handleEvents();

		if (FlappyPlane.gameStatus.restarted) {
			FlappyPlane.reset();
		}
		if (!FlappyPlane.gameStatus.gameOver && !FlappyPlane.gameStatus.paused)
		{
			FlappyPlane.update(5);
			FlappyPlane.renderAndPlayMusic();
		}

		int frameTime = 1000 / FPS;
		if (realTime < frameTime)
			SDL_Delay(frameTime - realTime);
	}

	FlappyPlane.clean();

	return 0;
}