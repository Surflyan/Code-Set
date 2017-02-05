#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include "stack.h"
#include "queue.h"
//declaration and typedefinition
typedef std::pair<int, int> Position;
typedef std::pair<int, int> mazeSize;
typedef stack<Position> path;
typedef stack<Position> next_position;
using namespace std;

bool maze[50][50];
void initializeMaze(const string & filename, mazeSize & size, Position & start, Position & end);
next_position createDirection(Position currentPosition);
bool & value(Position p) { return maze[p.first][p.second]; }
std::ostream & operator<<(std::ostream & os, const Position & p) { os << "(" << p.first << ", " << p.second << ") "; return os; }
int main()
{
	stack<path> path_aggravate(32);
	path min_path;
	stack<next_position> availableDirection;
	path currentPath(32);
	Position start;
	Position end;
	mazeSize size;
	//initialize maze from a file
	string filename = "data.txt";
	initializeMaze(filename, size, start, end);
	//initialize current position and available direction
	next_position direction = createDirection(start);
	Position currentPosition = start;
	value(start) = 0;
	currentPath.push(currentPosition);
	availableDirection.push(direction);
	//find paths
	while (!currentPath.empty())
	{
		if (currentPosition == end)
		{
			path_aggravate.push(currentPath);
			value(currentPosition) = 1;
			currentPath.pop();
			availableDirection.pop();
			currentPosition = currentPath.top();
			direction = availableDirection.top();
		}
		else if (!direction.empty())
		{
			direction.pop(currentPosition);
			value(currentPosition) = 0;
			direction = createDirection(currentPosition);
			currentPath.push(currentPosition);
			availableDirection.push(direction);
		}
		else
		{
			value(currentPosition) = 1;
			currentPath.pop();
			availableDirection.pop();
			if (currentPath.empty())
				break;
			currentPosition = currentPath.top();
			direction = availableDirection.top();
		}
	}
	int i = 0;
	for (auto iter_path = path_aggravate.begin(); iter_path != path_aggravate.end(); iter_path++, i++)
	{
		cout << "path" << i << ": ";
		for (auto iter_pos = (*iter_path).begin(); iter_pos != (*iter_path).end(); iter_pos++)
			cout << *iter_pos;
		cout << endl;
	}
}

void initializeMaze(const string & filename, mazeSize & size, Position & start, Position & end)
{
	ifstream fin;
	fin.open(filename);
	int x, y;
	fin >> x >> y;
	for (int i = 0; i <= x + 1; i++)
		maze[i][0] = maze[i][y + 1] = 0;
	for (int i = 1; i <= y; i++)
		maze[0][i] = maze[x + 1][i] = 0;
	int x0, y0;
	int xt, yt;
	fin >> x0 >> y0 >> xt >> yt;
	for (int j = 1; j <= y; j++)
		for (int i = 1; i <= x; i++)
			fin >> maze[i][j];
	start = Position(x0, y0);
	end = Position(xt, yt);
	size = mazeSize(x, y);
}

next_position createDirection(Position currentPosition)
{
	next_position temp(7);
	Position tempPosition;
	int x = currentPosition.first - 1;
	int y = currentPosition.second - 1;
	int i, j;
	for (i = 0; i < 3; i++, tempPosition.first++)
		for (j = 0; j < 3; j++, tempPosition.second++)
			if (value(tempPosition) && tempPosition != currentPosition)
				temp.push(tempPosition);
	return temp;
}
