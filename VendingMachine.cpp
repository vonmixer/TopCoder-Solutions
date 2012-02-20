//SRM 145 (Division I Level Two , Division II Level Three)
#include <vector> 
#include <map>
#include <string>
#include <sstream>

using namespace std;

class Time
{
	int time;

public:
	Time(const int num): time(num) {};
	void increment(const int num) { time+=num;}
	int get_time() const { return time;}
	void set_time(const int num) {time=num;}
};

class VendingMachine
{
	vector< vector<int> > cylinder;
	vector<int> totals;
	int current_col;
	int max_col;
	Time total_time;
	Time motor_time;
	Time last_purchase;
public:	
	VendingMachine() : total_time(0), motor_time(0), last_purchase(0), current_col(0) {};
	int motorUse(vector <string> prices, vector <string> purchases);
	void set_totals();
	void move_to_max();
	int purchase(const int,const int,const int);
};

void VendingMachine::set_totals()
{
	vector<int> temp_totals(cylinder[0].size(),0);
	totals = temp_totals;
	int max = 0;
	max_col = 0;
	for(int i=0; i<cylinder[0].size();++i)
	{
		for(int j=0; j<cylinder.size(); ++j)
		{
			totals[i] += cylinder[j][i];
		}
		if(totals[i]>max)
		{
			max = totals[i];
			max_col = i;
		}
	}
}

void VendingMachine::move_to_max()
{
	int diff=0;
	if(max_col<current_col)
	{
		int max_col2 = max_col+cylinder[0].size();
		if(max_col2 - current_col > current_col - max_col)
			diff = current_col - max_col;
		else
			diff = max_col2 - current_col;
	}
	if(max_col>current_col)
	{
		int max_col2 = max_col-cylinder[0].size();
		if(current_col - max_col2 > max_col - current_col)
			diff = max_col - current_col;
		else
			diff = current_col - max_col2;
	}
	current_col = max_col;
	total_time.increment(diff);
	motor_time.increment(diff);
}

int VendingMachine::purchase(const int row, const int col,const int time)
{
	int this_time = time*60;
	total_time.set_time(this_time);
	if(total_time.get_time() - last_purchase.get_time() >=300)
		move_to_max();

	int diff=0;
	if(col<current_col)
	{
		int col2 = col+cylinder[0].size();
		if(col2 - current_col > current_col - col)
			diff = current_col - col;
		else
			diff = col2 - current_col;
	}
	if(col>current_col)
	{
		int col2 = col-cylinder[0].size();
		if(current_col - col2 > col - current_col)
			diff = col - current_col;
		else
			diff = current_col - col2;
	}
	current_col = col;
	total_time.increment(diff);
	motor_time.increment(diff);
	last_purchase.set_time(this_time);

	if(cylinder[row][col]==0)
		return -1;
	cylinder[row][col]=0;
	set_totals();
	return 1;
}

int VendingMachine::motorUse(vector<string> prices, vector<string> purchases)
{
	for(int i=0; i<prices.size();++i)
	{
		istringstream ss(prices[i]);
		vector<int> shelf;
		int temp;
		while(ss >> temp)
			shelf.push_back(temp);
		cylinder.push_back(shelf);
	}

	set_totals();
	move_to_max();

	for(int i=0; i<purchases.size(); ++i)
	{
		int row,col,time;
		char delim;
		stringstream ss(purchases[i]);
		ss >> row >> delim >> col >> delim >> time;
		if(purchase(row,col,time) < 0)
			return -1;
	}
	move_to_max();

	return motor_time.get_time();
}

int main()
{
	VendingMachine VH;
	vector<string> data,purses;
	data.push_back("100 200 300 400 500 600");
	purses.push_back("0,2:0");
	purses.push_back("0,3:5");
	purses.push_back("0,1:10");
	purses.push_back("0,4:15");
	VH.motorUse(data,purses);

	return 0;
}

