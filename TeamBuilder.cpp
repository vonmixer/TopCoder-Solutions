//SRM 184 Div 2 1000
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class TeamBuilder
{
public:
	vector<int> specialLocations(vector <string> paths);
};

int min(int a, int b)
{
	if(a<b)
		return a;
	else
		return b;
}

vector<int> TeamBuilder::specialLocations(vector <string> paths)
{
	vector< vector<int> > team;
	vector<int> row;
	row.assign(paths.size(), 0);
	team.assign(paths.size(), row);

	for(int i=0; i< paths.size(); ++i)
	{
		for(int j=0; j<paths.size(); ++j)
		{
			if(paths[i][j] == '1')
				team[i][j] = 1;
			else
				team[i][j] = 100;
			if(i==j)
				team[i][j] = 100;
		}
	}

	for(int k=0; k<team.size(); ++k)
	{
		for(int i=0; i<team.size(); ++i)
		{
			for(int j=0; j<team.size(); ++j)
			{
				if(i!=j)
					team[i][j] = min(team[i][k] + team[k][j],team[i][j]);
			}
		}
	}

	vector<int> result;
	result.assign(2,0);

	for(int i=0; i<team.size(); ++i)
	{
		int num_ones = 0;
		for(int j=0; j<team.size();++j)
		{
			if(team[i][j] < 100)
				num_ones++;
		}
		if(num_ones==team.size()-1)
			result[0]++;
	}

	for(int i=0; i<team.size(); ++i)
	{
		int num_ones = 0;
		for(int j=0; j<team.size();++j)
		{
			if(team[j][i] < 100)
				num_ones++;
		}
		if(num_ones==team.size()-1)
			result[1]++;
	}

	return result;
}

int main()
{
	TeamBuilder lala;

	vector<string> input;
	input.push_back("0110000");
	input.push_back("1000100");
	input.push_back("0000001");
	input.push_back("0010000");
	input.push_back("0110000");
	input.push_back("1000010");
	input.push_back("0001000");

	lala.specialLocations(input);

}