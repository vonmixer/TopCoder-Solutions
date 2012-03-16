#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

class IsHomomorphism
{
public:
	vector <string> numBad(vector <string> source, vector <string> target, vector <int> mapping);
};

vector <string> IsHomomorphism::numBad(vector <string> source, vector <string> target, vector <int> mapping)
{
	vector<int> row;
	row.assign(source[0].size(),0);
	vector< vector<int> > smap;
	vector< vector<int> > tmap;
	smap.assign(source.size(),row);
	tmap.assign(source.size(),row);
	vector<string> answer;

	for(int i=0; i<source.size(); ++i)
	{
		for(int j=0; j<source.size(); ++j)
		{
			smap[i][j] = source[i][j] - 48;
			tmap[i][j] = target[i][j] - 48;
		}
	}

	for(int i=0; i<source.size(); ++i)
	{
		int first = mapping[i];
		for(int j=0; j<source.size(); ++j)
		{
			int second = mapping[j];
			if(tmap[first][second] != mapping[smap[i][j]])
			{
				stringstream ss;
				ss << "(" << i << "," << j << ")";
				answer.push_back(ss.str());
			}
		}
	}

	return answer;
}

int main()
{
	IsHomomorphism lala;
	vector <string> a0;
	vector <string> a1;
	vector <int> a2;
	a0.push_back("0000");
	a0.push_back(
 "0123");
	a0.push_back(
 "0202");
	a0.push_back(
 "0321");
	a1.push_back("0000");
	a1.push_back(
 "0123");
	a1.push_back(
 "0202");
	a1.push_back(
 "0321");
	a2.push_back(0);
	a2.push_back(1);
	a2.push_back(2);
	a2.push_back(3);
	lala.numBad(a0,a1,a2);
	return 0;
}
