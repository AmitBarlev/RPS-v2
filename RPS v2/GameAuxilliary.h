#pragma once
#include "GameModes.h"
#include "Game.h"
#include "Player.h"
#include <string>

constexpr size_t parameters = 3;

class GameAuxilliary {

public:
	void newGame(int argc, char *argv[]);
	int whichMode(char* argv[], int &index);
	int* getParameters(int argc, char* argv[]);
	Game* initializeGame(int* parameters, Player **players);
	Input *whichInput(int which);
	Player** preparePlayers(Input* command);
	void GameAuxilliary::deletePlayers(Player **arr);
};