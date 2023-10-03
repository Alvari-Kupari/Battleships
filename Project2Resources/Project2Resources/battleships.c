/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void PrintRow(int row, int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
int IsSquareOccupied(int row, int col, int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]);
int IsHorizontalShipValid(int size, int row, int col, int map[MAP_SIZE][MAP_SIZE]);
int IsVerticalShipValid(int size, int row, int col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);
int IsShipDestroyed(int orientation, int shipSize, int rowStart, int colStart, int shots[MAP_SIZE][MAP_SIZE]);
void DestroyShip(int orientation, int rowStart, int colStart, int shipSize, int shots[MAP_SIZE][MAP_SIZE]);



/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

/*Task 1*/
void PrintRow(int row, int values[MAP_SIZE][MAP_SIZE])
{
    // print all but last column
    for (int col = 0; col < MAP_SIZE - 1; col++)
    {
        printf("%d ", values[row][col]);
    }
    // print the last column
    printf("%d\n", values[row][MAP_SIZE - 1]);
}

void PrintArray(int values[MAP_SIZE][MAP_SIZE])
{
    for (int row = 0; row < MAP_SIZE; row++)
    {
        PrintRow(row, values);
    }
}

/*Task 2*/
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE])
{
    // place biggest ship, from the top left downward
    for (int row = 0; row < 5; row++)
    {
        map[row][0] = 5;
    }

    // place the next biggest ship on the bottom left
    for (int col = 1; col < 5; col++)
    {
        map[MAP_SIZE - 1][col] = 4;
    }

    // place the size 3 ship near top left
    for (int row = MAP_SIZE / 2 - 2; row < MAP_SIZE / 2 + 1; row++)
    {
        map[row][2] = 3;
    }

    // place size 2 ship near the top right
    map[1][MAP_SIZE - 2] = 2;
    map[2][MAP_SIZE - 2] = 2;
}

/*Task 3*/
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE])
{
    int placeVertically = rand() & 1;

    int rowStart = rand() % (MAP_SIZE - size + 1);
    int col = rand() % (MAP_SIZE - size);

    for (int row = rowStart; row < rowStart + size; row++)
    {

        if (placeVertically)
        {
            map[row][col] = size;
        }

        else
        {
            map[col][row] = size;
        }
    }
}

/*Task 4*/
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE])
{
    int count = 0;

    for (int row = 0; row < MAP_SIZE; row++)
    {
        for (int col = 0; col < MAP_SIZE; col++)
        {
            if (map[row][col] == value)
            {
                count++;
            }
        }
    }

    return count;
}

/*TASK 5*/
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE])
{
    // find the first occurence of the ship
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if (map[i][j] == size)
            {
                *row = i;
                *col = j;

                // check if square to the right is also from the same ship
                if (map[i][j + 1] == size)
                {
                    return 1;
                }
                // otherwise it must have been vertical
                return 2;
            }
        }
    }
}

int IsSquareOccupied(int row, int col, int map[MAP_SIZE][MAP_SIZE])
{
    if (row < 0 || row >= MAP_SIZE)
    {
        return 0;
    }

    if (col < 0 || col >= MAP_SIZE)
    {
        return 0;
    }

    return map[row][col] != 0;

    // return 0 <= row < MAP_SIZE && 0 <= col < MAP_SIZE && map[row][col] != 0;
}
int IsHorizontalShipValid(int size, int row, int col, int map[MAP_SIZE][MAP_SIZE])
{
    // check the square to the left
    if (IsSquareOccupied(row, col - 1, map))
    {
        return 0;
    }

    // check the square to the right
    if (IsSquareOccupied(row, col + size, map))
    {
        return 0;
    }

    // check all squares above and below the ship
    for (int j = col; j < col + size; j++)
    {
        if (IsSquareOccupied(row - 1, j, map) || IsSquareOccupied(row + 1, j, map))
        {
            return 0;
        }
    }

    // otherwise everything was ok so it was valid
    return 1;
}

int IsVerticalShipValid(int size, int row, int col, int map[MAP_SIZE][MAP_SIZE])
{
    // check square above
    if (IsSquareOccupied(row - 1, col, map))
    {
        return 0;
    }

    // check square below
    if (IsSquareOccupied(row + size, col, map))
    {
        return 0;
    }

    // check all squares to the left and right
    for (int i = row; i < row + size; i++)
    {
        if (IsSquareOccupied(i, col - 1, map) || IsSquareOccupied(i, col + 1, map))
        {
            return 0;
        }
    }

    // otherwise everything must have been ok so it was valid
    return 1;
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE])
{
    int row, col, orientation;

    // find the ship we are checking
    orientation = TopLeftPosition(size, &row, &col, map);

    if (orientation == 1)
    {
        return IsHorizontalShipValid(size, row, col, map);
    }

    return IsVerticalShipValid(size, row, col, map);
}

