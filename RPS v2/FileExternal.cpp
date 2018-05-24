#include "FileExternal.h"

std::vector<std::string>** const FileExternal::getPositions(Player **user)
{//gets positioning files from both users and insert each line into vector
	std::vector<std::string> **positions = new std::vector<std::string>*[numOfPlayers];
	positions[0] = getPositionsFromPlayer(positions1, user[0]);
	positions[1] = getPositionsFromPlayer(positions2, user[1]);
	return(positions);
}//getPositions
std::vector<std::string>* FileExternal::getPositionsFromPlayer(const char* position_file, Player *user) {
	std::vector<std::string> *positions = new std::vector<std::string>;
	std::string temp;
	std::ifstream inFile;

	inFile.open(position_file);
	if (inFile.is_open()) {
		while (!inFile.eof()) {//goes thourgh 13 lines of defined number of pawns
			std::getline(inFile, temp);
			if (checkPositionLine(temp)) {//checks if format is correct, if so, push it inside the vector
				//unlike ConsoleInput, FileInput does not suggest second try
				positions->push_back(temp);
			}
			else {
				throw EndGameData(EndGameData::Reasons::BadPositionFormat, user, positions->size());
				//throws data with line number, and by who error was made.
			}
		}
	}
	else {
		throw EndGameData(EndGameData::Reasons::noPosFiles, user);
	}
	inFile.close();
	return(positions);
}//getPositions
std::string FileExternal::getMoveLine(std::ifstream *inFile, Player *user)
{//gets move line, checks if format is correct and modify it accordingly
	std::string temp;
	if (inFile->is_open())
	{
		std::getline(*inFile, temp);
		if (checkMoveLine(temp))
			return temp;
	}
	throw EndGameData(EndGameData::Reasons::BadMovingFormat, user);
	return temp;
}//getMoveLine
void FileExternal::writeOutput(EndGameData &fin, Game* current) {
	//outputfile for End game
	std::ofstream output;
	output.open("RPS.output");
	if (output.is_open()){
		output << fin.getString();//gets detailed information on who won, and why
	}
	output << "\n" << std::endl;
	if (current) {//checks if current is not nullptr since this function can be called even before Game was created.
		output << current;
	}
}//writeOutput
std::ofstream& operator<< (std::ofstream& out, Game *current) {
	//operator for printing the board's last state to output file.
	for (int i = 0; i <= 20; i++)
		out << "=";
	for (int index = 0; index < 10; index++)
	{
		out << '\n';
		for (int j = 0; j <= 9; j++)
		{
			out << "|";
			Pawn **_pawn = current->getSquare(index, j).getPawn();
			if (_pawn) {
				out << (*_pawn)->getPrint();
			}
			else {
				out << ' ';
			}
		}
		out << '|' << index + 1 << '\n';
		for (int i = 0; i <= 20; i++)
			out << "=";
	}
	out << '\n';
	for (int index = 0; index < 10; index++)
		out << " " << index + 1;
	return(out);
}//ofstream& << operator