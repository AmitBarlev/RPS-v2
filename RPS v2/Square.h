#pragma once
#include "Pawn.h"

class Square {
	Pawn **current;

public:
	Pawn **getPawn() { return current; }
	void setPawn(Pawn **ptr) { current = ptr; }
	bool isSquareOccupied() { return current; }
	void wipe() { current = nullptr; }
	Player* getUser() { return (*current)->getUser(); }
};
