//SRM 198 Div 1 500 Points
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

typedef pair<int,int> couple;

struct PairComparator 
{
	bool operator()( const couple p1, const couple p2 ) const 
    { 
		if( p1.first > p2.first ) 
			return true;
		else
			return false;
    }
};

class DungeonEscape
{
public:
	int exitTime(vector <string> up, vector <string> down, vector <string> east, vector <string> west, int startLevel, int startEasting);
};

int DungeonEscape::exitTime(vector <string> up, vector <string> down, vector <string> east, vector <string> west, int startLevel, int startEasting)
{
	vector< vector<int> > dungeon;
	vector<int> level;
	level.assign((up.size()*up[0].length())+1,-1);
	dungeon.assign((up.size()*up[0].length())+1,level);
	int jango;

	for(int i=0; i< up.size(); ++i)
	{
		for(int j=0; j<up[0].length(); ++j)
		{
			jango = i*up[0].size()+j+1;
			if(up[i][j]!='x')
			{
				if(i==0)
					dungeon[jango][0] = up[i][j]-48;
				else
					dungeon[jango][(i-1)*up[0].size()+j+1] = up[i][j]-48;
			}				
			if(down[i][j]!='x')
			{
				if(i!=up.size()-1)
					dungeon[jango][(i+1)*up[0].size()+j+1] = down[i][j]-48;
			}	
			if(east[i][j]!='x')
			{
				if(j!=up[0].size()-1)
					dungeon[jango][jango+1] = east[i][j]-48;
			}	
			if(west[i][j]!='x')
			{
				if(j>0)
					dungeon[jango][jango-1] = west[i][j]-48;
			}	
		}
	}

	int enter = startLevel*up[0].size()+startEasting+1;

	priority_queue<couple,vector<couple>,PairComparator> rooms_seen;
	set<int> found;
	rooms_seen.push(couple(0,enter));

	while(rooms_seen.empty()==false)
	{
		int current = rooms_seen.top().second;
		int time = rooms_seen.top().first;
		rooms_seen.pop();

		if(current==0)
			return time;

		int water_level = ((up.size()*up[0].size() - current)/up[0].size() +1)*up[0].size();
		if(time>= water_level)
			continue;

		for(int i=0; i<(up.size()*up[0].length())+1; ++i)
		{
			if(dungeon[current][i] != -1 && found.find(i)==found.end())
				rooms_seen.push(couple(time+dungeon[current][i],i));
		}
		found.insert(current);
	}

	return -1;
}

int main()
{
	DungeonEscape lala;

	vector<string> up;
	vector<string> down;
	vector<string> east;
	vector<string> west;

	/*up.push_back("123");
	up.push_back("111");
	down.push_back("987");
	down.push_back("111");
	east.push_back("222");
	east.push_back("3x3");
	west.push_back("222");
	west.push_back("131");*/
	
	up.push_back("xxxxxxxxx1");
	up.push_back("xxxx999991");
	up.push_back("x999999991");
	down.push_back("1111111111");
	down.push_back("1111111111");
	down.push_back("1111111111");
	east.push_back("1111122242");
	east.push_back("2222222241");
	east.push_back("2111111111");
	west.push_back("xxxxxxxxx1");
	west.push_back("1111111111");
	west.push_back("xxxxxxxxx1");

	lala.exitTime(up,down,east,west,2,0);

	return 0;
}
