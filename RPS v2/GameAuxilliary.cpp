#include "GameAuxilliary.h"

void GameAuxilliary::newGame(int argc, char *argv[]) {
	//translates command line arguments and create game accordingly
	int* parameters = getParameters(argc, argv);//creates a array of parameters to create game according to
	Input* command = whichInput(parameters[1]);
	Player **users = preparePlayers(command);
	if (!users) {
		return;
	}
	Game* Jajanken = initializeGame(parameters, users);
	Jajanken->run(command, users);
	delete(Jajanken);
}//newGame
int GameAuxilliary::whichMode(char* argv[], int &index) {
	//checks which mode user has asked for, default it -show-all
	if (strcmp(argv[index], "-show-all") == 0) {
		return 0;
	}
	else if (strcmp(argv[index], "-quiet") == 0) {
		return 1;
	}
	else if (strcmp(argv[index], "-show-only-known-info") == 0) {
		return 2;
	}
	else if (strcmp(argv[index++], "-show") == 0) {
		if (strcmp(argv[index], "1") == 0) {
			return 3;
		}
		else if (strcmp(argv[index], "2") == 0) {
			return 4;
		}
	}
	return 0;
}//whichMode
int* GameAuxilliary::getParameters(int argc, char* argv[]) {
	//gets command line arguments, inserts them to a defined indexes 
	int *gameParameters = new int[parameters];
	gameParameters[0] = 0;
	gameParameters[1] = 0;
	gameParameters[2] = 50;
	//index 0 is for gameMode,index 1 is for console or file,index 2 is for delay 
	//default is -show-all,file,50 mili seconds delay
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-delay") == 0) {
			gameParameters[2] = Input::parseInt(argv[++i]);
		}
		else if (strcmp(argv[i], "-console") == 0) {
			gameParameters[1] = 1;
		}
		else {
			if (gameParameters[0] != 0) {
				gameParameters[0] = 0;
			}
			else {
				gameParameters[0] = whichMode(argv, i);
			}
		}
	}
	return gameParameters;
}//getParameters
Game* GameAuxilliary::initializeGame(int *parameters, Player **players) {
	//allocates game type according to user's request
	Game *Jajanken = nullptr;
	switch (parameters[0]) {
	case 0: {
		Jajanken = new PresentationMode(parameters[2]);
		break;
	}
	case 1: {
		Jajanken = new QuietMode(players);
		break;
	}
	case 2: {
		Jajanken = new CompetativeMode(parameters[2], players);
		break;
	}
	case 3: {
		Jajanken = new OneSideComp(parameters[2], 0, players);
		break;
	}
	case 4: {
		Jajanken = new OneSideComp(parameters[2], 1, players);
		break;
	}
	}
	return Jajanken;
}//initializeGame
Input* GameAuxilliary::whichInput(int which) {
	//allocates console input or file input
	Input *command;
	if (which == 1) {
		command = new ConsoleInput;
	}
	else {
		command = new FileExternal;
	}
	return command;
}//whichInput
Player** GameAuxilliary::preparePlayers(Input* command) {
	//allocates array of 2 pointers of players
	Player **players = new Player*[numOfPlayers];
	players[0] = new Player(LIGHTCYAN);//constructor
	players[1] = new Player(RED);//constructor
	std::vector<std::string> **positions = nullptr;
	try {
		positions = command->getPositions(players);//gets pawns lines from both files/users
		players[0]->setPawns(*positions[0]);//sets pawns to user
		players[1]->setPawns(*positions[1]);//sets pawns to user
	}
	catch (EndGameData &fin) {
		fin.end_Game_Screen_output();
		command->writeOutput(fin, nullptr);
		deletePlayers(players);
		return nullptr;
	}	
	system("CLS");
	return players;
}//preparePlayers
void GameAuxilliary::deletePlayers(Player **arr) {
	delete(arr[0]);
	delete(arr[1]);
	delete(arr);
}
void EndGameData::end_Game_Screen_output() {
	//prints a summary line of how and why the game has ended
	Player *whoDid = getWhoDid();
	Player *winner = getWinner();
	std::string &output = getString();
	setTextColor(WHITE);
	system("CLS");
	switch (getReason()) {
	case 1: {
		output += "Wrong position format has been written by " + whoDid->getName() + ", Line: " + std::to_string(getLine() + 1);
		break;
	}
	case (2): {
		output += "Wrong moving format has been written by " + whoDid->getName();
		break;
	}
	case (3): {
		output += whoDid->getName() + " tried to create too many or too few pawns of certain type than the define number.";
		break;
	}
	case (4): {
		output += whoDid->getName() + " tried to place two pawns on the same square.\n";
		break;
	}
	case (5): {
		output += "No pawn exists on the wanted square, error was made by " + whoDid->getName();
		break;
	}
	case (6): {
		output += "Destination is already occupied, error was made by " + whoDid->getName();
		break;
	}
	case (7): {
		output += "There's no Joker on the wanted square, error was made by " + whoDid->getName();
		break;
	}
	case (8): {
		output += "Ilegal move were made by " + whoDid->getName() +
			" (attempts to move diagonally or skip sqaures, or moving a bomb/flag pawn).";
		break;
	}
	case (9): {
		output += "Position file doesn't exist.\n";
		break;
	}
	case (10): {
		output += "Move file doesn't exist.\n";
		break;
	}
	case (11): {
		output += "Winner: " + winner->getName() + ".\n" +
			whoDid->getName() + " lost by losing all mobile pawns.";
		break;

	}
	case (12): {
		output += "Winner: " + winner->getName() + ".\n" +
			whoDid->getName() + " lost by getting the flag captured.";
		break;
	}
	default:
		output += "Tie";
		break;
	}
	std::cout << output;
	Sleep(5000);//so that users would have the time to watch results
}//end_Game_Screen_output