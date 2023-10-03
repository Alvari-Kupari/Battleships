#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

#define MAP_SIZE 6

int rand(void);

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

/*TESTING FUNCTIONS*/
void TestPrintArray(void)
{
    int map1[MAP_SIZE][MAP_SIZE] = {0};
    printf("Map 1:\n");
    PrintArray(map1);
    int map2[MAP_SIZE][MAP_SIZE] = {0};
    for (int i = 0; i < MAP_SIZE; i++)
    {
        map2[MAP_SIZE - i - 1][i] = i;
    }
    printf("\nMap 2:\n");
    PrintArray(map2);
}

void TestInitialiseMap(void)
{
    int map1[MAP_SIZE][MAP_SIZE] = {0};
    InitialiseMap(map1);
    printf("Map: \n");
    PrintArray(map1);
}

void TestAddRandomShip(void)
{
    int map1[MAP_SIZE][MAP_SIZE] = {0};
    int map2[MAP_SIZE][MAP_SIZE] = {0};
    AddRandomShip(5, map1);
    printf("Map: \n");
    PrintArray(map1);
    AddRandomShip(2, map2);
    AddRandomShip(3, map2);
    AddRandomShip(4, map2);
    AddRandomShip(5, map2);
    printf("Map: \n");
    PrintArray(map2);
}
void TestCountValues(void)
{
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int count, shipSize;
    InitialiseMap(map);
    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++)
    {
        count = CountValues(shipSize, map);
        printf("The value %d appears %d times\n", shipSize,
               count);
    }
}

void TestTopLeftPosition(void)
{
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int row, col, direction, shipSize;
    InitialiseMap(map);
    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++)
    {
        direction = TopLeftPosition(shipSize, &row, &col, map);
        printf("Ship %d is at (%d, %d) facing %d\n", shipSize,
               row, col, direction);
    }
}

void TestIsShipValid(void)
{
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int valid, shipSize;
    InitialiseMap(map);
    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++)
    {
        valid = IsShipValid(shipSize, map);
        printf("Is ship %d valid? %d\n", shipSize, valid);
    }
    // move ship 3 to invalid pos
    map[1][2] = 0;
    map[2][2] = 0;
    map[3][2] = 0;

    map[5][0] = 3;
    map[5][1] = 3;
    map[5][2] = 3;

    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++)
    {
        valid = IsShipValid(shipSize, map);
        printf("Is ship %d valid? %d\n", shipSize, valid);
    }
}

void TestOccupiedSquares(void)
{
    int map[MAP_SIZE][MAP_SIZE] = {0};
    InitialiseMap(map);
    PrintArray(map);

    for (int i = -1; i < MAP_SIZE + 1; i++)
    {
        for (int j = -1; j < MAP_SIZE + 1; j++)
        {
            printf("Is the square %d, %d occupied?: %d\n", i, j, IsSquareOccupied(i, j, map));
        }
    }
}

void TestInitialiseRandomMap(void)
{
    int map[MAP_SIZE][MAP_SIZE] = {0};
    InitialiseRandomMap(map);
    PrintArray(map);
}

void TestFireShot(void)
{
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int shots[MAP_SIZE][MAP_SIZE] = {0};
    InitialiseMap(map);
    printf("Map:\n");
    PrintArray(map);
    printf("Shots:\n");
    PrintArray(shots);
    FireShot(shots, map, 2, 0);
    printf("Shots:\n");
    PrintArray(shots);
    FireShot(shots, map, 2, 1);
    printf("Shots:\n");
    PrintArray(shots);
    FireShot(shots, map, 2, 2);
    printf("Shots:\n");
    PrintArray(shots);
    FireShot(shots, map, 2, 3);
    printf("Shots:\n");
    PrintArray(shots);
    FireShot(shots, map, 0, 0);
    FireShot(shots, map, 1, 0);
    FireShot(shots, map, 2, 0);
    FireShot(shots, map, 3, 0);
    FireShot(shots, map, 4, 0);
    FireShot(shots, map, 5, 0);
    printf("Shots:\n");
    PrintArray(shots);
}

void TestCheckGameOver(void)
{
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int shots[MAP_SIZE][MAP_SIZE] = {0};
    InitialiseMap(map);
    printf("Map:\n");
    PrintArray(map);
    printf("Shots:\n");
    PrintArray(shots);
    while (!CheckGameOver(shots, map))
    {
        FireShot(shots, map, rand() % MAP_SIZE, rand() % MAP_SIZE);
    }
    PrintArray(shots);
}

/*END TESTING FUNCTIONS*/

int main()
{
    TestCheckGameOver();
    return 0;
}