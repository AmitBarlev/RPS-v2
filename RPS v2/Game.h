#pragma once
#include "Input.h"
#include "Square.h"
#include "Player.h"
#include "EndGameData.h"
#include <Windows.h>
#include <fstream>


constexpr size_t lines = 10;
constexpr size_t colums = 10;

class Game {
	int delay = 0;
protected:
	class Square board[lines][colums];
public:
	Game();
	Game(int mSecs);
	void nullifyBoard();
	Square& getSquare(int y, int x) { return board[y][x]; }
	void run(Input* command, Player **players);
	void fileHandling(std::ifstream *inFile1, std::ifstream *inFile2);
	void deletePlayers(Player **arr);
	//position and printing board
	void positionPhase(Input* command, Player **players);
	void printBoard(Player **players) const;
	void setPawnsToBoard(Player *user);
	//moving pawns
	void moving(Input* command, Player **players);
	int fight(Square &current, Pawn **invader);
	int fight(Square &source, Square& destination);
	void move(Player *acting_player, Player *idle_player, Input *command, std::ifstream *inFile);
	bool checkPlayers(Square &current, Pawn **p);
};
