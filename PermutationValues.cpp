//SRM 161 Div 1 Hard
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

int factorial(int val)
{
	if(val == 1)
		return 1;
	else
		return val*factorial(val-1);
}

class PermutationValues
{
	long long target;
public:
	bool permute(vector<int> vals, string& progress,string& final, int& count,bool done);
	vector <int> getValues(vector <int> lows, vector <int> highs, string lexPos, vector <string> retInts);
};

bool PermutationValues::permute(vector<int> vals, string& progress, string& final, int& count,bool done=false)
{
	if(vals.empty())
	{
		count++;
		if(count==target)
		{
			final = progress;
			done = true;
		}
		return done;
	}

	for(int i=0; i<vals.size(); ++i)
	{
		if(done)
			return true;
		stringstream ss;
		ss << vals[i] << ",";
		int cache = vals[i];
		string prog2 = progress+ss.str();
		vals.erase(vals.begin()+i);
		done = permute(vals,prog2,final,count,done);
		vals.insert(vals.begin()+i,cache);
	}

	return false;
}

vector <int> PermutationValues::getValues(vector <int> lows, vector <int> highs, string lexPos, vector <string> retInts)
{
	vector<int> lala;
	vector<int> hola;

	for(int i=0; i<lows.size(); ++i)
	{
		for(int j=lows[i]; j<=highs[i]; ++j)
			lala.push_back(j);
	}
		
	stringstream ss(lexPos);
	int max = factorial(lala.size());
	ss >> target;
	if(target > max)
		target = target%max;

	int init = -1;
	string dummy,final;
	permute(lala,dummy,final,init);

	vector<int> perms;
	int temp;
	char garbage;
	stringstream vv(final);
	while(vv >> temp >> garbage)
		perms.push_back(temp);

	for(int i=0; i<retInts.size(); ++i)
	{
		stringstream ll(retInts[i]);
		int val;
		ll >> val;
		hola.push_back(perms[val]);
	}

	return hola;
}


int main()
{
	PermutationValues lala;
	vector <int> a0;
	vector <int> a1;
	string a2;
	vector <string> a3;
	a0.push_back(-1000000000);
	a0.push_back(500000);
	a1.push_back(0);
	a1.push_back(2000000000);
	a2="99999999999999999";
	a3.push_back("2999500000");
	a3.push_back("1234123");
	a3.push_back("123344");
	a3.push_back("9293939");
	a3.push_back("2999500001");
	a3.push_back("2999499950");
	lala.getValues(a0,a1,a2,a3);
	return 0;
}
