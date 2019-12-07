#include "AStar.h"

//Constructor
AStar::AStar()
{
}

//Destructor - This will delete the map
AStar::~AStar()
{
	// important: clean up memory
	//This only needs to be done onces as it is a pointer
	printf("\n");
	printf("Cleaning up memory...\n");
	for (int h = 0; h < height; h++)
	{
		delete[] grid[h];
	}
	delete[] grid;
	grid = 0;
}

//This function will calulate the value of H
float AStar::findH(Coord temp, Coord End)
{
	//To Calculate H this function will calculate the magniude of two coords

	//Finds the X and Y difference from the current location to end
	float X = temp.x - End.x;
	float Y = temp.y - End.y;

	//Squares X and Y
	X *= X;
	Y *= Y;

	//Adds the now Squared X and Y and returns the Root value
	float ans = X + Y;
	return (sqrt((ans)));
}

//This is the main pathfinding algorithm
void AStar::pathfind()
{
	//initialise local variables
	int save = 10000;
	float est;
	vector <int> value;
	bool found = false;
	int num = 0;
	int idN = 1;
	int testNum = 0;
	isPath = true;
	Coord temp;

	//sets the F G H parent and id values of the starting location
	Start.g = 0;
	Start.f = Start.g + findH(Start, End);
	Start.parent = 0;
	Start.id = idN;

	//increment the id number
	idN++;

	//set temp to start
	//temp is used to gather more unchecked coords
	temp = Start;

	//pushes temp into unchecked
	unchecked.push_back(temp);

	//This loop will run as long a unchecked is not empty
	while (!(unchecked.empty()))
	{
		//Save is used to find the lowest f value in the unchecked vector, this will be used later 
		save = 10000;
		
		///This part of the algorithm will check the coord around the current position and add them into the unchecked vector if they have not been seen before

		//Check Above
		//Check if the y value of the current location is greater than 0 (not at the top of the map)
		if (temp.y > 0)
		{
			//This will check if the Coord above the current position is already either in unchecked or checked
			if (!(checkCoord(Coord{ temp.x,temp.y - 1 })))
			{
				//This will push the coord above into unchecked
				unchecked.push_back(Coord{ temp.x , temp.y - 1 });
			}
		}
		//Check Below
		//Check if the y value of the current location is less than height of the map (not at the bottom)
		if (temp.y < height-1)
		{
			//	This will check if the Coord below is already either in unchecked or checked
			if (!(checkCoord(Coord{ temp.x,temp.y + 1 })))
			{
				//This will push the coord below into unchecked
				unchecked.push_back(Coord{ temp.x , temp.y + 1 });
			}
		}
		//Check Left
		//This will check if the x value of the current location is greater than 0 (not on the far left)
		if (temp.x > 0)
		{
			//	This will check if the Coord on the left is eitherin unchecked or checked
			if (!(checkCoord(Coord{ temp.x - 1 ,temp.y })))
			{
				//This will push the coord on the left into unchecked
				unchecked.push_back(Coord{ temp.x - 1 , temp.y });
			}
		}
		//Check Right
		//Check if the x value of the current location is less than the width of the map (not on the far right)
		if (temp.x < width-1)
		{
			//This will check if the coord on the right is either in unchecked or checked
			if (!(checkCoord(Coord{ temp.x + 1,temp.y })))
			{
				//	This will push the right coord into unchecked
				unchecked.push_back(Coord{ temp.x + 1, temp.y });
			}
		}

		///This part of the algorithm will give each new node a F G H value

		//Loop for the size of unchecked
		for (int i = 0; i < unchecked.size(); i++)
		{
			//set pointer coord test to the current unchecked value
			Coord* test = &unchecked[i];

			//Check if the value F has not been set yet
			if (test->f == 0)
			{
				//Check if the Coord is the End
				if (grid[test->x][test->y] == -3)
				{
					//sets found to true and exits the loop
					found = true;
					break;
				}
				//if its not the end...
				else
				{
					//check if the Coord is not a wall
					if (!(grid[test->x][test->y] == -2))
					{
						
						//Set the value of  G to its parent's G value plus 1
						test->g = temp.g + 1;

						//find the H value using the function
						test->h = findH(*test, End);

						//Set F to H + G
						test->f = test->h + test->g;

						//set parent to temp id
						test->parent = temp.id;

						//set new id to id number
						test->id = idN;

						//increment id number
						idN++;
					}
					//if test is a wall it will set its F to 100
					else
					{
						test->f = 100;
					}
				}
			}
		}

		
		//this will check if the size of unchecked is 1 (usually a wall)
		if (unchecked.size() == 1)
		{
			//end loop
			break;
		}
		
		//This will find which value temp is in  unchecked so it can be removed later
		//This will also find the lowest F value in unchecked

		//loop for size of unchecked
		for (int i = 0; i < unchecked.size(); i++)
		{
			//check if the X and Y values of temp are the same as the X and Y values of the current unchecked Coord
			if (unchecked[i].x == temp.x && unchecked[i].y == temp.y)
			{
				//sets test num to i - Test num the indicator of what number in unchecked is temp in
				testNum = i;
			}

			//This will check if the F value is lower than the int Save
			if (unchecked[i].f < save)
			{
				//if true it will update save to be the value of the current coords F and save which spot in unchecked its in
				save = unchecked[i].f;
				num = i;
			}

		}

		//sets a Boolean ex to false - this will be used to check if temp already appears in check so there are no duplicated values
		bool ex = false;

		//loop for size of checked
		for (int i = 0; i < checked.size(); i++)
		{
			//Check if the X and Y values of temp apppear in checked
			if ((temp.x == checked[i].x && temp.y == checked[i].y))
			{
				//set ex to true
				ex = true;
			}
			else
			{
				//set ex to false
				ex = false;
			}
		}

		//Check if ex is false
		if (ex == false)
		{
			//push temp into checked
			checked.push_back(temp);
		}
		//otherwise do nothing
		
		//set the new temp value to the unchecked Coord with lowest F
		temp = unchecked[num];

		//removed the previous temp Coord from unchecked - previous temp either pushed into checked or was already in checked
		if (!(testNum + 1 > unchecked.size()))
		{
			unchecked.erase(unchecked.begin() + testNum);
		}

		//check if found is true or blocked by walls
		if (found == true ||temp.f == 100)
		{
			//end loop
			break;
		}

	}

	// check if loop was exited with found being false 
	if (found == false)
	{
		//print no path to console
		cout << "NO PATH" << endl;
		isPath = false;
	}


 //This part of the algorthim will sort the checked vector into the next vector so that next is a sorted path from the end to the start

	//creates a new Coord and sets it to the last value of checked
	Coord tempCoord = checked[checked.size() - 1];

	//Loop while tempcoord parent value is  not 0
	while (tempCoord.parent != 0)
	{
		//push the coord into  vector path
		path.push_back(tempCoord);
		
		//loops for size of checked
		for (int i = 0; i < checked.size(); i++)
		{
			//Check if the id value of unchecked is the coord's parent value 
			if (checked[i].id == tempCoord.parent)
			{
				//set num to i
				num = i;
			}
		}
		//set temp Coord to parent
		tempCoord = checked[num];
		
	}
}

