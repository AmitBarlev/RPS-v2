#pragma once
#include "Input.h"
#include "Player.h"
#include <string>
#include <vector>


class ConsoleInput : public Input {

public:

	void insertPositionLine(std::vector<std::string>* position, Player *user);
	bool correctPosition(std::string &temp);
	void getValue(std::string &temp);
	void jokerLineAuxilliary(std::string &temp, Player *user); 
	void clearLines(int sentence_length, Point p);
	void check_leave_request(std::string &leave);

	virtual void writeOutput(EndGameData &fin, Game* current) {};
	virtual std::vector<std::string>** const getPositions(Player **user) override;
	virtual std::string getMoveLine(std::ifstream *inFile, Player *user) override;
	virtual bool keepMoving(std::ifstream *inFile1, std::ifstream *inFile2) override { return true; }
	virtual bool keepMovingSingle(std::ifstream *inFile) override { return false; }
};