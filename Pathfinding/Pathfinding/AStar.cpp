#include "AStar.h"

AStar::AStar()
{
}

AStar::~AStar()
{
	// important: clean up memory
	printf("\n");
	printf("Cleaning up memory...\n");
	for (int h = 0; h < height; h++)
	{
		delete[] grid[h];
	}
	delete[] grid;
	grid = 0;
}

float AStar::findH(Coord temp, Coord End)
{
	float X = temp.x - End.x;
	float Y = temp.y - End.y;
	X *= X;
	Y *= Y;
	float ans = X + Y;
	return (sqrt((ans)));
}

bool AStar::check(Coord temp, vector<Coord> checked, vector<Coord> unchecked, int** grid)
{
	for (int i = 0; i < checked.size(); i++)
	{
		if ((temp.x == checked[i].x && temp.y == checked[i].y) || grid[temp.x][temp.y] == -2)
		{
			return false;
		}
	}
	for (int i = 0; i < unchecked.size(); i++)
	{
		if ((temp.x == unchecked[i].x && temp.y == unchecked[i].y))
		{
			return false;
		}
	}

	return true;
}

void AStar::pathfind()
{


	int save = 10000;
	float est;
	vector <int> value;
	bool found = false;
	int num = 0;
	int bing;
	Coord temp;

	Start.g = 0;
	Start.f = Start.g + findH(Start, End);

	//cout << "Starting...  Start.f is " << Start.f << endl;

	temp = Start;
	unchecked.push_back(temp);

	while (!(unchecked.empty()))
	{
		//		 cout << "Unchecked is not Empty" << endl;
				 //check next
		save = 10000;
		//Above
//		 cout << "Checking around me" << endl;
		if (temp.y > 0)
		{
			//			 cout << "Checking Above" << endl;
			unchecked.push_back(Coord{ temp.x , temp.y - 1 });
		}
		//Below
		if (temp.y < height)
		{
			//				 cout << "Checking Below" << endl;
			unchecked.push_back(Coord{ temp.x , temp.y + 1 });
		}
		//left
		if (temp.x > 0)
		{
			//			 cout << "Checking left" << endl;
			unchecked.push_back(Coord{ temp.x - 1 , temp.y });
		}
		//right
		if (temp.x < width)
		{
			//			 cout << "Checking Right" << endl;
			unchecked.push_back(Coord{ temp.x + 1, temp.y });
		}

		//		 cout << "Going to loop through unchecked" << endl;
		for (int i = 0; i < unchecked.size(); i++)
		{
			Coord* test = &unchecked[i];
			if (test->f == 0)
			{
				//				 cout << "New Node" << endl;
				//				 cout << "Setting test to unchecked " << i << endl;
				if (grid[test->x][test->y] == -3)
				{
					//					 cout << "We found the end! " << endl;
					found = true;
					break;
				}
				else
				{
					if (!(grid[test->x][test->y] == -2))
					{
						//							 cout << "Grid i j is " << grid[test->x][test->y] << endl;

						test->g = temp.g + 1;
						test->h = findH(*test, End);
						test->f = test->h + test->g;
						//						 cout << " G H F" << test->g << test->h << test->f << endl;
							//					 cout << "is " << test->f << " <" << save << endl;
						if (test->f < save)
						{
							save = test->f;
							num = i;
							//					 cout << save << " : Save  " << num << ": num" << endl;
						}

					}
				}
			}
		}

		for (int i = 0; i < unchecked.size(); i++)
		{
			if (unchecked[i].x == temp.x && unchecked[i].y == temp.y)
			{
				bing = i;
				//					 cout << "temp is  number  " << bing << "in unchecked" << endl;
			}
		}


		bool ex = false;
		for (int i = 0; i < checked.size(); i++)
		{
			if ((temp.x == checked[i].x && temp.y == checked[i].y))
			{
				ex = true;
				//					 cout << "temp already exsist in check" << endl;
			}
			else
			{
				ex = false;
				//						 cout << "temp doesnt  exsist in check" << endl;
			}
		}

		if (ex == false)
		{
			checked.push_back(temp);
			//					 cout << "pushing temp into checked" << endl;
		}

		temp = unchecked[num];
		//				 cout << "New value of temp is now " << temp.x;


		unchecked.erase(unchecked.begin() + bing);

		if (found == true)
		{
			break;
		}

	}

	//find lowest F
	//if next is -2 dont pop and if -3 break

 //store node

	Coord thing = checked[checked.size() - 1];
	while (thing.g != 0)
	{
		next.push_back(thing);
		for (int i = 0; i < checked.size(); i++)
		{
			if (checked[i].g == thing.g - 1)
			{
				num = i;
			}
		}
		thing = checked[num];
	}


	
}

void AStar::setUp(int** map, Coord start, Coord end,int W,int H)
{
	grid = map;
	Start = start;
	End = end;
	width = W;
	height = H;
}

void AStar::showEnd()
{
	system("CLS"); // clears the console
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (grid[i][j] != -2)
			{
				if (i != End.x || j != End.y)
				{
					grid[i][j] = 0;
				}
			}
		}
	}


	grid[End.x][End.y] = -3;
	grid[Start.x][Start.y] = 0;

//pop node into checked
	int j = 1;

	for (int i = next.size() - 1; i >=0; i--)
	{
		//cout << next[i].x << "," << next[i].y << endl;
		
		grid[next[i].x][next[i].y] = j;
		j++;
	//	system("CLS"); // clears the console
	//	showGrid();
	//	Sleep(600);
	}

}

void AStar::showGrid()
{

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				cout << grid[j][i] << "   ";
			}
			cout << endl;
		}
}



