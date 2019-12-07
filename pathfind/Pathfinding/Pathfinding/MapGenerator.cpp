#include "MapGenerator.h"

//Constructor
MapGenerator::MapGenerator()
{
}

//destructor
MapGenerator::~MapGenerator()
{
}

//This function will create a map which is a grid of size width * height, it will also generate 5 walls with value of -2 and an end point with value of -3
int** MapGenerator::generateMap(int height, int width, Coord* end,Coord* start)
{
	//This sets the pointer to 0
	int** map = 0;

	//Pointer set to an array of size height
	map = new int* [height];

	//loops for the size of height
	for (int i = 0; i < height; i++)
	{
		//give each row a column 
		map[i] = new int[width];

		//loops for the size of width
		for (int j = 0; j < width; j++)
		{
			//sets each value of the grid to -1
			map[i][j] = -1;
		}
	}

	//This part of the functionwill generate 5 walls at random locations
	//Loop 5 times
	for (int i = 0; i < 5; i++)
	{
		//this will randomly generate an X and Y for the walls to be placed
		int tempX = rand() % width;
		int tempY = rand() % height;

		//makes a wall at location tempx and tempy in the map
		map[tempX][tempY] = -2;
	}

	//resets the temp variables
	int tempX = 0, tempY= 0;

	//This part of the function will generate an end point
	//loop while the end doesnt get placed at 0
	while (tempX == 0 && tempY == 0)
	{
		//This will generate  a x and y position for the end point between 0 and the size of the map
		 tempX = rand() % width;
		 tempY = rand() % height;
	}

	//sets the location of the end point to -3
	map[tempX][tempY] = -3;

	end->x = tempX;
	end->y = tempY;

	//sets the starting location to 0
	map[start->x][start->y] = 0;

	//returns the map
	return map;
}


//This function will simply print the map to the console
void MapGenerator::printMap(int** map, int height, int width)
{
	//Loop for width and height
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//print the value to console
			std::cout << map[j][i] << "   ";
		}
		//next row
		std::cout << std::endl;
	}
}

//This function will return the map back to its original form, this will be used if the map is needed to be used again
void MapGenerator::mapReset(int** map, int height, int width,Coord Start,Coord End)
{
	//Loop for width and height
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//check if value at location is not -2
			if (map[i][j] != -2)
			{
				//set value to -1
				map[i][j] = -1;
			}
		}
	}

	//reset the start and end values
	map[Start.x][Start.y] = 0;
	map[End.x][End.y] = -3;
}

//This function will make a preset map used for testing *** please ignore this as it is used for testing only
int** MapGenerator::setMap(Coord* start, Coord* end)
{
	//initialise
	int width = 5;
	int height = 5;

	int** map = 0;

	//create map
	map = new int* [height];

	for (int i = 0; i < height; i++)
	{
		map[i] = new int[width];
		for (int j = 0; j < width; j++)
		{
			map[i][j] = -1;
		}
	}


	//create walls around end
	map[3][0] = -2;
	map[3][1] = -2;
	map[0][4] = -2;
	map[1][4] = -2;

	//set end
	map[2][0] = -3;

	end->x = 2;
	end->y = 0;

	//set start
	map[start->x][start->y] = 0;

	return map;



}
