//TCO 03 Room 4
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

typedef pair<int,int> couple;

bool ins(int a, int max)
{
	if(a<0 || a>max)
		return false;
	else
		return true;
}

class AvoidRoads
{
public:
	long long numWays(int width, int height, vector <string> bad);
};

long long AvoidRoads::numWays(int width, int height, vector <string> bad)
{	
	set< pair<couple,couple> > notgood;
	set<couple> found;
	found.insert(couple(0,0));
	for(int i=0; i<bad.size(); ++i)
	{
		couple a,b;
		stringstream ss(bad[i]);
		ss >> a.first >> a.second >> b.first >> b.second;
		notgood.insert( pair<couple,couple>(a,b));
		notgood.insert( pair<couple,couple>(b,a));
	}

	vector< vector<long long> > area;
	vector<long long> row;
	row.assign(width+1,0);
	area.assign(height+1,row);

	area[0][0] = 1;

	for(int i=0; i<=height; ++i)
	{
		for(int j=0; j<=width; ++j)
		{
			for(int k=-1; k<=1; k+=2)
			{
				if(ins(i+k,height) && notgood.find(pair<couple,couple>(couple(i,j),couple(i+k,j)))==notgood.end())
					area[i][j] += area[i+k][j];
				if(ins(j+k,width) && notgood.find(pair<couple,couple>(couple(i,j),couple(i,j+k)))==notgood.end())
					area[i][j] += area[i][j+k];
			}
		}
	}

	return area[height][width];
}

int main()
{
	AvoidRoads lala;
	int a0;
	int a1;
	vector <string> a2;
	a0=35;
	a1=31;
	//a2.push_back("0 0 0 1");
	//a2.push_back("6 6 5 6");
	long long haha = lala.numWays(a0,a1,a2);
	return 0;
}
