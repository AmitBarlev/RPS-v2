#pragma once
#include "Pawn.h"

Pawn::Pawn(std::string coordinates, Player *ptr, short* type) {
	//constructor, sets point, owner and counter
	setPoint(coordinates);
	user = ptr;
	counter = type;
}//Pawn
Pawn::~Pawn() {//destructor, decrease counter
	if (counter) {
		*counter -= 1;
	}
}//~Pawn
void Pawn::setPoint(std::string &destination) {
	location.setX(destination[0] - '0');
	location.setY(destination[1] - '0');
}//setPoint
bool Pawn::oneSquareMove(const std::string &moveCommand) const {
	//checks if no diagonal move were made, or trying to skip squares
	return	moveCommand[0] + 1 == moveCommand[2] && moveCommand[1] == moveCommand[3]||
		moveCommand[0] == moveCommand[2] && moveCommand[1] == moveCommand[3] + 1 ||
		moveCommand[0] - 1 == moveCommand[2] && moveCommand[1] == moveCommand[3] ||
			moveCommand[0] == moveCommand[2] && moveCommand[1] == moveCommand[3] - 1;
}//oneSquareMove
void Pawn::deleteTrace() {//deletes where pawn has been to
	gotoxyPoint(getPoint());
	std::cout << ' ';
}//deleteTrace
void Pawn::operator += (const std::string &moveCommand) {//operator to change joker representation
	throw EndGameData(EndGameData::Reasons::noJokerOnSquare, getUser());
}//operator +=