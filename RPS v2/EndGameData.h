#pragma once
#include <string>

class Player;

class EndGameData {
	int reason = 0;
	char error_line;
	Player *whoDid = nullptr;
	Player *winner = nullptr;
	std::string ending_line;
public:
	EndGameData() { reason = Tie; };
	EndGameData(int num,Player* _whoDid) { reason = num; whoDid = _whoDid; }
	EndGameData(int num, Player* _whoDid, int _line) :reason(num), whoDid(_whoDid), error_line(_line) {};
	EndGameData(int num, Player *loser, Player *_winner) : reason(num), whoDid(loser), winner(_winner) {};
	int getReason() { return reason; }
	Player *getWhoDid() { return whoDid; }
	Player *getWinner() { return winner; }
	std::string& getString() { return ending_line; }
	void setString(std::string _line) { ending_line = _line; }
	char getLine() { return error_line; }
	void end_Game_Screen_output();
	enum Reasons {
		BadPositionFormat = 1, BadMovingFormat, tooManyPawns, twoOnSameSquare,
		BadSource, BadDestination, noJokerOnSquare, IllegalMove, noPosFiles, 
		noMoveFiles, allMobileDied, FlagCaptured,Tie };
};