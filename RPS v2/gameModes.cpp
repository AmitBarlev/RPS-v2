#include "GameModes.h"

QuietMode::QuietMode(Player **players) {
	//present all pawns "invisible"
	players[0]->setPrints(' ');
	players[1]->setPrints(' ');
}//QuietMode

CompetativeMode::CompetativeMode(int delay, Player **players) : Game(delay) {
	//present all pawns as questions marks
	players[0]->setPrints('?');
	players[1]->setPrints('?');
}//CompetativeMode
OneSideComp::OneSideComp(int delay,char index,Player **players) : Game(delay) {
	//present only one side as questions marks
	players[index]->setPrints('?');
}//OneSideComp