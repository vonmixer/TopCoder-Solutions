//SRM 176 Div 1 Hard
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>
#include <math.h>

using namespace std;

typedef pair<double,double> coord;

class Watchtower
{
public:
	vector <int> orderByArea(vector <int> x, vector <int> y);
};

double calc_dist(coord a,coord b)
{
	return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}

vector <int> Watchtower::orderByArea(vector <int> x, vector <int> y)
{
	vector<int> count;
	vector<int> order;
	count.assign(x.size(),0);

	for(int i=0; i<101; ++i)
	{
		for(int j=0; j<101; ++j)
		{
			double min_dist = 10000;
			int min_pos;
			for(int k = 0; k<count.size(); ++k)
			{
				if(calc_dist(coord(i,j),coord(x[k],y[k])) <= min_dist)
				{
					min_dist = calc_dist(coord(i,j),coord(x[k],y[k]));
					min_pos = k;
				}
			}
			count[min_pos]++;
		}
	}

	for(int i = 0; i<count.size(); ++i)
		order.push_back(i);

	for(int i = 0; i<order.size(); ++i)
	{
		for(int j = i; j<order.size(); ++j)
		{
			if(count[i]<count[j])
			{
				int temp = count[i];
				count[i] = count[j];
				count[j] = temp;
				temp = order[i];
				order[i] = order[j];
				order[j] = temp;
			}
		}	
	}

	return order;
}

int main()
{
	Watchtower lala;
	vector <int> a0;
	vector <int> a1;
	a0.push_back(10);
	a0.push_back(40);
	a0.push_back(50);
	a0.push_back(50);
	a0.push_back(90);
	a1.push_back(10);
	a1.push_back(40);
	a1.push_back(50);
	a1.push_back(75);
	a1.push_back(50);
	lala.orderByArea(a0,a1);
	return 0;
}
