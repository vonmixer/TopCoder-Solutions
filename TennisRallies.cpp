#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

class TennisRallies
{
public:
	int howMany(int numLength, vector <string> forbidden, int allowed);
};

int countRallies(int numLength,int pos, string sequence, vector<string>& FD,int allowed, int sofar)
{
	if(pos == numLength)
		return 1;
	int count = 0;
	int sofar1 = sofar;
	int sofar2 = sofar;

	for(int i=0; i<FD.size(); ++i)
	{
		int len = FD[i].size();
		if(len>sequence.size())
			continue;

		string case1 = sequence.substr(sequence.size() - len,len-1) +"c";
		if(case1.find(FD[i]) != string::npos)
			sofar1++;
		
		string case2 = sequence.substr(sequence.size() - len,len-1) +"d";
		if(case2.find(FD[i]) != string::npos)
			sofar2++;
	}

	if(sofar1 < allowed)
		count += countRallies(numLength, pos+1, sequence+"c", FD,allowed,sofar1);

	if(sofar2 < allowed)
		count += countRallies(numLength, pos+1, sequence+"d", FD,allowed,sofar2);

	return count;	
}

int TennisRallies::howMany(int numLength, vector <string> forbidden, int allowed)
{
	int res = countRallies(numLength,0,"",forbidden,allowed,0);
	return res;
}

int main()
{
	TennisRallies lala;
	int a0;
	vector <string> a1;
	int a2;
	a0=18;
	a1.push_back("c");
	//a1.push_back("dd");
	a2=100;
	lala.howMany(a0,a1,a2);
	return 0;
}
