//SRM 433 Divison 1 1000 Pts
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>
#include <stack>

using namespace std;

typedef pair<int,int> couple;
typedef pair<couple,vector<int> > strouple;

struct StroupleComparator 
{
	bool operator()( const strouple& p1,const strouple& p2 ) const 
    { 
		if(p1.first.first > p2.first.first)
			return true;
		if(p1.first.first == p2.first.first)
			return p1.first.second > p2.first.second;
		return false;
    }
};

bool at_border(const couple current, const vector< vector<couple> >& country)
{
	int x = current.first;
	int y = current.second;
	for(int i=-1; i<=1; i+=2)
	{
		if(country[x+i][y].first ==	0)
			return true;
		if(country[x][y+i].first ==	0)
			return true;
	}
	return false;
}

int get_id(int x, int y)
{
	return (x*100+y);
}

class BarbarianInvasion
{
public:
	int minimalDetachment(vector <string> countryMap, vector <int> detachmentSize);
};

int BarbarianInvasion::minimalDetachment(vector <string> countryMap, vector <int> detachmentSize)
{
	vector< vector<couple> > country;
	vector<couple> row;
	row.assign(countryMap[0].size()+2,couple(0,0));
	country.assign(countryMap.size()+2,row);

	map<int,couple> directory;

	couple capital;

	for(int i=0; i<countryMap.size(); ++i)
	{
		for(int j=0; j<countryMap[0].size(); ++j)
		{
			if(countryMap[i][j] == '*')
			{
				capital = couple(i+1,j+1);
				country[i+1][j+1] = couple(100,get_id(i,j));
				directory[get_id(i,j)] = couple(i+1,j+1);
			}
			else if(countryMap[i][j] != '-')
			{
				country[i+1][j+1] = couple(countryMap[i][j] - 64,get_id(i,j));
				directory[get_id(i,j)] = couple(i+1,j+1);
			}
			else
			{
				country[i+1][j+1] = couple(-1,get_id(i,j));;
				directory[get_id(i,j)] = couple(i+1,j+1);
			}
		}
	}
		
	vector< vector<int> > routes;
	stack<strouple> notHandled;
	vector<int> temp;
	notHandled.push(strouple(capital,temp));
	set<strouple> found;

	while(notHandled.size()>0)
	{
		strouple current = notHandled.top();
		couple cur_node = current.first;
		vector<int> path = current.second;
		notHandled.pop();

		int x = cur_node.first;
		int y = cur_node.second;

		set<int> found_now;
		for(int iter=0; iter<path.size(); ++iter)
			found_now.insert(path[iter]);
		found_now.insert(country[capital.first][capital.second].second);

		if(at_border(cur_node,country))
			routes.push_back(path);
		else
		{
			for(int i=-1; i<=1; i+=2)
			{
				vector<int> new_path1 = path;
				vector<int> new_path2 = path;
				new_path1.push_back(country[x+i][y].second);
				new_path2.push_back(country[x][y+i].second);
				if((country[x+i][y].first != -1) && (found.find(strouple(couple(x+i,y),new_path1))==found.end()) && (found_now.find(country[x+i][y].second)==found_now.end()))
				{
					notHandled.push(strouple(couple(x+i,y),new_path1));
				}
				if((country[x][y+i].first != -1) && (found.find(strouple(couple(x,y+i),new_path2))==found.end()) && (found_now.find(country[x][y+i].second)==found_now.end()))
				{
					notHandled.push(strouple(couple(x,y+i),new_path2));
				}
			}
		}
	}
	
	for(int i=0; i<routes.size(); ++i)
	{
		for(int j=i; j<routes.size(); ++j)
		{
			if(i==j)
				continue;
			int min_len,common = -1;
			if(routes[i].size() < routes[j].size())
				min_len = routes[i].size();
			else
				min_len = routes[j].size();
			for(int k=0; k<min_len; ++k)
			{
				if(routes[i][k]!=routes[j][k])
					break;
				else
				{
					common++;
				}
			}
			if(common!=-1)
			{
				vector<int> temp;
				routes[i] = temp;
				routes[j].erase(routes[j].begin()+common+1,routes[j].end());
			}
		}
	}

	int cost = 0;
	for(int i=0; i<routes.size(); ++i)
	{
		if(routes[i].size()>0)
		{
			int min = 100000;
			couple mindex;
			for(int j=0; j<routes[i].size(); ++j)
			{
				couple current = directory[routes[i][j]];
				int target = country[current.first][current.second].first-1;
				if(detachmentSize[target] < min)
				{
					min = detachmentSize[target];
					mindex = current;
				}
			}
			cost += detachmentSize[country[mindex.first][mindex.second].first-1];
		}
	}

	return cost;

}

int main()
{
	BarbarianInvasion lala;
	vector<string> map;
	map.push_back("-A-----");
	map.push_back("-BCCC*-");
	map.push_back("-A-----");

	vector<int> army;
	army.push_back(1);
	army.push_back(5);
	army.push_back(10);

	lala.minimalDetachment(map,army);

	return 0;
}
