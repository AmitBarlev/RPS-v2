#pragma once
#include "Game.h"
#include "ConsoleInput.h"
#include "FileExternal.h"
#include "Player.h"


class QuietMode : public Game {

public:
	QuietMode() {};
	QuietMode(Player **players);
};

class PresentationMode : public Game {
	
public:
	PresentationMode() {};
	PresentationMode(int delay) : Game(delay) {};
};

class CompetativeMode : public Game {

public:
	CompetativeMode() {};
	CompetativeMode(int delay, Player **players);
};

class OneSideComp : public Game {

public:
	OneSideComp() {};
	OneSideComp(int delay, char index, Player **players);
};