#include <windows.h>
#include <iostream>
using namespace std;

#include "TheSnakesGame.h"
#include "_board.h"

int main() {
	hideCursor();
	TheSnakesGame game;
	game.setBoard(start_board);
	game.init();
	game.run();
}