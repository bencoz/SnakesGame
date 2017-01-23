#include <windows.h>
#include <iostream>
using namespace std;

#include "TheSnakesGame.h"
#include "_board.h"

int main() {
	char key;
	hideCursor();
	TheSnakesGame game;
	key = game.BeginScreenSwitch();
	if (key == 1)
	{
		game.setBoard(start_board);
		game.init();
		game.run();
		game.killAllOBJS();
	}
}