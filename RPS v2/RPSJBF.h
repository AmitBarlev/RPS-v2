#pragma once
#include "Pawn.h"
#include "Utils.h"
#include "EndGameData.h"


struct PawnCounter;
class Game;

class Rock : public Pawn {
	char _print = 'R';
public:
	Rock() {};
	Rock(std::string location, Player* user, short* counter) : Pawn (location, user,counter) {}

	virtual char getPrint() override { return _print; }
	virtual void print()  override {std::cout << _print; }
	virtual void setPrint(char rep = 'R')  override;
	virtual int operator >> (Pawn &enemy) override;
	virtual int operator >> (Rock &enemy) override;
	virtual int operator >> (Paper &enemy) override;
	virtual int operator >> (Scissor &enemy) override;
	virtual int operator >> (Bomb &enemy) override;
	virtual int operator >> (Flag &enemy) override;
	virtual int operator >> (Joker &enemy) override;
	virtual void move (const std::string &moveCommand) override;
};

class Paper : public Pawn {
	char _print = 'P';
public:
	Paper() {};
	Paper(std::string location, Player* user, short* counter) : Pawn(location, user, counter) {}

	virtual char getPrint() override { return _print; }
	virtual void print()  override { std::cout << _print; }
	virtual void setPrint(char rep = 'P')  override;
	virtual int operator >> (Pawn &enemy) override;
	virtual int operator >> (Rock &enemy) override;
	virtual int operator >> (Paper &enemy) override;
	virtual int operator >> (Scissor &enemy) override;
	virtual int operator >> (Bomb &enemy) override;
	virtual int operator >> (Flag &enemy) override;
	virtual int operator >> (Joker &enemy) override;
	virtual void move (const std::string &moveCommand) override;
};

class Scissor : public Pawn {
	char _print = 'S';
public:
	Scissor() {};
	Scissor(std::string location, Player* user, short* counter) : Pawn(location, user, counter) {}
	virtual char getPrint() override { return _print; }
	virtual void print()  override { std::cout << _print; }
	virtual void setPrint(char rep = 'S')  override;
	virtual int operator >> (Pawn &enemy) override;
	virtual int operator >> (Rock &enemy) override;
	virtual int operator >> (Paper &enemy) override;
	virtual int operator >> (Scissor &enemy) override;
	virtual int operator >> (Bomb &enemy) override;
	virtual int operator >> (Flag &enemy) override;
	virtual int operator >> (Joker &enemy) override;
	virtual void move (const std::string &moveCommand) override;
};

class Bomb : public Pawn {
	char _print = 'B';
public:
	Bomb() {};
	Bomb(std::string location, Player* user, short* counter) : Pawn (location, user, counter) {};

	virtual char getPrint() override { return _print; }
	virtual void print()  override { std::cout << _print; }
	virtual void setPrint(char rep = 'B')  override;
	virtual int operator >> (Pawn &enemy) override;
	virtual int operator >> (Rock &enemy) override;
	virtual int operator >> (Paper &enemy) override;
	virtual int operator >> (Scissor &enemy) override;
	virtual int operator >> (Bomb &enemy) override;
	virtual int operator >> (Flag &enemy) override;
	virtual int operator >> (Joker &enemy) override;
	virtual void move (const std::string &moveCommand) override;
};

class Joker: public Pawn {
	char _print;
	Pawn *representation;
	Rock jan;
	Paper ken;
	Scissor pon;
	Bomb genthru;

public:
	Joker() {};
	Joker(std::string location, char type, Player* user, short* counter);
	void setPrintJoker(char rep);
	
	
	virtual void setRep(char type)  override;
	virtual char getPrint() override { return _print; }
	virtual void print()  override { std::cout << _print; }
	virtual void setPrint(char rep)  override;
	virtual int operator >> (Pawn &enemy) override;
	virtual int operator >> (Rock &enemy) override;
	virtual int operator >> (Paper &enemy) override;
	virtual int operator >> (Scissor &enemy) override;
	virtual int operator >> (Bomb &enemy) override;
	virtual int operator >> (Flag &enemy) override;
	virtual int operator >> (Joker &enemy) override;
	virtual void move (const std::string &moveCommand) override;
	virtual void operator += (const std::string &moveCommand);
};

class Flag : public Pawn {
	char _print = 'F';
public:
	Flag() {};
	Flag(std::string location, Player* user, short* counter) : Pawn (location, user, counter) {};

	virtual char getPrint() override { return _print; }
	virtual void print()  override { std::cout << _print; }
	virtual void setPrint(char rep = 'F')  override;
	virtual int operator >> (Pawn &enemy) override;
	virtual int operator >> (Rock &enemy) override;
	virtual int operator >> (Paper &enemy) override;
	virtual int operator >> (Scissor &enemy) override;
	virtual int operator >> (Bomb &enemy) override;
	virtual int operator >> (Flag &enemy) override;
	virtual int operator >> (Joker &enemy) override;
	virtual void move (const std::string &moveCommand) override;
};