#pragma once 
#include "Point.h"
#include "EndGameData.h"
#include "Utils.h"
#include <iostream>
#include <string>


class Player;
class Rock;
class Paper;
class Scissor;
class Bomb;
class Joker;
class Flag;

class Pawn {
	Point location;
protected:
	Player *user;
	short* counter;
public:
	Pawn() {};
	Pawn(std::string coordinates, Player* ptr, short* type);
	virtual ~Pawn();
	inline Point getPoint() { return location; }
	void deleteTrace();
	void setPoint(std::string &destination);
	inline Player* getUser() { return user; }
	bool oneSquareMove(const std::string &moveCommand) const;

	virtual void setRep(char type) {};
	virtual char getPrint() = 0;
	virtual void print() = 0;
	virtual void setPrint(char rep = '?') = 0;
	virtual void move(const std::string &moveCommand) = 0;
	virtual int operator >> (Pawn &enemy) = 0;
	virtual int operator >> (Rock &enemy) = 0;
	virtual int operator >> (Paper &enemy) = 0;
	virtual int operator >> (Scissor &enemy) = 0;
	virtual int operator >> (Bomb &enemy) = 0;
	virtual int operator >> (Flag &enemy) = 0;
	virtual int operator >> (Joker &enemy) = 0;
	
	virtual void operator += (const std::string &moveCommand);

	enum type { rock = 'R', paper = 'P', scissor = 'S', joker = 'J', bomb = 'B', flag = 'F' };
};