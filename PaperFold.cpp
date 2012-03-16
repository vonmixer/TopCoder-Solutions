//SRM 162 Div 1
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

typedef pair<int,int> couple;

int min(int a, int b)
{
	if(a<b)
		return a;
	else
		return b;
}

class PaperFold
{
	couple pap;
	couple cont;
public:
	int numFolds(vector <int> paper, vector <int> box);
	int fold(couple sheet,int count);
};

int PaperFold::fold(couple sheet,int count)
{
	if(count == 8)
	{
		return 100;
	}
	if((sheet.first<=cont.first && sheet.second<=cont.second) || (sheet.second<=cont.first && sheet.first<=cont.second))
		return count;
	return min(fold(couple(sheet.first/2,sheet.second),count+1),fold(couple(sheet.first,sheet.second/2),count+1));
}

int PaperFold::numFolds(vector <int> paper, vector <int> box)
{
	pap.first = paper[0];
	pap.second = paper[1];
	cont.first = box[0];
	cont.second = box[1];

	int result = fold(pap,0);
	if(result==100)
		result = -1;
	return result;
}

int main()
{
	PaperFold lala;
	vector <int> a0;
	vector <int> a1;
	a0.push_back(1895);
	a0.push_back(6416);
	a1.push_back(401);
	a1.push_back(1000);
	lala.numFolds(a0,a1);
	return 0;
}
