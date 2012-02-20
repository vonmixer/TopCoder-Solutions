//SRM 184 (Division II Level One)
#include <string>
#include <iostream>
#include <math.h>
#include <sstream>

using namespace std;


class RaceApproximator
{
public:
	string timeToBeat(int d1, int t1, int d2, int t2, int raceDistance);
};

string RaceApproximator::timeToBeat(int d1, int t1, int d2, int t2, int raceDistance)
{
	//T1*e^(ln(T2/T1)*ln(D1/D)/ln(D1/D2))
	double time1 = t1;
	double time2 = t2;
	double dis1 = d1;
	double dis2 = d2;
	double raceTime = time1*exp(log(time2/time1)*log(dis1/raceDistance)/log(dis1/dis2));

	int hours = raceTime/3600;
	int mins = (raceTime - hours*3600)/60;
	int secs = raceTime - hours*3600 - mins*60;

	ostringstream ss;
	ss << hours << ":";
	if(mins<10)
		ss << 0 << mins << ":";
	else
		ss << mins << ":";

	if(secs<10)
		ss << 0 << secs;
	else
		ss << secs;
	
	string out = ss.str();

	return out;
}

int main()
{
	RaceApproximator timer;
	timer.timeToBeat(800,118,5000,906,1500);

	return 0;
}