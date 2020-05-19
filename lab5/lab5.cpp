#include <iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
#define MAX 129269

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
	}
	return coor;
}

int main()
{
	ifstream file("d:\\ukraine_poi.csv");
	place* coor = readplace(file);
}