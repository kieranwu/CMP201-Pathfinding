#include "Lee.h"

//Constructor
Lee::Lee()
{
}

//Destructor
Lee::~Lee()
{

}

//This varible will simply print the map to the console
void Lee::showGrid()
{
	//loop for width and height
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//print value to console
			cout << grid[j][i] << "   ";
		}
		//next row
		cout << endl;
	}
}

//This function will save all the important variables needed for the algorithm to run
void Lee::setUp(int** map,Coord tempStart, Coord tempEnd, int W, int H)
{
	Start = tempStart;
	End = tempEnd;
	grid = map;
	width = W;
	height = H;
	isPath = true;
}

//This function will look at the value of the position in the map and do different things
bool Lee::findType(int i, int j, int num, bool end)
{
	//Checks if End is false (End is already found)
	if (end == false)
	{
		//set temp to the value of the map position passed in
		int temp = grid[i][j];

		//switch statement to respond to the value of temp
		// If the value is -3 then it is the end of the map, it will set the value to num+1 (number of step) and return true
		// If the value is -2 then it is a wall so it will just exit
		//If the value is -1 then it is a free space and set the the value to num +1 
		switch (temp)
		{
		case -3: grid[i][j] = num + 1; return true; break;
		case -2: break;
		case -1: grid[i][j] = num + 1; break;
		}
		//if not the end it will return false
		return false;
	}
	else
	{
		//return true as it is the end;
		return true;
	}
}

//This function implements the Lee pathfinding algorithm
void Lee::pathfinder()
{
	//initialise local variables
	bool end = false;
	int num = 0;

	//set the start of the map to 0
	grid[Start.x][Start.y] = 0;

	//Loop while end is false
	while (end == false)
	{
		//Loop for width and height
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//Check if location is = num (if where the function is looking at on the map is the value of what step its on)
				if (grid[i][j] == num)
				{
					//Check above
					//This will check if the row is greater 0  
					if (i > 0)
					{
						//run the findtype function passing in the location above and what step its on
						end = findType(i - 1, j, num, end);
					}
					//Check Below
					//This will check if the row is less than height -1
					if (i < height-1)
					{
						//run the findtype function passing in the location below and what step its on
						end = findType(i + 1, j, num, end);
					}
					//Check Left
					//This will check if the column is greater than 0
					if (j > 0)
					{
						//run the findtype function passing in the location left and what step its on
						end = findType(i, j - 1, num, end);
					}
					//Check right
					//This will check if the column is less than the width
					if (j < width-1)
					{
						//run the findtype function passing in the location right and what step its on
						end = findType(i, j + 1, num, end);
					}
				}

			}
		}
		//increment num (next step)
		num++;
	
		//Check if the number of steps taken is double the height (moved throughout the whole map and end is still false)
		if (num > height*2)
		{
			//set end to true and path to false
			end = true;
			isPath = false;
		}
	}
}

//This function will save the algorithm has taken
void Lee::savePath()
{
	//initialise local variables
	bool fin = false;
	Coord temp;
	int x = End.x;
	int y = End.y;
	int num = grid[x][y];

	//push the end into the path vector
	path.push_back(End);

	//Loop while fin is false and there is a path
	while (!fin && isPath)
	{
		
		//This will check if the y is not 0 (not at the top of the map) and if the value above is the previous step
		if (y != 0 && (grid[x][y - 1] == num - 1))
		{
			//decrease y by one and push current location into path
			y -= 1;
			temp.x = x;
			temp.y = y;
			path.push_back(temp);
		}
		//otherwise this will check if the x is not 0 (not on the far left) and if the value to the left is the previous step
		else if ((x != 0) && (grid[x - 1][y] == num - 1))
		{
			//decrease x by one and push current location into path
			x -= 1;
			temp.x = x;
			temp.y = y;
			path.push_back(temp);
		}
		//otherwise this will check if the x is not the width of the map (not on the far right) and if the value to the right is the previous step
		else if (x != width -1 && (grid[x + 1][y] == num - 1))
		{
			//increase x by one and push current location into path
			x += 1;
			temp.x = x;
			temp.y = y;
			path.push_back(temp);
		}
		//otherwise this will check if the value is not the height of the map (not on the bottom) and if the value below is the previous step 
		else if (y != height - 1&& (grid[x][y + 1] == num - 1))
		{
			//increase y by one and push the current location into path
			y += 1;
			temp.x = x;
			temp.y = y;
			path.push_back(temp);
		}

		//set num to the value of the location on the map
		num = grid[x][y];

		//check if num is 0 (start of the path)
		if (num == 0)
		{
			//set fin to true
			fin = true;
		}
	}
}

//This function will show the path the algorithm has taken
void Lee::showEnd()
{
	system("CLS"); // clears the console

	//Loop for width and height
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			//Check if location is not a wall
			if (grid[i][j] != -2)
			{
				//set value to 0
				grid[i][j] = 0;
			}
		}
	}

	//reset end point to -3
	grid[End.x][End.y] = -3;

	//initialise local variable
	int num = 0;
	int x, y;

	//Checks if there is a path
	if (isPath)
	{
		//Loop for the size of path vector
		for (int i = path.size() - 1; i >= 0; i--)
		{
			system("CLS"); // clears the console

			
			
		//	Sleep(600);
			//change the value of each location of the map in order of the path 
			x = path[i].x;
			y = path[i].y;
			grid[x][y] = num;
			num++;
		}
		//print the map 
		showGrid();
	}
	else
	{
		//print no path to console
		cout << "NO PATH" << endl;
	}
}


//This function will clear the vectors so that they can be used again
void Lee::clearVector()
{
		//set A to the size of the vector - A must be set before hand as the size will decrease as the loop runs
		int A  = path.size();
		for (int i = 0; i < A; i++)
		{
			path.pop_back();
		}
}
