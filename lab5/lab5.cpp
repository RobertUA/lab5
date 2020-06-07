#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
#define MAX 129266
#define PI 3.1415926535
#define R 6371

double Distance(double weight1, double long1, double weight2, double long2);

struct place
{
	double width;
	double height;
	string type;
	string undertype;
	string name;
	string address;
};
place* readplace(ifstream& file)
{
	place* coor = new place[MAX];
	string s;
	setlocale(LC_ALL, "ukr"); //короче это штука очень важная
	ofstream f("d:\\M.txt");
	for (int i = 0; i < MAX; i++)
	{
		getline(file, s, ';');
		coor[i].width = atof(s.c_str());
		getline(file, s, ';');
		coor[i].height = atof(s.c_str());
		getline(file, s, ';');
		coor[i].type = s;
		getline(file, s, ';');
		coor[i].undertype = s;
		getline(file, s, ';');
		coor[i].name = s;
		getline(file, s, ';');
		coor[i].address = s;
		//cout << "[" << i << "] " << coor[i].width << " " << coor[i].height << " " << coor[i].type << " " << coor[i].undertype << " " << coor[i].name << " " << coor[i].address << "\n";
	}
	cout << endl << fixed << Distance(49, 33, 49.35, 34.32);
	return coor;
}

int main()
{
	ifstream file("ukraine_poi.csv");
	place* coor = readplace(file);
}

double Distance(double weight1, double long1, double weight2, double long2)
{
	weight1 = (weight1 / 180) * PI;
	weight2 = (weight2 / 180) * PI;
	long1 = (long1 / 180) * PI;
	long2 = (long2 / 180) * PI;
	double AvgWeight = (weight1 + weight2) / 2;
	return R*sqrt((weight2-weight1)*(weight2-weight1) 
		+ (cos(AvgWeight)*(long2-long1)) 
		* (cos(AvgWeight)*(long2-long1)));
}