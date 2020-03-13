/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}


void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{
    if (x == 1 && y == 1) initializeVisited();
    this->visited[x][y] = true;
    if (this->labirinth[x][y] == 2) {
        return true;
    }
    if (this->labirinth[x+1][y] != 0 && !visited[x+1][y]) {
        if (findGoal(x+1, y)) return true;
    }
    if (this->labirinth[x-1][y] != 0 && !visited[x-1][y]) {
        if (findGoal(x-1, y)) return true;
    }
    if (this->labirinth[x][y+1] != 0 && !visited[x][y+1]) {
        if (findGoal(x, y+1)) return true;
    }
    if (this->labirinth[x][y-1] != 0 && !visited[x][y-1]) {
        if (findGoal(x, y-1)) return true;
    }
	return false;
}

/*
 * b) In the worst case, the eficiency of the algorithm is ???
 * */


