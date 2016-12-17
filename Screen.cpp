#include "Screen.h"
#include "Color.h"

void Screen::Begin_Screen() {
	this->Clear_Screen();
	gotoxy(0, 0);
	setTextColor(WHITE);
	cout << "Press 1 for Instructions" << endl;
	cout << "Press 2 to Start" << endl;
	cout << "Press 9 to Exit" << endl;
	cout.flush();
}

int Screen::Pause_Screen() {
	char key;
	Clear_Screen();
	gotoxy(0, 0);
	setTextColor(WHITE);
	cout << "Press 1 to Exit" << endl;
	cout << "Press 2 to main menu" << endl;
	cout << "Press 3 to resume" << endl;
	cout << "Press 4 to restart this mission" << endl;
	cout << "Press 5 to start a new mission" << endl;
	cout << "Press 6 to start a new game" << endl;
	cout.flush();
	do {
		key = _getch();
	} while (key != '6' && key != '5'  && key != '4' && key != '3' && key != '2' && key != '1');
	return (int)(key - '0');
}

void Screen::Instructions_Screen() {
	this->Clear_Screen();
	gotoxy(0, 0);
	cout << "whats the game, missions, contorls, score and more" << endl;
}

void Screen::Clear_Screen() {
	gotoxy(0, 0);
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++)
			cout << " ";
	}
}