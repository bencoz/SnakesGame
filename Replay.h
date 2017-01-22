#ifndef _REPLAY_H_
#define _REPLAY_H_
#include <iostream>
#include "Point.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>


class Replay {
	struct Change{
		int time;
		Point p;
		char ch;
	};

	char startBoard[24][81];
	vector<Change> changes;
	__int64 lchange = 0;

public:
	/*Replay();
	~Replay();*/
	void saveState(char board[24][81]){
		memcpy(startBoard, board, sizeof(char)*24*(81));
		changes.clear();
		lchange = getTimeMs();
	}
	void addChange(Point loc, char ch);
	void PrintChanges(Change ch);
	void startReplay();
	__int64 getTimeMs() {
		return std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

};


#endif