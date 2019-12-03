#include "Lee.h"

Lee::Lee()
{
}

Lee::~Lee()
{

}

void Lee::showGrid()
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

void Lee::setUp(int** map,Coord tempStart, Coord tempEnd, int W, int H)
{
	Start = tempStart;
	End = tempEnd;
	grid = map;
	width = W;
	height = H;
}

bool Lee::findType(int i, int j, int num, bool end)
{
	if (end == false)
	{
		int temp = grid[i][j];
		switch (temp)
		{
		case -3: grid[i][j] = num + 1; return true; break;
		case -2: break;
		case -1: grid[i][j] = num + 1; break;
		}
		return false;
	}
	else
	{
		return true;
	}
}

void Lee::pathfinder()
{
	bool end = false;
	int num = 0;
	grid[Start.x][Start.y] = 0;
//	showGrid();


	while (end == false)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (grid[i][j] == num)
				{
					//check up down left right
					if (i > 0)
					{
						end = findType(i - 1, j, num, end);
					}
					if (i < height-1)
					{
						//down
						end = findType(i + 1, j, num, end);
					}
					if (j > 0)
					{
						//left
						end = findType(i, j - 1, num, end);
					}
					if (j < width-1)
					{
						//right
						end = findType(i, j + 1, num, end);
					}
				}

			}
		}
		num++;
	}

//	showGrid();
}

void Lee::savePath()
{
	//look for 3
	//check around 3 for the lowest number
	//save coord
	//redraw
	//grid[End.x][End.y]
	bool fin = false;
	Coord temp;
	int x = End.x;
	int y = End.y;
	int num = grid[x][y];
	path.push_back(End);
	while (!fin)
	{
		/*
		int test = grid[x - 1][y];
		if (test == num - 1)
		{
			cout << endl;
		}
		*/
		//Check Up , Right left  down
		if (y != 0 && (grid[x][y - 1] == num - 1))
		{
			y -= 1;
			temp.x = x;
			temp.y = y;
			path.push_back(temp);
		}
		else if ((x != 0) && (grid[x - 1][y] == num - 1))
		{
			x -= 1;
			temp.x = x;
			temp.y = y;
			path.push_back(temp);
		}
		else if (x != width && (grid[x + 1][y] == num - 1))
		{
			x += 1;
			temp.x = x;
			temp.y = y;
			path.push_back(temp);
		}
		else if (y != height && (grid[x][y + 1] == num - 1))
		{
			y += 1;
			temp.x = x;
			temp.y = y;
			path.push_back(temp);
		}
		num = grid[x][y];

		if (num == 0)
		{
			fin = true;
		}
	}

/*
	int j = path.size() - 1;
	for (int i = 0; i < path.size(); i++)
	{

		cout << "Coord - " << j << " (" << path.at(i).x << " , " << path.at(i).y << "). \n";
		j--;
	}
	*/
}

void Lee::showEnd()
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
	int num = 0;
	int x, y;
	for (int i = path.size() - 1; i >= 0; i--)
	{
	//	system("CLS"); // clears the console
	//	showGrid();
	///	Sleep(600);
		x = path[i].x;
		y = path[i].y;
		grid[x][y] = num;
		num++;
	}
}
