#pragma once
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <conio.h>
#include <windows.h>
#include "MapGenerator.h"

using namespace std;


class Lee
{
	public:

		Lee();
		~Lee();

	MapGenerator map;
	Coord Start;
	Coord End;
	vector <Coord> path;

	 int width;
	 int height;
	 int** grid;


	void showGrid();
	void setUp(int** map, Coord tempStart, Coord tempEnd,int W, int H);
	bool findType(int i, int j, int num, bool end);
	void pathfinder();
	void savePath();
	void showEnd();

private:



};
