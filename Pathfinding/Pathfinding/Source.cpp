//CMP201 final coursework - 1801249 - Kieran Wu - Pathfinding Algorithms Lee/BruteForece and A* 

//includes used throughout the program
#include <iostream>
#include <stdlib.h>    
#include <time.h>      
#include <vector>		
#include <windows.h>
#include <chrono>
#include <thread>
#include <algorithm>

//includes of personal classes
#include "Lee.h"
#include "MapGenerator.h"
#include "AStar.h"

// Import things we need from the standard library
	using std::chrono::duration_cast;
	using std::chrono::milliseconds;
	using std::cout;
	using std::endl;
	using std::this_thread::sleep_for;
	using namespace std;

//initialise objects
	Lee Leefinder;
	AStar AStarfinder;
	MapGenerator Map;


//initialise vector used to 
	vector <float> LeeTimes;
	vector <float> AStarTimes;

	// Define the alias "the_clock" for the clock type we're going to use.
	// (You can change this to make the code below use a different clock.)
	typedef std::chrono::steady_clock the_clock;



	//this function will run the functions inside the lee pathfinding algorithm
	void LeePathfinder(int** map,Coord Start,Coord End,int width ,int height)
	{
		Leefinder.setUp(map,Start,End,width,height);
		Leefinder.pathfinder();
		Leefinder.savePath();
		Leefinder.showEnd();
	}

	//this function will run the function inside the A* pathfinding algorithm 
	void AStarPathfinder(int** map, Coord Start, Coord End,int width,int height)
	{
		AStarfinder.setUp(map, Start, End,width ,height);
		AStarfinder.pathfind();
		AStarfinder.showEnd();
	}

	int compare(const void* a, const void* b)
	{
		const int* x = (int*)a;
		const int* y = (int*)b;
		if (*x > * y)
			return 1;
		else if (*x < *y)
			return -1;
		return 0;
	}

	void test(int times)
	{
		//setting a start and End 
		Coord Start{0,0};
		Coord End;

		//width and height of the map
		int width = 10;
		int height = 10;
		float time_taken;

		//This pointer pointer will store the randomly generated map created in the map object
		int** map;
		for (int i = 0; i < times; i++)
		{
			map = Map.generateMap(height,width,&End,&Start);

			// Start timing
			the_clock::time_point Tstart = the_clock::now();

			//run Lee Algorithm
			LeePathfinder(map,Start,End,width , height);

			// Stop timing
			the_clock::time_point Tend = the_clock::now();

			// Compute the difference between the two times in milliseconds
			 time_taken = duration_cast<milliseconds>(Tend - Tstart).count();

			//store time taken 
			LeeTimes.push_back(time_taken);

			//reset the map so it goes back to -1s
			Map.mapReset(map, width, height,Start,End);

			// Start timing
			Tstart = the_clock::now();

			AStarPathfinder(map,Start,End,width,height);

			// Stop timing
			Tend = the_clock::now();

			// Compute the difference between the two times in milliseconds
			 time_taken = duration_cast<milliseconds>(Tend - Tstart).count();

			//store time taken 
			AStarTimes.push_back(time_taken);

		}

		std::qsort(LeeTimes.data(), times, sizeof(int), compare);
		cout << "The average time taken for Lee Algorithm was :" << LeeTimes[times/2] << "ms.\n";

		std::qsort(AStarTimes.data(), times, sizeof(int), compare);
		cout << "The average time taken for AStar was :" << AStarTimes[times/2] << "ms.\n";
	}
	

	//Main function will create a starting location and pass the map into the pathfinding algorithms
int main()
{	
	//create a random seed for the generation of the map
	srand(time(NULL));
	test(10);
	

}
