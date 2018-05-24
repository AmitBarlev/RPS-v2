# RPS-v2

FileExternal :
Win conditions - capture flag or destory all mobile pawns.
Tie - both files end without a winner. if player 1's file is longer than player 2's file, FileExternal will only read player 1's file.
Pawns - the number of pawns is a maximum of 13, each type cannot be higher than:
Rock = 2
Paper = 5
Scissor = 1
Bomb = 2
Joker = 2
Flag = 1 (Flag is 1, cannot be higher or lower than 1)
Inputs (Position or Moving) - File External will not give another chance, format must 
be correct, inputs will be inserted by the next files:
player1.rps_board
player2.rps_board
player1.rps_moves
player2.rps_moves
Output file - class creates output file in which the game's outcome is written,
and the last position of the board. output file name : 'RPS.output' .


ConsoleInput:
Win conditions - capture the flag or destory all mobile pawns.
Tie - if one player decides to leave the game by pressing 'y' when the game offers him,
otherwise the game will continue until a winner is decided.
Pawns - the number of pawns is 13, every types numbers are defined as:
R = 2
P = 5
S = 1
B = 2
J = 2
F = 1
Inputs - 
	Position - If the user has written in a bad format, ConsoleInput will guide him and ask for
	detailed inputs (will ask for type, X coordinate,
	Y coordinate and Joker's representation seperetely). If by the second try the user has still inserted a wrong
	format, he'll be disqualified.
	Moving - ConsoleInput will ask for a moving command line (which includes moving certain 
	pawns and Joker's changing representation). The user HAS to insert a moving line correctly.
	If Joker's changing representation has not been inserted, ConsoleInput will give the user a second
	chance of doing so.
Output File - will not create output file, will print to console the game's outcome.

Disqulification - Triggers :
1. Wrong position format.
2. Wrong moving format.
3. Too many or too few pawns.
4. Placing two pawns (of the same player) on the same square.
5. Trying to access an empty square.
6. Trying to move pawn to an occupied square.
7. Trying to change Joker's representation thourgh a square with no Joker placed on it.
8. Trying to move a pawn diagonally.
9. Trying to move a bomb.
10. Trying to move a Flag.
11. Position files don't exist.
12. Moving files don't exist.

Tests:
FileExternal - 
	- Placing 1 and 2 are a working position files and should be used to check moving 
	errors or winning conditions.
	-Immobile Pawns P1, P2 and Flag Win P1,P2 are a working moving files in order to check
	two conditions for winning the game.
	-All files starting in "BadPositionFile" are for checking positions errors
	-All files starting in "BadMovingCommand" are for checking moving errors 
	(these file require working positioning, use Placing 1 and 2 ). Also,
	when checking for player error, make sure that the other player's moving file is correct.
ConsoleInput - 
	- Placing is a working position file,content of it should be copy & pasted into console when Game asks for positions.
	-Immobile Pawns and Flag Capture are a working moving files, each line should be inserted seperetely when game asks to.
	-Immobile Pawns and Flag Capture - Fully Automated are a fully automated version of Immobile Pawns and Flag Capture,
	content should be copy & pasted into console when game asks to.
	-All files starting in "BadPositionFile" is for checking positions errors (copy content into console)
	-All files starting in "BadMovingCommand" is for checking moving errors (copy content into console)
	
