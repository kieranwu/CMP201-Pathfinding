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
#include <fstream>

//includes of personal classes
#include "Lee.h"
#include "MapGenerator.h"
#include "AStar.h"

// Import things we need from the standard library
	using std::chrono::duration_cast;
	using std::chrono::microseconds;
	using std::chrono::milliseconds;
	using std::cout;
	using std::endl;
	using std::this_thread::sleep_for;
	using std::ofstream;
	using namespace std;

//initialise objects
	Lee Leefinder;
	AStar AStarfinder;
	MapGenerator Map;


//initialise vector used to 
	vector <float> LeeTimes;
	vector <float> AStarTimes;

	//this will all the application to write to a file named test.csv
	ofstream my_file("test.csv");

	// Define the alias "the_clock" for the clock type we're going to use.
	typedef std::chrono::steady_clock the_clock;


	//this function will run the functions inside the lee pathfinding algorithm
	void LeePathfinder(int** map,Coord Start,Coord End,int width ,int height)
	{
		Leefinder.setUp(map,Start,End,width,height);
		Leefinder.pathfinder();
		Leefinder.savePath();
		Leefinder.showEnd();
		Leefinder.clearVector();
	}

	//this function will run the function inside the A* pathfinding algorithm 
	void AStarPathfinder(int** map, Coord Start, Coord End,int width,int height)
	{
		AStarfinder.setUp(map, Start, End,width ,height);
		AStarfinder.pathfind();
		AStarfinder.showEnd();
		AStarfinder.clearVector();
	}

	//This function is sourced from:
// Adam Sampson <a.sampson@abertay.ac.uk> , Basic Benchmarking lab exercise CMP201 Data Structures and Algorithms

	//This function used to compare two inputs (used for the qsort) 
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

	void test(int times, int W , int H)
	{

		//setting a start and End 
		Coord Start{0,0};
		Coord End;

		//width and height of the map
		int width = W;
		int height = H;
		//auto time_taken;

		//This pointer pointer will store the randomly generated map created in the map object
		int** map;

		//This will loop for the value of times
		for (int i = 0; i < times; i++)
		{
			//Generate map
			map = Map.generateMap(height,width,&End,&Start);
			

			// Start timing
			the_clock::time_point Tstart = the_clock::now();

			//run Lee Algorithm
			LeePathfinder(map,Start,End,width , height);

			// Stop timing
			the_clock::time_point Tend = the_clock::now();

			// find the difference  in milliseconds
			auto  time_taken = duration_cast<milliseconds>(Tend - Tstart).count();

			//store time taken 
			LeeTimes.push_back(time_taken);
		
			
			//reset the map so it goes back to -1s
			Map.mapReset(map, width, height,Start,End);

			// Start timing
			Tstart = the_clock::now();

			//Run A* algorithm
			AStarPathfinder(map,Start,End,width,height);

			// Stop timing
			Tend = the_clock::now();

			// find the difference in milliseconds
			 time_taken = duration_cast<milliseconds>(Tend - Tstart).count();
		
			//store time taken 
			AStarTimes.push_back(time_taken);
			
		}
	
		//print results to console
		std::qsort(LeeTimes.data(), times, sizeof(int), compare);
		cout << "The average time taken for Lee Algorithm was :" << LeeTimes[times/2] << "ms.\n";

		std::qsort(AStarTimes.data(), times, sizeof(int), compare);
		cout << "The average time taken for AStar was :" << AStarTimes[times/2] << "ms.\n";

		//write average to csv file
		my_file << LeeTimes[times / 2] << "," << AStarTimes[times / 2] <<","<< width << endl;

		for (int i = 0; i < times; i++)
		{
			LeeTimes.pop_back();
			AStarTimes.pop_back();
		}

	}
	
	//TEST FUNCTIONS PLEASE IGNORE
	/*
	void test2() 
	{
		Coord Start{0,0};
		Coord End;
		int** map = Map.setMap(&Start, &End);
		Map.printMap(map,5,5);
		AStarPathfinder(map,Start,End,5,5);
	
	}

	void test3()
	{
		float total = -1;
		float times[11];
		//setting a start and End 
		Coord Start{ 0,0 };
		Coord End;

		//width and height of the map
		int width = 1000;
		int height = 1000;
		//auto time_taken;

		//This pointer pointer will store the randomly generated map created in the map object
		int** map;

		for (int i = 0; i < 11; i++)
		{

			map = Map.generateMap(height, width, &End, &Start);
			// Start timing
			the_clock::time_point start = the_clock::now();

			// Do something that takes some time
			//sleep_for(milliseconds(302));
	
			LeePathfinder(map, Start, End, width, height);

			// Stop timing
			the_clock::time_point end = the_clock::now();

			// Compute the difference between the two times in milliseconds
			auto time_taken = duration_cast<microseconds>(end - start).count();
			times[i] = time_taken;
			//cout << "It took " << time_taken << " ms.\n";
			//cout << "The total is :" << total << endl;

		}
		std::qsort(times, 11, sizeof(int), compare);


		cout << "The average time taken was :" << times[5] << "ms.\n";
	}
	*/

	//Main function will create a starting location and pass the map into the pathfinding algorithms
int main()
{	
	//create a random seed for the generation of the map
	srand(time(NULL));	

	//print title of columns to file
	my_file << "Time A" << "," << "Time B"<<","<<"Size of Grid" << endl;

	//run tests 100 times each with different map sizes
	test(100,5,5);
	test(100, 10, 10);
	test(100, 15, 15);
	test(100, 20, 20);
	test(100, 25, 25);
}
