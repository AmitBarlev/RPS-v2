#include "Game.h"
Game::Game() {
	nullifyBoard();
}
Game::Game(int mSecs) {
	//constructor, insert values such as delay, and nullifies every square on board data-member
	delay = mSecs;
	nullifyBoard();
}//Game
void Game::nullifyBoard() {
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 10; j++) {
			board[i][j].setPawn(nullptr);
		}
	}
}
void Game::run(Input* command, Player **players) {
	try {
		positionPhase(command, players);
		moving(command, players);
	}
	catch (EndGameData &fin) {
		fin.end_Game_Screen_output();
		command->writeOutput(fin, this);
		deletePlayers(players);
		return;
	}
}//run
void Game::positionPhase(Input* command, Player **players) {
	//sets pawns to board and check for possible clashes 
	setPawnsToBoard(players[0]);
	setPawnsToBoard(players[1]);
	printBoard(players);
}//positionPhase
void Game::moving(Input* command, Player **players) {
	//manages the entire moving section
	std::ifstream *inFile1 = new std::ifstream;
	std::ifstream *inFile2 = new std::ifstream;
	inFile1->open(moveFile1);
	inFile2->open(moveFile2);
	try {
		while (command->keepMoving(inFile1, inFile2)) {
			//when both players can move
			move(players[0], players[1], command, inFile1);
			move(players[1], players[0], command, inFile2);
		}
		//single player moves
		while (command->keepMovingSingle(inFile1)) {
			move(players[0], players[1], command, inFile1);
		}
		while (command->keepMovingSingle(inFile2)) {
			move(players[1], players[0], command, inFile2);
		}
		throw EndGameData();
	}
	catch (EndGameData &fin) {
		fileHandling(inFile1, inFile2);
		throw fin;
	}
}//moving
void Game::printBoard(Player **players) const {
	//prints board.
	gotoxy(0, 0);
	for (int i = 0; i <= 20; i++) {
		std::cout << "=";
	}
	for (int index = 0; index < 10; index++) {
		std::cout << std::endl;
		for (int j = 0; j <= 10; j++) {
			std::cout << "| ";
		}
		std::cout << index + 1 << std::endl;
		for (int i = 0; i <= 20; i++) {
			std::cout << "=";
		}
	}
	std::cout << std::endl;
	for (int index = 0; index < 10; index++) {
		std::cout << " " << index + 1;
	}
	players[0]->printPawns();
	players[1]->printPawns();
}//printboard
void Game::fileHandling(std::ifstream *inFile1, std::ifstream *inFile2) {
	inFile1->close();
	inFile2->close();
	delete(inFile1);
	delete(inFile2);
}
void Game::setPawnsToBoard(Player *user) {
	//sets player's pawns to board and checks for possible clashes
	Pawn  **arr = user->getPawns();
	Point temp;
	char x, y;
	size_t pawns = user->counterSum();
	for (size_t i = 0; i < pawns; i++){
		//gets wanted location on board
		temp = arr[i]->getPoint();
		x = temp.getX() ;
		y = temp.getY() ;
		Square &current = board[y][x];
			if (current.isSquareOccupied()) {
				if (checkPlayers(current, &arr[i])) {//checks if player has placeed two pawns on the same square 
					throw EndGameData(EndGameData::Reasons::twoOnSameSquare, user);
				}
				else {//if both players placed pawn on a certain square, call fight function
					fight(current, &arr[i]);
				}
			}
			else {
				current.setPawn(&arr[i]);
			}
	}
}//setPawnsToBoard
int Game::fight(Square &current,Pawn **invader) {
	//manages the entire fighting process
	//function used in setPawnsToBoard
	Pawn &current_pawn = **current.getPawn();
	Pawn &invader_pawn = **invader;
	switch (current_pawn >> invader_pawn) {//fighting operator
	case 1: { // if LHS has won
		invader_pawn.getUser()->deletePawn(invader);
		return 1;
	}
	case 0: { //tie, both die
		invader_pawn.getUser()->deletePawn(invader);
		current_pawn.getUser()->deletePawn(current.getPawn());
		current.wipe();
		return 0;
	}
	case -1: { // if RHS has won
		current_pawn.getUser()->deletePawn(current.getPawn());
		current.setPawn(invader);
		return -1;
	}
	}
	return 0;
}//fight
int Game::fight(Square &source, Square& destination) {
	//manages the entire fighting process
	//function used in move
	Pawn &source_pawn = **source.getPawn();
	Pawn &destination_pawn = **destination.getPawn();
	switch (source_pawn >> destination_pawn) {//fighting operator
	case 1: {// if LHS has won
		destination.getUser()->deletePawn(destination.getPawn());
		destination.setPawn(source.getPawn());
		source.wipe();
		return 1;
	}
	case 0: { //tie, both die
		destination.getUser()->deletePawn(destination.getPawn());
		source.getUser()->deletePawn(source.getPawn());
		destination.wipe();
		source.wipe();
		return 0;
	}
	case -1: {//if RHS has won
		source.getUser()->deletePawn(source.getPawn());
		source.wipe();
		return -1;
	}
	}
	return 0;
}//fight
bool Game::checkPlayers(Square &current, Pawn **p) {
	return current.getUser() == (*p)->getUser();
}//checkPlayers
void Game::move(Player *acting_player,Player *idle_player, Input *command, std::ifstream *inFile) {
	//manages the entire moving process - asking player for input.
	//moving it across and board and checks if player has won
	setTextColor(acting_player->getColor());
	acting_player->move(command->getMoveLine(inFile, acting_player), this);
	acting_player->checkWinCondition(idle_player);
	idle_player->checkWinCondition(acting_player);
	Sleep(delay);
}//move
void Game::deletePlayers(Player **arr) {
	delete(arr[0]);
	delete(arr[1]);
	delete(arr);
}