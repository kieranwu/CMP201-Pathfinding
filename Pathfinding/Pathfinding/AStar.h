#pragma once
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <conio.h>
#include <windows.h>
#include "MapGenerator.h"

using namespace std;

class AStar
{
public:
	AStar();
	~AStar();

	Coord Start;
	Coord End;
	vector <Coord> path;

	vector <Coord> unchecked;
	vector <Coord> checked;
	vector<Coord> next;
	int width;
	int height;
	int** grid;

	float findH(Coord temp, Coord End);
	bool check(Coord temp, vector <Coord> checked, vector <Coord> unchecked, int** grid);
	void pathfind();
	void setUp(int** map, Coord Start, Coord End,int W,int H);
	void showEnd();
	void showGrid();
};

