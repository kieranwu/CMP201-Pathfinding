//This class will implement the Lee/Bruteforce pathfinding algorithm 

#pragma once

//includes used throughout the class
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <conio.h>
#include <windows.h>

//include of personal class
#include "MapGenerator.h"

using namespace std;

class Lee
{
	public:

		//Constructor and Destructor
		Lee();
		~Lee();
	
	//Coords for the algorithm 
	Coord Start;
	Coord End;

	//Vector used to save the path it takes
	vector <Coord> path;

	//initialise important variables
	 int width;
	 int height;
	 bool isPath = true;
	 //This pointer pointer is the map 
	 int** grid;

	 //initialise functions
	void showGrid();
	void setUp(int** map, Coord tempStart, Coord tempEnd,int W, int H);
	bool findType(int i, int j, int num, bool end);
	void pathfinder();
	void savePath();
	void showEnd();
	void clearVector();

};

