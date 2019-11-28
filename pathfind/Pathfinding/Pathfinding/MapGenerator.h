#pragma once
#include <iostream>

struct  Coord { int x; int y; };


class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	int** generateMap(int height, int width, Coord* end,Coord* start);
	void printMap(int **map, int height, int width);



};

