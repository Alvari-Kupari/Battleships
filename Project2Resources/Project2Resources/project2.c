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
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

void PrintArray(int values[MAP_SIZE][MAP_SIZE])
{
	values[0][0] = 0; // to prevent compiler warning (you must complete this function)
}

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE])
{
	map[0][0] = 0; // to prevent compiler warning (you must complete this function)
}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE])
{
	map[0][0] = size; // to prevent compiler warning (you must complete this function)
}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE])
{
	return map[0][0] + value; // to prevent compiler warning (you must complete this function)
}

int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE])
{
	return map[0][0] + size + *row + *col; // to prevent compiler warning (you must complete this function)
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE])
{
	return map[0][0] + size; // to prevent compiler warning (you must complete this function)
}

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE])
{
	map[0][0] = 0; // to prevent compiler warning (you must complete this function)
}

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{
	shots[0][0] = map[0][0] + row + col; // to prevent compiler warning (you must complete this function)
}

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
	return shots[0][0] + map[0][0]; // to prevent compiler warning (you must complete this function)
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

/*************************************************************************
** You should define your own test functions below
*************************************************************************/

// Example: a test function for Task One
void TestPrintArray(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	printf("Map 1: \n");
	PrintArray(map1);

	int map2[MAP_SIZE][MAP_SIZE] = {0};
	for (int i = 0; i < MAP_SIZE; i++) {
		map2[MAP_SIZE-i-1][i] = i;
	}
	printf("\nMap 2:\n");
	PrintArray(map2);
}

// Example: a test function for Task Two
void TestInitialiseMap(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	InitialiseMap(map1);
	printf("\nMap: \n");
	PrintArray(map1);
}

// Example: a test function for Task Three
void TestAddRandomShip(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	int map2[MAP_SIZE][MAP_SIZE] = {0};

	AddRandomShip(5, map1);

	printf("\nMap: \n");
	PrintArray(map1);

	AddRandomShip(2, map2);
	AddRandomShip(3, map2);
	AddRandomShip(4, map2);
	AddRandomShip(5, map2);

	printf("\nMap: \n");
	PrintArray(map2);
}

int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	TestPrintArray();
	TestInitialiseMap();
	TestAddRandomShip();

	return 0;
}


