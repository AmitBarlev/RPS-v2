#pragma once
#include "Player.h"

Player::Player(Color dye) {//constructor, gets user name,allocates counters for pawns
	std::cout << "Please Enter Player Name: ";
	std::getline(std::cin, name);
	allocateCounters();
	_color = dye;
}//Player
Player::~Player() {//destructor, delete pawns
	for (int i = 0; i < numOfPawns; i++)
		if (pawns[i]) {
			delete(pawns[i]);
		}
	deleteCounter();
}//~Player
void Player::deleteCounter() {
	delete(counter.bomb);
	delete(counter.flag);
	delete(counter.paper);
	delete(counter.joker);
	delete(counter.rock);
	delete(counter.scissor);
}
void Player::setPawns(std::vector<std::string> &positions) {//gets a vector of strings, creates and places pawns according to
	for (size_t i = 0; i < positions.size(); i++) {
		createPawn(positions[i], pawns[i]);
	}
	checkPawnCounter();
}//setPawns
void Player::allocateCounters() {
	//allocates counter and insert values
	counter.bomb = new short;
	*counter.bomb = 0;
	counter.flag = new short;
	*counter.flag = 0;
	counter.joker = new short;
	*counter.joker = 0;
	counter.scissor = new short;
	*counter.scissor = 0;
	counter.paper = new short;
	*counter.paper = 0;
	counter.rock = new short;
	*counter.rock = 0;
}//allocateCounters
void Player::createPawn(std::string pawnLine, Pawn *&index) {
	//allocates pawn according to pawnLine
	switch (pawnLine[0]){
	case (Pawn::paper): {
		*counter.paper += 1;
		index = new Paper(pawnLine.substr(1, 2),this,counter.paper);
		break;
	}
	case (Pawn::rock): {
		*counter.rock += 1;
		index = new Rock(pawnLine.substr(1, 2),this,counter.rock);
		break;
	}
	case (Pawn::scissor): {
		*counter.scissor += 1;
		index = new Scissor(pawnLine.substr(1, 2),this,counter.scissor);
		break;
	}
	case (Pawn::bomb): {
		*counter.bomb += 1;
		index = new Bomb(pawnLine.substr(1, 2),this,counter.bomb);
		break;
	}
	case (Pawn::joker): {
		*counter.joker += 1;
		index = new Joker(pawnLine.substr(1, 2),pawnLine[3],this,counter.joker);
		break;
	}
	case (Pawn::flag): {
		*counter.flag += 1;
		index = new Flag(pawnLine.substr(1, 2),this,counter.flag);
		break;
	}
	}
}//setPawn
void Player::setPrints(char rep) {//sets prints according to gameMode
	for (size_t i = 0; i < numOfPawns; i++) {
		if (pawns[i]) {
			pawns[i]->setPrint(rep);
		}
	}
}//setPrints
void Player::printPawns() const {//print all pawns 
	setTextColor(_color);
	for (size_t i = 0; i < numOfPawns; i++) {
		if (pawns[i]) {
			gotoxyPoint(pawns[i]->getPoint());
			pawns[i]->print();
		}
	}
}//printPawns
void Player::checkPawnCounter() {//checks if counter is not according to what's been defined
	if (*counter.rock > 2 || *counter.paper > 5 || *counter.scissor > 1 ||
		*counter.joker > 2 || *counter.bomb > 2 || *counter.flag != 1) {
		throw EndGameData(EndGameData::Reasons::tooManyPawns, this);
	}
}//checkPawnCounter
bool Player::checkFlagCounter() {
	return *counter.flag == 1;
}
char Player::counterSumMobile() const {
	return ( *counter.joker + *counter.scissor + *counter.paper + *counter.rock);
}//counterSum
char Player::counterSum() const {
	return (counterSumMobile() + *counter.bomb + *counter.flag);
}
void Player::checkWinCondition(Player *winner) {
	//checks condition for user's winning
	if (getFlagCounter() == 0) {
		throw EndGameData(EndGameData::Reasons::FlagCaptured,this,winner);
	}
	if (counterSumMobile() == 0) {
		throw EndGameData(EndGameData::Reasons::allMobileDied, this, winner);
	}
}//checkWinCondition
void Player::deletePawn(Pawn **pawn) {
	(*pawn)->deleteTrace();
	delete(*pawn);
	*pawn = nullptr;
}//deletePawn
void Player::move(std::string &moveCommand, Game *current) {
	//checks if user has inserted a correct location of pawn he wants to move
	Square& source = current->getSquare(moveCommand[1] - '0', moveCommand[0] - '0');
	Square& destination = current->getSquare(moveCommand[3] - '0', moveCommand[2] - '0');
	jokerChange(moveCommand, current);
	if (source.isSquareOccupied() && source.getUser() == this) {//checks if square is occupied by 
		//another pawn and if the user is the same
		destinationHandler(source, destination, current, moveCommand);
	}
	else {
		throw EndGameData(EndGameData::Reasons::BadSource, this);
	}
}//move
void Player::destinationHandler(Square &source, Square &destination, Game *current, std::string &moveCommand) {
	//checks if destination is occupied, if not, move pawn to destination
	Pawn **moving_pawn = source.getPawn();
	if (destination.isSquareOccupied()) {
		destionationOccupied(source, destination, current, moveCommand);
	}
	else {
		source.wipe();
		(*moving_pawn)->move(moveCommand);
		destination.setPawn(moving_pawn);
	}
}//destinationHandler
void Player::destionationOccupied(Square &source, Square &destination, Game *current, std::string &moveCommand) {
	//checks if destination is occupied by an enemy or by another pawn of the same player
	Pawn **moving_pawn = source.getPawn();
	if (source.getUser() == destination.getUser()) {
		throw EndGameData(EndGameData::Reasons::BadDestination, this);
	}
	else {//occupied by an enemy
		if (current->fight(source,destination) == 1) {
			(*moving_pawn)->move(moveCommand);
		}
	}
}//destionationOccupied
void Player::jokerChange(std::string &moveCommand,Game* current) {
	//function that manages joker's entire process of changing state 
	if (moveCommand.size() == 7) {
		char x = moveCommand[4] - '0';
		char y = moveCommand[5] - '0';
		Pawn **mrJ = current->getSquare(y, x).getPawn();
		if (mrJ && (*mrJ)->getUser() == this) {//if square is occupied
			**mrJ += moveCommand.substr(4, 3);//operator to change joker
		}
		else {
			throw EndGameData(EndGameData::Reasons::noJokerOnSquare, this);
		}
	}
}//jokerChange