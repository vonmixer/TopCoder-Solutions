//TCI '02 Semifinals 2 (Division I Level Two)
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

void swap(int& a,int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

class Node
{
	int x;
	int y;
	int dist;

public:
	Node(int a, int b): x(a), y(b), dist(0) {};
	Node(int a, int b, int c): x(a), y(b), dist(c) {};
	int getx() const { return x;}
	int gety() const { return y;}
	int getlen() const { return dist;}
};

class NodeCmp
{
public:
	bool operator()(Node& a, Node& b) { return a.getlen()>b.getlen();}
};

class Escape
{
public:
	int lowest(vector <string> harmful, vector <string> deadly);
};

int Escape::lowest(vector <string> harmful, vector <string> deadly)
{
	vector< vector<int> > field;
	vector<int> row;
	row.assign(501,0);
	field.assign(501,row);

	vector< vector<bool> > visits;
	vector<bool> col;
	col.assign(501,false);
	visits.assign(501,col);

	for(int i=0; i<harmful.size(); ++i)
	{
		istringstream ss(harmful[i]);
		int x1,y1,x2,y2;
		ss >> x1 >> y1 >> x2 >> y2;
		if(x1>x2)
			swap(x1,x2);
		if(y1>y2)
			swap(y1,y2);
		for(int hor = x1; hor<=x2; hor++)
		{
			for(int ver=y1; ver<=y2; ver++)
			{
				if(field[hor][ver]<1)
					field[hor][ver]=1;
			}
		}			
	}

	for(int i=0; i<deadly.size(); ++i)
	{
		istringstream ss(deadly[i]);
		int x1,y1,x2,y2;
		ss >> x1 >> y1 >> x2 >> y2;
		if(x1>x2)
			swap(x1,x2);
		if(y1>y2)
			swap(y1,y2);
		for(int hor = x1; hor<=x2; hor++)
		{
			for(int ver=y1; ver<=y2; ver++)
			{
				if(field[hor][ver]<2)
					field[hor][ver]=2;
			}
		}			
	}

	priority_queue<Node,vector<Node>,NodeCmp> foundNotHandled;

	foundNotHandled.push(Node(0,0,0));

	
	while(foundNotHandled.empty()==false)
	{
		Node current = foundNotHandled.top();
		foundNotHandled.pop();
		int x = current.getx();
		int y = current.gety();

		if(x==500 && y==500)
			return current.getlen();

		for(int i=-1; i<=1; i+=2)
		{
			if(x+i>=0 && x+i<=500)
			{
				if((field[x+i][y]<2) && !visits[x+i][y])
				{
					foundNotHandled.push(Node(x+i,y,current.getlen()+field[x+i][y]));
					visits[x+i][y] = true;
				}
			}
			if(y+i>=0 && y+i<=500)
			{
				if((field[x][y+i]<2) && !visits[x][y+i])
				{
					foundNotHandled.push(Node(x,y+i,current.getlen()+field[x][y+i]));
					visits[x][y+i] = true;
				}
			}
		}
		cout << foundNotHandled.size() << endl;
	}

	return -1;
}

int main()
{
	vector<string> harmful;
	harmful.push_back("500 0 0 500");
	vector<string> deadly;
	deadly.push_back("0 0 0 0");

	Escape grid;
	int x = grid.lowest(harmful,deadly);

	return 0;
}