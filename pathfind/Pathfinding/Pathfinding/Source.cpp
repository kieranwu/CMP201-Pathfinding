#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <conio.h>
#include <windows.h>
#include "Lee.h"
#include "MapGenerator.h"

using namespace std;
	Lee finder;
	MapGenerator Map;


	void LeePathfinder(int** map,Coord Start,Coord End)
	{
		finder.setUp(map,Start,End);
		finder.pathfinder();
		finder.savePath();
		finder.showEnd();
	}

	void AStar()
	{
		const int width = 10;
		const int height = 10;
		 int grid[width][height];

		 //find start
		 //add to checked list
		 //look ajacent
		 //check not in checked list
		 //store step
		 //estimate distance left
		 //add to checked list
		 Coord Start{ 0,0 };



	}

int main()
{	
	srand(time(NULL));
	Coord Start{0,0};
	Coord End;
	int** map = Map.generateMap(10,10,&End,&Start);
	LeePathfinder(map,Start,End);
}
