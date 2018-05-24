#include "ConsoleInput.h"

const Point name_location(0, 11);
const Point joker_line(0, 12);

std::vector<std::string>** const ConsoleInput::getPositions(Player **user){
	//gets positioning line from each player and inserts it inside a vector
	//memory allocation - array of 2 pointers to vectors
	std::vector<std::string> **positions = new std::vector<std::string>*[2];
	positions[0] = new std::vector<std::string>;
	positions[1] = new std::vector<std::string>;
	std::cout << "Please Insert Pawn's Type, Coordinates seperated by spaces:" << std::endl;
	for (size_t index = 0; index < numOfPawns; index++){ //gets line,checks and modifies it accordingly
		insertPositionLine(positions[0],user[0]);
		insertPositionLine(positions[1],user[1]);
	}
	system("CLS");
	return positions;
}//getPositions
void ConsoleInput::insertPositionLine(std::vector<std::string>* position,Player *user) {
	std::string temp;
	std::cout << user->getName() << "'s Turn:";//current turn indication
	std::getline(std::cin, temp);
	if (checkPositionLine(temp) || correctPosition(temp)) {//checks if user entered line correctly, if user didn't
		//call correctPosition function, function will guide him how to write position line correctly.
		position->push_back(temp);
	}
	else {
		//throws EndGameData class with BadPositionFormat
		throw EndGameData(EndGameData::Reasons::BadPositionFormat, user,position->size());
	}
}//insertPositionLine
bool ConsoleInput::correctPosition(std::string &temp) {
	//helps the user insert correct position line in case the first try went wrong
	char dummy;
	temp.clear();
	std::cout << "Please enter Pawn's type:\n";
	getValue(temp);
	std::cout << "Please enter X coordinate:\n";
	getValue(temp);
	std::cout << "Please enter Y coordinate:\n";
	getValue(temp);
	if (temp[0] == 'J') {
		std::cout << "Please enter Joker's representation:\n";
		getValue(temp);
	}
	std::cin.get(dummy);
	return checkPositionLine(temp);
}//correctPosition
void ConsoleInput::getValue(std::string &temp) {
	//gets value from user and modify string so that checkPositionLine would work on.
	char ch;
	std::cin >> ch;
	temp.push_back(ch);
	temp += ' ';
}//getValue
std::string ConsoleInput::getMoveLine(std::ifstream *inFile, Player *user) {
	//gets move line from user, checks if written correctly.
	//also manages joker changing request by user
	const int turnAddition = 41;//for "'s .... press y" string length
	int size_move;
	std::string temp;
	//prints user's turn indication
	setTextColor(WHITE);
	gotoxyPoint(name_location);
	std::cout << user->getName() << "'s Turn,if you'd like to leave, press y:";
	//gets input
	std::getline(std::cin, temp);
	size_move = temp.size();
	check_leave_request(temp);
	if (checkMoveLine(temp)) {//checks if format is written correctly
		jokerLineAuxilliary(temp, user);//deals with joker changing request
		clearLines(size_move+user->getName().size() + turnAddition,name_location);//clear lines of user's turn indication
		setTextColor(user->getColor());
		return temp;
	}
	throw EndGameData(EndGameData::Reasons::BadMovingFormat, user);
	return temp;
}//getMoveLine
void ConsoleInput::jokerLineAuxilliary(std::string &temp,Player *user) {
	//function deals with the entire joker request part by user.
	//if user inserted joker changing request, function will stop at 'temp.size() != 7' because checkMoveLine modifies it 
	//to a 7 letter string. if user didn't insert a request, function will ask for it. Can be canceled by pressing Enter
	if (temp.size() != 7 && user->jokerCounting()) {
		const int joker_line_length = 72; //for "If ... else press Enter:" string length
		int index = 0, size_joker;
		char write = 0;
		std::string jokerAddition;
		//writes Joker request line and explnation
		gotoxyPoint(joker_line);
		std::cout << "If you'd like to, add command to change Joker's type, else press Enter:";//put extra attention on writing
		// "J:" at start of the string
		//gets input
 		std::getline(std::cin, jokerAddition);
		size_joker = jokerAddition.size();
		index += skipSpaces(jokerAddition);
		if (analyzeJokerCommand(index, write, jokerAddition)) {//analyze joker changing request and append it to move line
			temp += jokerAddition;
		}
		clearLines(size_joker+ joker_line_length, joker_line);//clears joker request line
	}
}//JokerLineAuxilliary
void ConsoleInput::clearLines(int sentence_length,Point p) {//clear lines according to a certain point and length
	gotoxyPoint(p);
	for (int index = 0; index < sentence_length; index++) {
		std::cout << ' ';
	}
}//clearLines
void ConsoleInput::check_leave_request(std::string &leave) {
	if (leave[0] == 'y') {
		throw EndGameData();
	}
}