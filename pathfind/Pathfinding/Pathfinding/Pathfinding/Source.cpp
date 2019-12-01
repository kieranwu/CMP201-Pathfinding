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

	void show(int ** map,int height , int width)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				cout << map[j][i] << "   ";
			}
			cout << endl;
		}
	}

	bool check(Coord temp, vector <Coord> checked, vector <Coord> unchecked ,int** grid) 
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
	};


	float findH(Coord temp, Coord End)
	{
		float X = temp.x - End.x;
		float Y = temp.y - End.y;
		X *= X;
		Y *= Y;
		float ans = X + Y;
		return ( sqrt((ans)));
	}

	void AStar(int** map, Coord Start, Coord End)
	{
		 int width = 10;
		 int height = 10;
		 int** grid = map;
		 vector <Coord> unchecked;
		 vector <Coord> checked;
		 vector<Coord> next;
		 int save = 10000;
		 float est;
		 vector <int> value;
		 bool found = false;
		 int num = 0;
		 int bing;
		 Coord temp;

		 Start.g = 0;
		 Start.f = Start.g + findH(Start, End);

		 cout << "Starting...  Start.f is " << Start.f << endl;

		 temp = Start;
		 unchecked.push_back(temp);
		 /*
		 while ( found == false)
		 {
			 //check above
			 if (checked[num].y > 0)
			 {
				 temp = { checked[num].x , checked[num].y  - 1};
				 if (check(temp, checked,unchecked,grid))
				 {
					 unchecked.push_back(temp);
				 }
			 }
			 if (checked[num].y < height)
			 {
				 temp = { checked[num].x , checked[num].y + 1};
				 if (check(temp, checked, unchecked,grid))
				 {
					 unchecked.push_back(temp);
				 }
			 }
			 if (checked[num].x < width)
			 {
				 temp = { checked[num].x + 1 , checked[num].y };
				 if (check(temp, checked, unchecked,grid))
				 {
					 unchecked.push_back(temp);
				 }
			 }
			 if (checked[num].x > 0)
			 {
				 temp = { checked[num].x - 1, checked[num].y + 1 };
				 if (check(temp, checked, unchecked,grid))
				 {
					 unchecked.push_back(temp);
				 }
			 }

			
			 //take pos 
			 //add up down left right to unchecked
			 //check list 


			 num += 1;

			 for (int i = 0; i < unchecked.size(); i++)
			 {
				 //check type
				 //calculate value
				 //push value

				 if (grid[unchecked[i].x][unchecked[i].y] == -3)
				 {
					 found == true;
				 }

				 float X = unchecked[i].x - End.x;
				 float Y = unchecked[i].y - End.y;
				 X *= X;
				 Y *= Y;
				 float ans = X - Y;
				est = sqrt((ans));
				value.push_back(est + num);

			 }

			 float test =1000000;
			 for (int i = 0; i < value.size(); i++)
			 {
				 if (value[i] < test)
				 {
					 test = value[i];
					 save = i;
				 }
			 }

			 checked.push_back(unchecked[save]);
			 grid[unchecked[save].x][unchecked[save].y] = num;
			 unchecked.erase (unchecked.begin() + (save ));
			 for (int i = 0; i < value.size(); i++)
			 {
				 value.pop_back();
			 }
			 
			 


			  system("CLS"); // clears the console
			  Map.printMap(grid, 10, 10);
			  Sleep(600);
			 // work out value
			 //change pos to the lowest value
		 }
		 //find start
		 //add to checked list
		 //look ajacent
		 //check not in checked list
		 //store step
		 //estimate distance left
		 //add to checked list
	*/
		 while (!(unchecked.empty()))
		 {
			 cout << "Unchecked is not Empty" << endl;
			 //check next
			 save = 10000;
			 //Above
			 cout << "Checking around me" << endl;
			 if (temp.y > 0)
			 {
				 cout << "Checking Above" << endl;
				 unchecked.push_back(Coord { temp.x , temp.y - 1 });
			 }
			 //Below
			 if (temp.y < height)
			 {
				 cout << "Checking Below" << endl;
				 unchecked.push_back(Coord{ temp.x , temp.y +1});
			 }
			 //left
			 if (temp.x > 0)
			 {
				 cout << "Checking left" << endl;
				 unchecked.push_back(Coord{ temp.x- 1 , temp.y });
			 }
			 //right
			 if (temp.x < width)
			 {
				 cout << "Checking Right" << endl;
				 unchecked.push_back(Coord{ temp.x+ 1, temp.y });
			 }

			 cout << "Going to loop through unchecked" << endl;
			 for (int i = 0; i < unchecked.size(); i++)
			 {
				 Coord *test = &unchecked[i];
				 if (test->f == 0)
				 {
					 cout << "New Node" << endl;
					 cout << "Setting test to unchecked " << i << endl;
					 if (grid[test->x][test->y] == -3)
					 {
						 cout << "We found the end! " << endl;
						 found = true;
						 break;
					 }
					 else
					 {
						 if (!(grid[test->x][test->y] == -2))
						 {
							 cout << "Grid i j is " << grid[test->x][test->y] << endl;

							 test->g = temp.g + 1;
							 test->h = findH(*test, End);
							 test->f = test->h + test->g;
							 cout << " G H F" << test->g << test->h << test->f << endl;
							 cout << "is " << test->f << " <" << save << endl;
							 if (test->f < save)
							 {
								 save = test->f;
								 num = i;
								 cout << save << " : Save  " << num << ": num" << endl;
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
						 cout << "temp is  number  " << bing << "in unchecked" << endl;
					 }
				 }


				 bool ex = false;
				 for (int i = 0; i < checked.size(); i++)
				 {
					 if ((temp.x == checked[i].x && temp.y == checked[i].y))
					 {
						 ex = true;
						 cout << "temp already exsist in check" << endl;
					 }
					 else
					 {
						 ex = false;
						 cout << "temp doesnt  exsist in check" << endl;
					 }
				 }
			
				 if (ex == false)
				 {
					 checked.push_back(temp);
					 cout << "pushing temp into checked" << endl;
				 }

				 temp = unchecked[num];
				 cout << "New value of temp is now " << temp.x;


				 unchecked.erase(unchecked.begin() + bing);
				 
				 if (found == true)
				 {
					 break;
				 }

			 }

				//find lowest F
				//if next is -2 dont pop and if -3 break

			 //store node

			 Coord thing = checked[checked.size()-1];
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















			 //pop node into checked
		 for (int i = 0; i < next.size(); i++)
		 {
			 cout << next[i].x << ","<<next[i].y<<endl;
			 grid[next[i].x][next[i].y] = i;
		 }
		

	}

int main()
{	
	srand(time(NULL));
	Coord Start{0,0};
	Coord End;
	int** map = Map.generateMap(10,10,&End,&Start);
	LeePathfinder(map,Start,End);
//finder.setUp(map,Start,End);	
	Map.mapReset(map, 10, 10,Start,End);
	Map.printMap(map, 10, 10);
	AStar(map, Start, End);
	Map.printMap(map, 10, 10);

}
