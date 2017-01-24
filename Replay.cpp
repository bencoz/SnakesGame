#include "Replay.h"


void Replay::addChange(Point loc, char ch) {
	Change c;
	__int64 now;
	now = getTimeMs();
	c.time = (int)(now - lchange);
	c.p.set(loc.getX(), loc.getY());
	c.ch = ch;
	changes.push_back(c);
	lchange = now;
}

void Replay::PrintChanges(Change ch) {
	gotoxy(ch.p.getX(), ch.p.getY());
	switch (ch.ch) {
	case('@') :
		setTextColor(LIGHTGREEN);
		cout << ch.ch;
		break;
	case('#') :
		setTextColor(LIGHTBLUE);
		cout << ch.ch;
		break;
	case('!') :
		setTextColor(GREEN);
		cout << ch.ch;
		break;
	case('%') :
		setTextColor(YELLOW);
		cout << ch.ch;
		break;
	case('*') :
		setTextColor(LIGHTRED);
		cout << ch.ch;
		break;
	default:
		setTextColor(WHITE);
		cout << ch.ch;
	}
	Sleep(ch.time);
}

void Replay::startReplay(){
	gotoxy(0, 2);
	setTextColor(LIGHTRED);
	cout << "REPLAY";
	setTextColor(WHITE);
	for (int i = 4; i < 24; i++) {
		for (int j = 0; j < 80; j++) {
			gotoxy(j, i);
			cout << startBoard[i][j];
		}
	}

	for_each(changes.begin(), changes.end(), [this](Change& ch){Replay::PrintChanges(ch); });
}

void Replay::waitForReturn(){
	gotoxy(0, 2);
	setTextColor(LIGHTRED);
	cout << "Replay has ended !! - ";// - Click Any Key To Resume";
	system("Pause");
	gotoxy(0, 2);
	cout << "                                                     ";
}