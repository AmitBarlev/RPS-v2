#include "RPSJBF.h"

//rock =====================================================
//double dispatch for fighting
int Rock::operator >> (Pawn &enemy){
	setPrint();
	return -enemy.operator >> (*this);
}//operator >>
int Rock::operator >> (Rock &enemy) {
	return 0;
}//operator >>
int Rock::operator >> (Paper &enemy) {
	return -1;
}//operator >>
int Rock::operator >> (Scissor &enemy){
	setPrint();
	return 1;
}//operator >>
int Rock::operator >> (Bomb &enemy){
	return 0;
}//operator >>
int Rock::operator >> (Flag &enemy){
	setPrint();
	return 1;
}//operator >>
int Rock::operator >> (Joker &enemy){
	return -enemy.operator >> (*this);
}//operator >>
void Rock::move (const std::string &moveCommand) {
	//manages the entire moving process of pawn,deletes trace, sets new point and prints
	if (oneSquareMove(moveCommand)) {
		deleteTrace();
		setPoint(moveCommand.substr(2, 2));
		gotoxyPoint(getPoint());
		print();
	}
	else {
		throw EndGameData(EndGameData::Reasons::IllegalMove, getUser());
	}
}//move
void Rock::setPrint(char rep) {
	if (_print != ' ') {
		_print = rep;
	}
}
//paper relations ===================================================
int Paper::operator >> (Pawn &enemy){
	setPrint();
	return -enemy.operator >> (*this);
}//operator >>
int Paper::operator >> (Rock &enemy){
	setPrint();
	return 1;
}//operator >>
int Paper::operator >>  (Paper &enemy){
	return 0;
}//operator >>
int Paper::operator >> (Scissor &enemy){
	return -1;
}//operator >>
int Paper::operator >> (Bomb &enemy){
	return 0;
}//operator >>
int Paper::operator >> (Flag &enemy){
	setPrint();
	return 1;
}//operator >>
int Paper::operator >> (Joker &enemy){
	return -enemy.operator >> (*this);
}//operator >>
void Paper::move (const std::string &moveCommand) {
	//manages the entire moving process of pawn,deletes trace, sets new point and prints
	if (oneSquareMove(moveCommand)) {
		gotoxyPoint(getPoint());
		std::cout << ' ';
		setPoint(moveCommand.substr(2, 2));
		gotoxyPoint(getPoint());
		print();
	}
	else {
		throw EndGameData(EndGameData::Reasons::IllegalMove, getUser());
	}
}//move
void Paper::setPrint(char rep) {
	if (_print != ' ') {
		_print = rep;
	}
}
//scissor relations ================================================
int Scissor::operator >> (Pawn &enemy) {
	setPrint();
	return -enemy.operator >> (*this);
}//operator >>
int Scissor::operator >> (Rock &enemy) {
	return -1;
}//operator >>
int Scissor::operator >> (Paper &enemy) {
	setPrint();
	return 1;
}//operator >>
int Scissor::operator >> (Scissor &enemy) {
	return 0;
}//operator >>
int Scissor::operator >> (Bomb &enemy) {
	return 0;
}//operator >>
int Scissor::operator >> (Flag &enemy) {
	setPrint();
	return 1;
}//operator >>
int Scissor::operator >> (Joker &enemy) {
	setPrint();
	return -enemy.operator >> (*this);
}//operator >>
void Scissor::move (const std::string &moveCommand) {
	//manages the entire moving process of pawn,deletes trace, sets new point and prints
	if (oneSquareMove(moveCommand)) {
		gotoxyPoint(getPoint());
		std::cout << ' ';
		setPoint(moveCommand.substr(2, 2));
		gotoxyPoint(getPoint());
		print();
	}
	else {
		throw EndGameData(EndGameData::Reasons::IllegalMove, getUser());
	}
}//move
void Scissor::setPrint(char rep) {
	if (_print != ' ') {
		_print = rep;
	}
}
//bomb relations ================================================
int Bomb::operator >> (Pawn &enemy) {
	return -enemy.operator >> (*this);
}//operator >>
int Bomb::operator >> (Rock &enemy) {
	return 0;
}//operator >>
int Bomb::operator >> (Paper &enemy) {
	return 0;
}//operator >>
int Bomb::operator >> (Scissor &enemy) {
	return 0;
}//operator >>
int Bomb::operator >> (Bomb &enemy) {
	return 0;
}//operator >>
int Bomb::operator >> (Flag &enemy) {
	return 0;
}//operator >>
int Bomb::operator >> (Joker &enemy) {
	return 0;
}//operator >>
void Bomb::move (const std::string &moveCommand) {//bomb is not allowed to move, illegal move
	throw EndGameData(EndGameData::Reasons::IllegalMove, getUser());
}//move
void Bomb::setPrint(char rep) {
	if (_print != ' ') {
		_print = rep;
	}
}
// flag relations ===================================================
int Flag::operator >> (Pawn &enemy) {
	return -enemy.operator >> (*this);
}//operator >>
int Flag::operator >> (Rock &enemy) {
	return -1;
}//operator >>
int Flag::operator >> (Paper &enemy) {
	return -1;
}//operator >>
int Flag::operator >> (Scissor &enemy) {
	return -1;
}//operator >>
int Flag::operator >> (Bomb &enemy) {
	return -1;
}//operator >>
int Flag::operator >> (Flag &enemy) {
	return -1;
}//operator >>
int Flag::operator >> (Joker &enemy) {
	return -1;
}//operator >>
void Flag::move (const std::string &moveCommand) {//flag is not allowed to move, illegal move
	throw EndGameData(EndGameData::Reasons::IllegalMove, getUser());
}//move
void Flag::setPrint(char rep) {
	if (_print != ' ') {
		_print = rep;
	}
}
// Joker ==============================================================================
Joker::Joker(std::string location, char type, Player* user, short* counter) : Pawn (location, user, counter){
	//constructor, sets point,owner and counter, also sets initial representation
	setRep(type);
}//Joker
void Joker::setRep(char type) {
	//sets representation according to the character user has inserted
	switch (type) {
	case (Pawn::rock): {
		setPrintJoker('r');
		representation = &jan;
		break;
	}
	case (Pawn::paper): {
		setPrintJoker('p');
		representation = &ken;
		break;
	}
	case (Pawn::scissor): {
		setPrintJoker('s');
		representation = &pon;
		break;
	}
	case (Pawn::bomb): {
		setPrintJoker('b');
		representation = &genthru;
		break;
	}
	}
}//setRep
int Joker::operator >> (Pawn &enemy) {
	setPrint(representation->getPrint() + 32);
	return representation->operator>> (enemy);
}//operator >>
int Joker::operator >> (Rock &enemy) {
	setPrint(representation->getPrint() + 32);
	return representation->operator>> (enemy);
}//operator >>
int Joker::operator >> (Paper &enemy) {
	setPrint(representation->getPrint() + 32);
	return representation->operator>> (enemy);
}//operator >>
int Joker::operator >> (Scissor &enemy) {
	setPrint(representation->getPrint() + 32);
	return representation->operator>> (enemy);
}//operator >>
int Joker::operator >> (Bomb &enemy) {
	setPrint(representation->getPrint() + 32);
	return representation->operator>> (enemy);
}//operator >>
int Joker::operator >> (Flag &enemy) {
	setPrint(representation->getPrint() + 32);
	return representation->operator>> (enemy);
}//operator >>
int Joker::operator >> (Joker &enemy) {
	setPrint(representation->getPrint()+32);
	return representation->operator>> (enemy);
}//operator >>
void Joker::move (const std::string &moveCommand) {
	//manages the entire moving process of pawn,deletes trace, sets new point and prints
	//checks if current representation is not bomb
	if (representation != &genthru && oneSquareMove(moveCommand)) {
		gotoxyPoint(getPoint());
		deleteTrace();
		setPoint(moveCommand.substr(2, 2));
		gotoxyPoint(getPoint());
		print();
	}
	else {
		throw EndGameData(EndGameData::Reasons::IllegalMove, getUser());
	}
}//move
void Joker::operator += (const std::string &moveCommand) {
		setRep(moveCommand[2]);
		gotoxyPoint(getPoint());
		print();
}//operator +=
void Joker::setPrintJoker(char rep) {
	if (_print != '?' && _print != ' ') {
		_print = rep;
	}
}//setPrintCompetative
void Joker::setPrint(char rep) {
	if (_print != ' ') {
		_print = rep;
	}
}