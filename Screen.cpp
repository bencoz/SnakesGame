#include "Screen.h"
#include "Color.h"

int Screen::Begin_Screen() {
	char key;
	Clear_Screen();
	gotoxy(0, 0);
	setTextColor(WHITE);
	cout << "Press 1 for Instructions" << endl;
	cout << "Press 2 to Start a new game" << endl;
	cout << "Press 9 to Exit" << endl;
	cout.flush();
	do {
		key = _getch();
	} while (key != '1' && key != '2' && key != '9');
	return (int)(key - '0');
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
	cout << "Press 7 to replay last game" << endl;
	cout.flush();
	do {
		key = _getch();
	} while (key != '7' && key != '6' && key != '5'  && key != '4' && key != '3' && key != '2' && key != '1');
	return (int)(key - '0');
}

void Screen::Instructions_Screen() {
	char key;
	Clear_Screen();
	gotoxy(0, 0);
	setTextColor(WHITE);
	cout << "Press Esc to retrun to main menu" << endl << endl;
	cout << "This is a game called Snake." << endl;
	cout << "Its a 2 players game, Each player has a snake 3 signs size." << endl;
	cout << "The Objective is to get your snake to 12 signs size." << endl;
	cout << "To do that you have to collect with your snake the correct numbers that appers on the screen." << endl;
	cout << "The correct numbers depends on the missions. You have 6 different missions in the game" << endl;
	cout << "The missions are:" << endl;
	cout << "1.) Prime_Number: Collect a prime number." << endl;
	cout << "2.) Divided_By_4: Collect a number that divides by 4." << endl;
	cout << "3.) Multiple_By_7: Collect a number that is a multiple of 7." << endl;
	cout << "4.) Square_Of_Z_Num: Collect a number which is a square of an integer." << endl;
	cout << "5.) Rest_Is_3: Collect a number that when you divide it by 7 the rest is 3." << endl;
	cout << "6.) Square_Of_13: Collect the square of 13." << endl;
	cout << "If you collect a correct number, the snake will grow by 1 and the mission will change." << endl;
	cout << "If you collect a wrong number, the second snake will frow by 1 and the mission will change." << endl;
	cout << "Good Luck!" << endl;
	do {
		key = _getch();
	} while (key != ESC);
}

void Screen::Clear_Screen() {
	gotoxy(0, 0);
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++)
			cout << " ";
	}
}