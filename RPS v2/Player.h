#pragma once
#include "Game.h"
#include "EndGameData.h"
#include "Utils.h"
#include "FileExternal.h"
#include <vector>
#include <string>

class Input;
class Pawn;
class Game;

constexpr size_t numOfPawns = 13;

typedef struct pawncounter {
	short *paper;
	short *rock;
	short *scissor;
	short *flag;
	short *joker;
	short *bomb;
} Pawn_Counter ;

class Player {
	std::string name;
	Pawn *pawns[numOfPawns] = { nullptr };
	Pawn_Counter counter;
	Color _color;
public:
	//constructors
	Player() {};
	Player(Color dye);
	~Player();
	//function declarations
	std::string &getName() { return name; }
	void printPawns() const;
	void setPrints(char rep);
	void createPawn(std::string pawnLine, Pawn *&index);
	Color getColor() { return _color; }
	Pawn** getPawns() { return pawns; }
	short getFlagCounter() { return *counter.flag; }
	void setPawns(std::vector<std::string> &positions);
	Pawn_Counter getCounter() { return counter; }
	bool jokerCounting() { return *counter.joker >= 1; }
	void deleteCounter();
	void checkPawnCounter();
	bool checkFlagCounter();
	void allocateCounters();
	char counterSum() const;
	char counterSumMobile() const;
	void checkWinCondition(Player *winner);
	void deletePawn(Pawn** pawn);
	void move(std::string &moveCommand, Game *current);
	void jokerChange(std::string &moveCommand, Game* current);
	void destinationHandler(Square &source, Square &destination, Game *current, std::string &moveCommand);
	void destionationOccupied(Square &source, Square &destination, Game *current, std::string &moveCommand);
};