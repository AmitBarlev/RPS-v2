#pragma once
#include "Input.h"
#include "Game.h"
#include <string>
#include <vector>
#include <fstream>

constexpr char* positions1 = "player1.rps_board";
constexpr char* positions2 = "player2.rps_board";
constexpr char* moveFile1 = "player1.rps_moves";
constexpr char* moveFile2 = "player2.rps_moves";
constexpr size_t posLineLength = 10;//maximum size
constexpr size_t moveLineLength = 16;//maximum size
constexpr size_t numOfPlayers = 2;


class FileExternal: public Input {
	
	std::string moveCommand;
public :
	void writeOutput(EndGameData &fin, Game* current);
	std::vector<std::string>* getPositionsFromPlayer(const char* position_file, Player *user);
	friend std::ofstream& operator<< (std::ofstream& out, Game *current);

	virtual std::vector<std::string>** const getPositions(Player **user) override;
	virtual std::string getMoveLine(std::ifstream *inFile, Player *user) override;
	virtual bool keepMoving(std::ifstream *inFile1, std::ifstream *inFile2) override
	{ return !inFile1->eof() && !inFile2->eof(); }
	virtual bool keepMovingSingle(std::ifstream *inFile) override { return !inFile->eof(); }

};