// task 7
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE])
{

    int isMapValid;
    do
    {
        isMapValid = 1;

        // reset the array
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
                map[i][j] = 0;
            }
        }

        // add 4 ships
        for (int size = 5; size >= 2; size--)
        {
            AddRandomShip(size, map);

            // check if the ship added was not valid
            if (IsShipValid(size, map) == 0)
            {
                isMapValid = 0;
                break;
            }
        }

    } while (isMapValid == 0);
}

int IsShipDestroyed(int orientation, int shipSize, int rowStart, int colStart, int shots[MAP_SIZE][MAP_SIZE])
{
    // check for horizontal ship
    if (orientation == 1)
    {
        for (int col = colStart; col < colStart + shipSize; col++)
        {
            if (shots[rowStart][col] == 0)
            {
                // ship hasnt been destroyed
                return 0;
            }
        }
        // ship has been destroyed
        return 1;
    }

    // now check for vertically oriented ship
    for (int row = rowStart; row < rowStart + shipSize; row++)
    {
        if (shots[row][colStart] == 0)
        {
            // ship hasnt been destroyed
            return 0;
        }
    }
    // ship has been destroyed
    return 1;
}

void DestroyShip(int orientation, int rowStart, int colStart, int shipSize, int shots[MAP_SIZE][MAP_SIZE])
{
    // check for horizontal ship
    if (orientation == 1)
    {
        for (int col = colStart; col < colStart + shipSize; col++)
        {
            shots[rowStart][col] = (shots[rowStart][col] % 1000) + shipSize * 1000;
        }
        return;
    }

    // now check for vertically oriented ship
    for (int row = rowStart; row < rowStart + shipSize; row++)
    {
        shots[row][colStart] = (shots[row][colStart] % 1000) + shipSize * 1000;
    }
}

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{
    // check if square has already been shot
    if (shots[row][col] != 0)
    {
        return;
    }

    int shotCount = 0;

    // find the current shot count
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if (shots[i][j] % 1000 > shotCount)
            {
                shotCount = shots[i][j] % 1000;
            }
        }
    }

    // move onto the next shot
    shotCount++;

    int shipSize = map[row][col];

    // first check if the guess doesnt hit any ship
    if (shipSize == 0)
    {
        shots[row][col] = shotCount;
        return;
    }

    // hit the ship
    shots[row][col] = shotCount + 1000;

    // now check if ship was destroyed

    // find the start of the ship being hit
    int orientation, rowStart, colStart;
    orientation = TopLeftPosition(shipSize, &rowStart, &colStart, map);

    // check if ship wasn't destroyed
    if (IsShipDestroyed(orientation, shipSize, rowStart, colStart, shots) == 0)
    {
        return;
    }

    // update all values to indicate a destroyed ship
    DestroyShip(orientation, rowStart, colStart, shipSize, shots);
}

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
    //find the max ship size
    int max = 2;
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] > max) {
                max = map[i][j];
            }
        }
    }


    //iterate through all ships, check if its destroyed
    for (int shipSize = 2; shipSize <= max; shipSize++) {
        //locate the ship
        int orientation, rowStart, colStart;
        orientation = TopLeftPosition(shipSize, &rowStart, &colStart, map);

        //return false if the ship is not destroyed
        if (IsShipDestroyed(orientation, shipSize, rowStart, colStart, shots) == 0) {
            return 0;
        }
    }

    return 1;
}


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Provided functions needed for playing the Battleships game:

// First, prototype declarations for the bots:
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);

// Gets the input for one move from the human player (an alphabetic row and a numeric column)
// This function converts both inputs to numeric values
void GetMoveHuman(int *row, int *col, int player)
{
	char a = ' ';
	int b = -1;
	printf("Player %d: enter move [row/col]: ", player);
	while (!(a >= 'A' && a <= 'Z')) {
		scanf("%c", &a);
	}
	while (!(b >= 0 && b <= 25)) {
		scanf("%d", &b);
	}
	*row = (int)(a - 'A');
	*col = b;
}

