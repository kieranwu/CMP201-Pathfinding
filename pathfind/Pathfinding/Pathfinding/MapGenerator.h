//This class the be used to create a map the pathfinding algorithms

#pragma once

//includes used 
#include <iostream>

//Coord structure used throughout the whole program which stores a X any Y as well as F G H values
struct  Coord { int x; int y; int g; int h; int f; int parent; int id; };


class MapGenerator
{
public:

	//constructor and destructor
	MapGenerator();
	~MapGenerator();

	//initialise functions
	int** generateMap(int height, int width, Coord* end,Coord* start);
	void printMap(int **map, int height, int width);
	void mapReset(int** map, int height, int width,Coord Start,Coord End);
	int** setMap(Coord* Start, Coord* End);

};

