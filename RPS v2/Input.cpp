#include "Input.h"


bool Input::checkPositionLine(std::string &temp) {
	//checks position line and eliminates spaces
	char write = 0;
	int index = 0;
	index += skipSpaces(temp);
	if (checkPawnType(temp[index])) { //check if Type is correct
		temp[write++] = temp[index++];
		for (size_t i = 0; i < 2; i++){
			if (!numberAnalyzing(index, write, temp))//check two numbers of placing
				return false;
		}
		index += skipSpaces(temp.substr(index));
		if (temp[0] != 'J' && temp[index] == '\0'){
			temp.resize(write);
			return true ;
		}//non joker Pawn
		return (jokerTypeAnalyzing(index, write, temp));//checks type of joker
	}//if
	return false;
}//checkPosLine
int Input::skipSpaces(std::string &temp) {
	//skip spaces and return index
	int index = 0;
	while (temp[index] == ' '){
		index++;
	}
	return index;
}//skip spaces
bool Input::numberAnalyzing(int &index, char &write, std::string &temp) {
	//Auxiliary function for checking numbers in text lines
	index += skipSpaces(temp.substr(index));
	int num = checkNum(temp, index);//checks number
	if (num == 0)
		return false;
	num -= 1;//decrease one for matrix
	temp[write++] = num + '0';//inser string
	return true;
}//numSection
bool Input::jokerTypeAnalyzing(int &index, char &write, std::string &temp) {
	//checks Type of Joker
	index += skipSpaces(temp.substr(index));
	if (!checkJokerType(temp[index]))//checks type
		return false;
	temp[write] = temp[index];//insert string
	temp.resize(++write);
	return true;
}//typeSection
bool Input::checkPawnType(char ch) const {
	//check if right letter is written in line.
	return (ch == Pawn::type::bomb || ch == Pawn::type::flag || ch == Pawn::type::paper
		|| ch == Pawn::type::rock || ch == Pawn::type::scissor || ch == Pawn::type::joker);
}//checkType
bool Input::checkJokerType(char ch) const {
	//checks if type for joker is valid
	return (ch == Pawn::rock || ch == Pawn::paper || ch == Pawn::bomb || ch == Pawn::scissor);
}//checkJokerType
int Input::checkNum(std::string &temp, int &index) const {
	//translates and checks if number is no higher than 10
	int num = 0;
	while (temp[index] != ' ' && temp[index] != '\0')
	{
		if (temp[index] >= '0' && temp[index] <= '9')
		{
			num *= 10;
			num += temp[index] - '0';
		}
		index++;
	}
	if (num >= 1 && num <= 10)
		return num;
	//general::indication = general::BadMovingFormat;
	return 0;
}//checkNum
int Input::parseInt(char argv[]) {
	//translates characters to int
	int index = 0, num = 0;
	while (argv[index] != '\0'){
		num *= 10;
		num += argv[index++] - '0';
	}
	return num;
}//parseInt
bool Input::checkMoveLine(std::string &temp) {
	int index = 0;
	char write = 0;
	index = skipSpaces(temp);
	for (size_t i = 0; i < 4; i++){
		if (!numberAnalyzing(index, write, temp))//checks 4 numbers of moving
			return(false);
	}
	index += skipSpaces(temp.substr(index));
	if (temp[index] == '\0')//non joker 
	{
		temp.resize(write);
		return(true);
	}
	if (analyzeJokerCommand(index, write, temp))//analyzes joker changing command
		return(true);
	//general::indication = general::BadMovingFormat;
	return(false);
}//checkMoveLine
bool Input::analyzeJokerCommand(int &index, char &write, std::string &temp) {
	//checks joker changing line
	if (temp[index++] == 'J')
	{
		index += skipSpaces(temp.substr(index));
		if (temp[index++] == ':')
		{
			for (size_t i = 0; i < 2; i++){
				if (!numberAnalyzing(index, write, temp))//checks numbers
					return false;
			}
			return jokerTypeAnalyzing(index, write, temp);//checks type
		}
	}
	return false;
}//analyzeJokerCommand