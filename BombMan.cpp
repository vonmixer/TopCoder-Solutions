//TCCC 004 Round 4 500 Points
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

const int WALL = 3;
const int PATH = 1;
typedef pair<int,int> coords;

struct PairComparator 
{
	bool operator()( const std::pair<coords,coords>& p1,const std::pair<coords,coords>& p2 ) const 
    {  
		return p1.first.first > p2.first.first;
    }
};

template< typename FirstType, typename SecondType >
struct PairComparator2 {
  bool operator()( const std::pair<FirstType, SecondType>& p1,
    const std::pair<FirstType, SecondType>& p2 ) const 
    {  if( p1.first < p2.first ) return true;
        if( p2.first < p1.first ) return false;
        return p1.second < p2.second;
    }
};


class BombMan
{
public:
    int shortestPath(vector <string> maze, int bombs);
};

int BombMan::shortestPath(vector <string> maze, int bombs)
{
	vector< vector<int> > level;
	vector<int> row;
	row.assign(maze[0].length()+2,0);
	level.assign(maze.size()+2,row);

	set<coords,PairComparator2<int,int> > found;

	pair<int,int> start,end;

	for(int i=0; i<maze.size(); ++i)
	{
		for(int j=0; j<maze[0].size(); ++j)
		{
			if(maze[i][j]=='#')
				level[i+1][j+1] = WALL;
			if(maze[i][j]=='.')
				level[i+1][j+1] = PATH;
			if(maze[i][j]=='B')
				start = pair<int,int>(i+1,j+1);
			if(maze[i][j]=='E')
			{
				end = pair<int,int>(i+1,j+1);
				level[i+1][j+1] = PATH;
			}
		}
	}

	priority_queue< pair<coords,coords>, vector< pair<coords,coords> >, PairComparator > foundNotHandled;
	foundNotHandled.push( pair<coords,coords>(coords(0,bombs),start));

	while(foundNotHandled.empty()==false)
	{
		coords current = foundNotHandled.top().second;
		int len = foundNotHandled.top().first.first;
		int cur_bombs = foundNotHandled.top().first.second;
		foundNotHandled.pop();
		
		if(current == end)
			return len;

		int x = current.first;
		int y = current.second;

		if(found.find(current)!=found.end())
			continue;

		if(level[x+1][y]==PATH)
			foundNotHandled.push(pair<coords,coords>(coords(len+1,cur_bombs),coords(x+1,y)));
		if(level[x-1][y]==PATH)
			foundNotHandled.push(pair<coords,coords>(coords(len+1,cur_bombs),coords(x-1,y)));
		if(level[x][y+1]==PATH)
			foundNotHandled.push(pair<coords,coords>(coords(len+1,cur_bombs),coords(x,y+1)));
		if(level[x][y-1]==PATH)
			foundNotHandled.push(pair<coords,coords>(coords(len+1,cur_bombs),coords(x,y-1)));
		if(level[x+1][y]==WALL && cur_bombs>0)
			foundNotHandled.push(pair<coords,coords>(coords(len+3,cur_bombs-1),coords(x+1,y)));
		if(level[x-1][y]==WALL && cur_bombs>0)
			foundNotHandled.push(pair<coords,coords>(coords(len+3,cur_bombs-1),coords(x-1,y)));
		if(level[x][y+1]==WALL && cur_bombs>0)
			foundNotHandled.push(pair<coords,coords>(coords(len+3,cur_bombs-1),coords(x,y+1)));
		if(level[x][y-1]==WALL && cur_bombs>0)
			foundNotHandled.push(pair<coords,coords>(coords(len+3,cur_bombs-1),coords(x,y-1)));
		found.insert(current);
	}

	return -1;
}

int main()
{
	BombMan lala;
	vector<string> input;
	input.push_back(".....B.");
	input.push_back(".#####.");
	input.push_back(".#...#.");
	input.push_back(".#E#.#.");
	input.push_back(".###.#.");
	input.push_back(".......");
	lala.shortestPath(input,1);

    return 0;
}
