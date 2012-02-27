//SRM 534 Div 2 Easy
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

class EllysDirectoryListing
{
public:
	vector <string> getFiles(vector <string> files);
};

vector <string> EllysDirectoryListing::getFiles(vector <string> files)
{
	int count = 0;
	for(int i=0; i<files.size()-3; ++i)
	{
		if(i>0)
		{
			if(files[i-1] == "." || files[i-1] == "..")
				i--;
		}
		if(count == 2)
			return files;
		if(files[i] == "." || files[i] == "..")
		{
			if(count ==0)
			{
				string temp = files[i];
				files[i] = files[files.size()-1];
				files[files.size()-1] = temp;
			}
			if(count ==1)
			{
				string temp = files[i];
				files[i] = files[files.size()-2];
				files[files.size()-2] = temp;
			}
			count++;
		}
	}
	return files;
}

int main()
{
	EllysDirectoryListing lala;
	vector <string> a0;
	a0.push_back("ContestApplet.jnlp");
	a0.push_back("..");
	a0.push_back(".");
	lala.getFiles(a0);
	return 0;
}
