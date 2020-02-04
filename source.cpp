#include <iostream>
#include "MPQ.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

struct skyline
{
	int x;
	int height;
	int label;
	string def_of_build;
	skyline(int x,int h,int l,string d):x(x),height(h),label(l),def_of_build(d){}
};
void sort(vector<skyline> &x,skyline temp)
{
	for (int i = 0; i<x.size(); i++)
	{
		for (int j = i + 1; j<x.size(); j++)
		{
			if (x[i].x>x[j].x)
			{
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}
		}
	}
}
int main()
{
	vector<skyline> apartment;
	ifstream x;
	string file = "input.txt";
	int value;
	x.open(file.c_str());
	x.clear();
	x.seekg(0);
	string line;
	getline(x, line);
	istringstream num_of_build(line);
	num_of_build >> value;

	MPQ<int> queue(value * 2+1);

	while (getline(x, line))
	{
		int x_s, x_e, h, label;
		istringstream coordinate(line);
		coordinate >> x_s >> h >> x_e;
		label = sqrt(pow(x_s, 2) + 2 * x_s*h*x_e + pow(x_e, 2));
		skyline s(x_s,h,label,"start");
		skyline e(x_e, h, label, "end");
		apartment.push_back(s);
		apartment.push_back(e);		
	}
	skyline temp(0,0,0,"start");
	sort(apartment, temp);
	
	for (int i = 0; i < apartment.size(); i++) // go over the inputs
	{
		if (apartment[0].x != 0&&i<1) // if x=0 cord is empty
			cout << "0"<<" "<<"0" << endl;
		if (apartment[i].def_of_build == "end") // if it is end point
		{
			int height = queue.deleteMax(apartment[i].label); // delete the ended building
			if (height > queue.findMax() && apartment[i + 1].x != apartment[i].x)
				cout << apartment[i].x << " " << queue.findMax() << endl;
			else if (queue.IsEmpty())
				cout << apartment[i].x << " " << "0" << endl;
		}
		else if (apartment[i].def_of_build == "start") // if it is starting point
		{
			if (queue.findMax() < apartment[i].height || queue.IsEmpty()) // height changed
				cout << apartment[i].x << " " << apartment[i].height << endl;
			queue.insert(apartment[i].height, apartment[i].label); // insert the new building
		}
	}


	return 0;
}