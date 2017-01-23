#include "MissionManager.h"

MissionManager::MissionManager(char *_description, int _X, int _Y) {
	description = _strdup(_description);
	X = rand() % (_Y - _X) + _X;
	do {
		Y = rand() % (_Y - _X) + _X;
	} while (Y == X);
}

MissionManager::~MissionManager() {
	delete description;
}


void MissionManager::printDescript() {
	for (int i = 0; i < (int)strlen(description); i++)
	{
		if (description[i] == 'X')
			cout << ' ' << X << ' ';
		else if (description[i] == 'Y')
			cout << ' ' << Y << ' ';
		else
			cout << description[i];
	}
}

