#pragma once
#include <iostream>

struct  Coord { int x; int y; int g; int h; int f; };


class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	int** generateMap(int height, int width, Coord* end,Coord* start);
	void printMap(int **map, int height, int width);
	void mapReset(int** map, int height, int width,Coord Start,Coord End);
	

};