//This function will set all the varible the A* algorithm needs 
void AStar::setUp(int** map, Coord start, Coord end,int W,int H)
{
	grid = map;
	Start = start;
	End = end;
	width = W;
	height = H;
}

//This function will show the progress visually the algorithm has made
void AStar::showEnd()
{
	system("CLS"); // clears the console

	if (isPath)
	{

		//Loop for width
		for (int i = 0; i < width; i++)
		{
			//Loop for height
			for (int j = 0; j < height; j++)
			{
				//Check if location is not a wall
				if (grid[i][j] != -2)
				{
					//check if location isnt the end
					if (i != End.x || j != End.y)
					{
						//set value to 0
						grid[i][j] = 0;
					}
				}
			}
		}

	
		//sets the start and end value to 0 and -3
		grid[End.x][End.y] = -3;
		grid[Start.x][Start.y] = 0;

		//sets J to 1
		int j = 1;

		//This part of the function will print out the path the algorithm takes

		//Loop for the size of path
		for (int i = path.size() - 1; i >= 0; i--)
		{
			//set location to j
			grid[path[i].x][path[i].y] = j;

			//increment J
			j++;
			//	system("CLS"); // clears the console

				//sleep so that we can see clearly the path taken
				//Sleep(600);
		}
		//prints the map
		showGrid();
	}
	else
	{
		cout << "NO PATH" << endl;
	}
}


//This Function will very simply print the values in the map
void AStar::showGrid()
{
	//Loop for with and height
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//print the value followed by a space
				cout << grid[j][i] << "   ";
			}
			//next row
			cout << endl;
		}
}

//This function will check if the Coord being passed in already exsist within the Unchecked or Checked vector
bool AStar::checkCoord(Coord test)
{
	//Loop for the size of unchecked
	for (int i = 0; i < unchecked.size(); i++)
	{
		//Coord is mainly defined by its X and Y
		// check if the coord exist in unchecked 
		if ((test.x == unchecked[i].x && test.y == unchecked[i].y ))
		{
			return true;
		}
	}
	//Loop for size of checked
	for (int i = 0; i < checked.size(); i++)
	{
		//Check if the Coord exist in checked
		if (test.x == checked[i].x && test.y == checked[i].y)
		{
			return true;
		}
	}

	//if function reaches here it means that the Coord did not appear in unchecked or checked and will return false
	return false;

}

//This function will clear the vectors so that they can be used again
void AStar::clearVector()
{
	//set A to the size of the vector - A must be set before hand as the size will decrease as the loop runs
	int A = unchecked.size();

	//Loop for the size of vector 
	for (int i = 0; i < A ;i++)
	{
		//pop value in vector
		unchecked.pop_back();
	}

	//The following is exactly the same as the above
	A = checked.size();

	for (int i = 0; i < A; i++)
	{
		checked.pop_back();
	}

	A = path.size();
	for (int i = 0; i < A; i++)
	{
		path.pop_back();
	}

}



