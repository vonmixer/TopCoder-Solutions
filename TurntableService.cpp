//SRm 219 Div 1 500 pts
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include<math.h>
#include <set>
#include <map>
#include <queue>
#include <stack>

using namespace std;

typedef pair<int,int> couple;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector< vector<int> > VV;
typedef vector< set<int> > VSET;

int ins(int a, int max)
{
	if(a<max)
		return a;
	else
		return a-max;
}

VI getRowSums( const VV all_combs)
{
	VI sums;
	for(int i=0; i<all_combs.size(); ++i)
	{
		int sum = 0;
		for(int j=0; j<all_combs.size(); ++j)
			sum+=all_combs[i][j];
		sums.push_back(sum);
	}
	return sums;
}

int min(int a,int b)
{
	if(a<b)
		return a;
	else
		return b;
}

int dist(int a, int b, int max)
{
	if(b-a>0)
		return min(b-a,max-b+a);
	else
		return min(a-b,max-a+b);
}

VV get2DVV(int x,int y, int val=0)
{
	VV twoD;
	VI row;
	row.assign(y,val);
	twoD.assign(x,row);	return twoD;
}

class TurntableService
{
public:
	int calculateTime(vector <string> favorites);
};

int TurntableService::calculateTime(vector <string> favorites)
{
	VI best;
	VSET favs;
	VV all_combs = get2DVV(favorites.size(),favorites.size());
	set<int> indiv;
	favs.assign(favorites.size(),indiv);
	best.assign(favorites.size(),0);

	for(int i=0; i<favorites.size(); ++i)
	{
		set<int> single;
		int temp;
		stringstream ss(favorites[i]);
		while(ss >> temp)
		{
			single.insert(temp);
			for(int j=0; j<favorites.size(); ++j)
			{
				if(i == ins(temp+j,favorites.size()))
					all_combs[j][ins(temp+j,favorites.size())] = 1;
			}
		}
		favs[i] = single;
	}

	best = getRowSums(all_combs);
	int left = best.size();
	int current = 0;
	int cost = 0;

	while(left)
	{
		int most = 0;
		int next = current;
		int least_dist = 0;
		for(int i=0; i<best.size(); ++i)
		{
			if((best[i] > most) || (best[i] == most && dist(current,i,best.size())<least_dist))
			{
				most = best[i];
				least_dist = dist(current,i,best.size());
				next = i;
			}
		}
		current = next;
		if(least_dist)
			cost+=least_dist+16;
		else
			cost+=15;

		VI fixed;
		for(int i=0; i<best.size(); ++i)
		{
			if(all_combs[next][i] == 1)
			{
				fixed.push_back(i);
				left--;
			}
		}

		for(int i=0; i<best.size(); ++i)
		{
			for(int j=0; j<fixed.size(); ++j)
				all_combs[i][fixed[j]] = 0;
		}
		best = getRowSums(all_combs);
	}

	return cost;
}

int main()
{
	TurntableService lala;
	vector <string> a0;
	a0.push_back("4");
	a0.push_back("1");
	a0.push_back("2");
	a0.push_back("3");
	a0.push_back("0");
	lala.calculateTime(a0);
	return 0;
}
