#include "MapGenerator.h"

MapGenerator::MapGenerator()
{
}

MapGenerator::~MapGenerator()
{
}

int** MapGenerator::generateMap(int height, int width, Coord* end,Coord* start)
{
	int** map = 0;
	map = new int* [height];

	for (int i = 0; i < height; i++)
	{
		map[i] = new int[width];
		for (int j = 0; j < width; j++)
		{
			map[i][j] = -1;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		int tempX = rand() % width;
		int tempY = rand() % height;

		map[tempX][tempY] = -2;
	}

	int tempX = rand() % width;
	int tempY = rand() % height;

	map[tempX][tempY] = -3;

	end->x = tempX;
	end->y = tempY;

	map[start->x][start->y] = 0;

	return map;
}

void MapGenerator::printMap(int** map, int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << map[j][i] << "   ";
		}
		std::cout << std::endl;
	}
}
