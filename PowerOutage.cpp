//SRM 144 (Division II Level Three)
#include <vector>
#include <map>
#include <string>
using namespace std;

class PowerOutage
{
public:
	int estimateTimeOut(vector <int> fromJunction, vector <int> toJunction, vector <int> ductLength);
};

int PowerOutage::estimateTimeOut(vector <int> fromJunction, vector <int> toJunction, vector <int> ductLength)
{
	map<int,int> tree;
	int total_cost = 0;
	int deepest = 0;
	int deepest_id;

	tree[0]=0;
	for(int i=0; i<fromJunction.size(); ++i)
	{
		if(tree.find(toJunction[i])==tree.end())
		{
			int lastlen = tree[fromJunction[i]];
			tree[toJunction[i]]=lastlen+ductLength[i];
			total_cost+=ductLength[i];
			if(deepest<lastlen+ductLength[i])
			{
				deepest = lastlen+ductLength[i];
				deepest_id = toJunction[i];
			}
		}
	}
	
	int best_time=2*total_cost - tree[deepest_id];
	return best_time;
}

int main()
{
	PowerOutage lala;
	vector<int> from;
	vector<int> to;
	vector<int> len;

	int temp[] = {0,0,0,1,4,4,6,7,7,7,20};
	for(int i=0; i<11; ++i)
		from.push_back(temp[i]);

	int temp2[] = {1,3,4,2,5,6,7,20,9,10,31};
	for(int i=0; i<11; ++i)
		to.push_back(temp2[i]);

	int temp3[] = {10,10,100,10,5,1,1,100,1,1,5};
	for(int i=0; i<11; ++i)
		len.push_back(temp3[i]);

	lala.estimateTimeOut(from,to,len);
	return 0;
}