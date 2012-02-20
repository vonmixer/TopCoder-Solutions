//SRM 160 Division I Level Two
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <queue>

using namespace std;

class Quilting
{
public:
	string lastPatch(int length, int width, vector <string> colorList);
};

pair<int,int> next_pos(vector< vector<int> > quilt, pair<int,int> last, bool start = false)
{
	int x = last.first;
	int y = last.second;

	if(start)
		return pair<int,int>(x-1,y);
	if((quilt[x+1][y]>=0) && (quilt[x][y-1]==-1))
		return pair<int,int>(x,y-1);
	if((quilt[x+1][y]==-1) && (quilt[x][y+1]>=0))
		return pair<int,int>(x+1,y);
	if((quilt[x-1][y]>=0) && (quilt[x][y+1]==-1))
		return pair<int,int>(x,y+1);
	if((quilt[x][y-1]>=0) && (quilt[x-1][y]==-1))
		return pair<int,int>(x-1,y);
}

int get_val(vector< vector<int> > quilt, pair<int,int> pos)
{
	int x = pos.first;
	int y = pos.second;
	if(x<1 || x>=quilt.size()-1 || y<1 || y>=quilt[0].size()-1)
		return -1;
	else
		return quilt[x][y];
}

int rule2(map<int,int> count,vector<int> current)
{
	int min = 10000;
	vector<int> current2;

	for(int i=0; i<current.size(); ++i)
	{
		if(count[current[i]]<min)
		{
			min = count[current[i]];
			current2.clear();
			current2.push_back(current[i]);
		}
		else if(count[current[i]]==min)
			current2.push_back(current[i]);
	}

	if(current2.size()==1)
		return current2[0];
	else
	{
		int mindex = 10000;
		for(int i=0; i<current2.size(); ++i)
		{
			if(current2[i]<mindex)
				mindex = current2[i];
		}
		return mindex;
	}

}

in*t rule1(map<int,int> count,vector< vector<int> > quilt, pair<int,int> next)
{
	vector<pair<int,int> > neighbors;
	for(map<int,int>::const_iterator it = count.begin(); it!=count.end(); ++it)
		neighbors.push_back(pair<int,int>(it->first,0));

	int min = 10000;
	vector<int> current;
	for(int i=-1; i<=1; ++i)
	{
		for(int j=-1; j<=1; ++j)
		{
			int val = get_val(quilt,pair<int,int>(next.first+i,next.second+j));
			if(val!=-1)
				neighbors[val].second++;
		}
	}
	for(int i = 0; i<neighbors.size(); ++i)
	{
		if(neighbors[i].second<min)
		{
			min = neighbors[i].second;
			current.clear();
			current.push_back(i);
		}
		else if(neighbors[i].second==min)
			current.push_back(i);
	}
	if(current.size()==1)
		return current[0];
	else
		return rule2(count,current);
}

string Quilting::lastPatch(int length, int width, vector <string> colorList)
{
	map<int,int> count;
	vector< vector<int> > quilt;
	vector<int> col;
	vector<int> sentinel;
	col.assign(width+2,-1);
	sentinel.assign(width+2,-2);
	col[0] = -2;
	col[width+1] = -2;
	quilt.assign(length+2,col);
	quilt[0] = sentinel;
	quilt[length+1] = sentinel;

	int progress = 0;
	for(int i=0; i<colorList.size(); ++i)
		count[i] = 0;

	pair<int,int> current;
	current.first = (length)/2+1;
	current.second = (width)/2+1;
	bool start = true;
	int last_put;
	while(progress < length*width)
	{
		progress++;
		quilt[current.first][current.second] = rule1(count,quilt,current);
		last_put = quilt[current.first][current.second];
		count[last_put]++;
		if(progress < length*width)
			current = next_pos(quilt,current,start);
		start = false;
	}

	return colorList[last_put];
}

int main()
{
	Quilting lala;

	vector<string> colorList;
	colorList.push_back("X");
	colorList.push_back("Y");
	colorList.push_back("Z");

	lala.lastPatch(10,10,colorList);
}