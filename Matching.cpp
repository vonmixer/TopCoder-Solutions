//SRM 176 Div 1 Easy
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

class Matching
{
public:
	vector <string> findMatch(vector <string> first, vector <string> second);
};

int next_num(int a, int b)
{
	if(a+b == 4)
		return 2;
	if(a+b == 3)
		return 3;
	if(a+b == 5)
		return 1;
}

vector <string> Matching::findMatch(vector <string> first, vector <string> second)
{
	vector<string> answer = first;
	vector< map<int,string> > params;
	map<int,string> dummy;
	params.assign(4,dummy);

	params[0][1] =  "CIRCLE";
	params[0][2] =  "SQUIGGLE";
	params[0][3] =  "DIAMOND";
	params[1][1] =  "RED";
	params[1][2] =  "BLUE";
	params[1][3] =  "GREEN";
	params[2][1] =  "SOLID";
	params[2][2] =  "STRIPED";
	params[2][3] =  "EMPTY";
	params[3][1] =  "ONE";
	params[3][2] =  "TWO";
	params[3][3] =  "THREE";

	for(int i=0; i<4; ++i)
	{
		if(first[i]!=second[i])
		{
			int vals[2];
			int pos = 0;
			for(int j=1; j<4; ++j)
			{
				string temp = params[i][j];
				if((temp == first[i]) || (temp == second[i]))
				{
					vals[pos] = j;
					pos++;
				}
			}
			int next = next_num(vals[0],vals[1]);
			answer[i] = params[i][next];
		}
			
	}

	return answer;
}

int main()
{
	Matching lala;
	vector <string> a0;
	vector <string> a1;
	a0.push_back("CIRCLE");
	a0.push_back("GREEN");
	a0.push_back("EMPTY");
	a0.push_back("TWO");
	a1.push_back("DIAMOND");
	a1.push_back("BLUE");
	a1.push_back("STRIPED");
	a1.push_back("ONE");
	lala.findMatch(a0,a1);
	return 0;
}