// Takes two "shots" arrays as input (which are the visible parts of the game shown to players) and formats them into a string for printing
// The player currently to move is highlighted
void GetDisplayMapString(int shots1[MAP_SIZE][MAP_SIZE], int shots2[MAP_SIZE][MAP_SIZE], int player, char *boardString)
{
	int i, j;
	char numbers[10];
	// Intialise board string to be empty:
	boardString[0] = '\0';
	strcat(boardString, "  ");

	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "\n  ");

	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "\n");

	for (i = 0; i < MAP_SIZE; i++) {
		int len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots1[i][j] / HIT > 0) {
				if (shots1[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots1[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots1[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots2[i][j] / HIT > 0) {
				if (shots2[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots2[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots2[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "\n");
	}
	if (player == 1) {
		strcat(boardString, "  P1");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	} else {
		for (i = 0; i < MAP_SIZE; i++) {
			strcat(boardString, " ");
		}
		strcat(boardString, "   P2");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	}
	strcat(boardString, "\n");
}

// Plays one game of Battleships, beginning with the specified starting player
// Game type = 1 (human vs human) or 2 (human vs bot) or 3 (bot vs bot)
int PlayOneGame(int startingPlayer, int gameType)
{
	int row, col, player, gameOver;

	// String to display the boards
	char displayBoardString[(2*MAP_SIZE+5)*(MAP_SIZE+5)];

	// The maps containing the locations of the ships
	int mapPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int mapPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	// The locations of the shots
	int shotsPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int shotsPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	player = startingPlayer;
	gameOver = 0;

	// Create random maps for each player
	InitialiseRandomMap(mapPlayer1);
	InitialiseRandomMap(mapPlayer2);

	// Display the board if a human is playing
	if (gameType != 3) {
		GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
		printf("%s", displayBoardString);
	}

	// Process one move for the current player
	while (!gameOver) {
		if (gameType == 1) {
			GetMoveHuman(&row, &col, player);
			if (player == 1) {
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else if (gameType == 2) {
			if (player == 1) {
				GetMoveHuman(&row, &col, player);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot1(shotsPlayer2, &row, &col);
				printf("Player 2 (bot) moves: %c%d\n", (char)(row+'A'), col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else {
			if (player == 1) {
				GetMoveBot1(shotsPlayer1, &row, &col);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot2(shotsPlayer2, &row, &col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}

		// Swap players
		if (!gameOver) {
			player = 3 - player;
		}
		if (gameType != 3) {
			GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
			printf("%s", displayBoardString);
		}
	}
	return player;
}

// Play a Battleships tournament
// If the tournament is between a human and a bot, only one game is played
// If the tournament is between two bots, the number of games is requested
void PlayBattleships(void)
{
	int gameType, numberOfGames, result;
	int i, wins1, wins2, player;

	// Get play options:
	printf("Options:\n");
	printf(" [1] = Human vs. Human\n");
	printf(" [2] = Human vs. Bot1\n");
	printf(" [3] = Bot1 vs. Bot2\n");
	printf("Choose game type: ");
	scanf("%d", &gameType);
	numberOfGames = 1;
	result = 0;

	// If two bots are playing a tournament, let the user choose how many games
	if (gameType == 3) {
		printf("Number of games: ");
		scanf("%d", &numberOfGames);
	}

	// Set win counts to zero
	wins1 = 0;
	wins2 = 0;

	// Player 1 will always start the first game
	// If a tournament is played (between two bots), the starting player alternates
	player = 1;

	for (i = 0; i < numberOfGames; i++) {
		result = PlayOneGame(player, gameType);
		if (result == 1) {
			wins1++;
		} else {
			wins2++;
		}
		// Switch the starting player for the next game
		player = 3 - player;
	}

	// Show the outcome (of a single game or tournament)
	if (numberOfGames == 1) {
		printf("\nGame over! Congratulations! Winner is Player %d\n\n", result);
	} else {
		printf("\nTournament over! Games played = %d\nPlayer 1 wins = %d / Player 2 wins = %d\n\n", numberOfGames, wins1, wins2);
	}
}

// The main function for the Battleships program
int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	printf("ENGGEN131 - C Project 2023\n");
	printf("                          ... presents ...\n");
	printf(" ___    __   _____ _____  _     ____  __   _     _   ___   __  \n");
	printf("| |_)  / /\\   | |   | |  | |   | |_  ( (` | |_| | | | |_) ( (` \n");
	printf("|_|_) /_/--\\  |_|   |_|  |_|__ |_|__ _)_) |_| | |_| |_|   _)_) \n");
	printf("\n                __/___            \n");
	printf("          _____/______|           \n");
	printf("  _______/_____\\_______\\_____     \n");
	printf("  \\              < < <       |    \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");

	PlayBattleships();

	return 0;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the two bots can be provided below
// The existing implementations are naive:
// - Bot 1 simply takes random shots (without checking for repeated shots)
// - Bot 2 also takes random shots (but makes a single test on each turn for a repeated shot)
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Strategy for Bot 1
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	*row = rand_row;
	*col = rand_col;
}

// Strategy for Bot 2
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	// If the shot has been tried before, try one more time
	if (shots[rand_row][rand_col] > 0) {
		rand_row = rand() % MAP_SIZE;
		rand_col = rand() % MAP_SIZE;
	}

	*row = rand_row;
	*col = rand_col;
}













