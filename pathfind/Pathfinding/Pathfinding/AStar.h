//This Class will implement the A* Pathfinding algorithm
#pragma once

//Includes used 
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <conio.h>
#include <windows.h>

//includes of personal classes
#include "MapGenerator.h"

using namespace std;

class AStar
{
public:

	//Constructor and Destructor
	AStar();
	~AStar();

	//Co ordinates of the start and the end of the map
	Coord Start;
	Coord End;

	//Vectors used to store Coords 
	vector <Coord> unchecked;
	vector <Coord> checked;
	vector<Coord> path;

	//Other important variables 

	//rows and columbs of the map
	int width;
	int height;
	bool isPath;
	//this pointer pointer the map
	int** grid;

	//initialise functions


	float findH(Coord temp, Coord End);
	void pathfind();
	void setUp(int** map, Coord Start, Coord End,int W,int H);
	void showEnd();
	void showGrid();
	bool checkCoord(Coord test);
	void clearVector();
};

