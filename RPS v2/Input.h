#pragma once
#include "RPSJBF.h"
#include <iostream>
#include <vector>


class Input {

public:
	bool checkPositionLine(std::string &temp);
	int skipSpaces(std::string &temp);
	bool numberAnalyzing(int &index, char &write, std::string &temp);
	bool jokerTypeAnalyzing(int &index, char &write, std::string &temp);
	bool checkPawnType(char ch) const;
	bool checkJokerType(char ch) const;
	int checkNum(std::string &temp, int &index) const;
	bool checkMoveLine(std::string &temp);
	bool analyzeJokerCommand(int &index, char &write, std::string &temp);
	static int parseInt(char argv[]);
	
	virtual void writeOutput(EndGameData &fin, Game* current) = 0;
	virtual std::vector<std::string>** const getPositions(Player **user) = 0;
	virtual std::string getMoveLine(std::ifstream *inFile, Player *user) = 0;
	virtual bool keepMoving(std::ifstream *inFile1, std::ifstream *inFile2) = 0;
	virtual bool keepMovingSingle(std::ifstream *inFile) = 0;
};