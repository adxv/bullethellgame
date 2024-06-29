#include "Game.h"

using namespace sf;

int main()
{
	//init rand
	srand(static_cast<unsigned>(time(0)));

	//init game obj
	Game game;
	
	//game loop
	while (game.running()) {
		game.update();
		game.render();
	}


	return 0;
}
