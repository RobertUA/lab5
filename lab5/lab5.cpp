#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
#define MAX 129266
#define PI 3.1415926535
#define R 6371

double Distance(double width1, double long1, double width2, double long2);

struct Place
{
	double width;
	double height;
	string type;
	string undertype;
	string name;
	string address;
};

Place* readplace(ifstream& file, double& w1, double& l1, double& w2, double& l2)
{
	Place* coor = new Place[MAX];
	string s;
	setlocale(0, "ukr");
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
		if (coor[i].width < w1) w1 = coor[i].width;
		else if (coor[i].width > w2) w2 = coor[i].width;
		if (coor[i].height < l1) l1 = coor[i].height;
		else if (coor[i].height > l2) l2 = coor[i].height;
		//cout << "[" << i << "] " << coor[i].width << " " << coor[i].height << " " << coor[i].type << " " << coor[i].undertype << " " << coor[i].name << " " << coor[i].address << "\n";
	}
	return coor;
}
class Tree3
{
private:
	int count = 0;
	double width1, long1, width2, long2;
	Place* place;
public:
	void set(double minw1, double minl1, double maxw2, double maxl2)
	{
		width1 = minw1;
		long1 = minl1;
		width2 = maxw2;
		long2 = maxl2;
		place = new Place[MAX];
		cout << "set Tree3\n";
	}
	void Put(Place newplace)
	{
		place[count] = newplace;
		count++;
		//cout << "Put Tree3\n";
	}
};
class Tree2
{
private:
	double DIST;
	double width1, long1, width2, long2;
	Tree3* tree3;
public:
	void set(double minw1, double minl1, double maxw2, double maxl2, double dist)
	{
		DIST = dist;
		width1 = minw1;
		long1 = minl1;
		width2 = maxw2;
		long2 = maxl2;
		tree3 = new Tree3[(width2 - width1) / DIST + (long2 - long1) / DIST + 2];
		cout << "set Tree2\n";
		Create();
	}
	void Create()
	{
		int C = 0;
		for (double i = width1; i < width2; i += DIST)
		{
			for (double j = long1; j < long2; j += DIST)
			{
				tree3[C].set(i, j, i + DIST, j + DIST);
				C++;
			}
		}
		cout << "Create Tree2\n";
	}
	void Put(Place newplace)
	{
		int C = 0;
		for (double i = width1; i < width2; i += DIST)
		{
			for (double j = long1; j < long2; j += DIST)
			{
				if (i < newplace.width && j < newplace.height
					&& i + DIST >= newplace.width && j + DIST >= newplace.height)
					tree3[C].Put(newplace);

				C++;
			}
		}
		//cout << "PUT Tree2\n";
	}
};
class Tree1
{
private:
	double DIST;
	double width1, long1, width2, long2;
	Tree2* tree2;
public:
	void set(double minw1, double minl1, double maxw2, double maxl2, double dist)
	{
		DIST = dist;
		width1 = minw1;
		long1 = minl1;
		width2 = maxw2;
		long2 = maxl2;
		tree2 = new Tree2[(width2 - width1) / DIST * 10 + (long2 - long1) / DIST * 10];
		cout << "set Tree1\n";
		Create();
	}
	void Create()
	{
		int C=0;
		for (double i = width1; i < width2; i += DIST * 10)
		{
			for (double j = long1; j < long2; j += DIST * 10)
			{
				tree2[C].set(i, j, i + DIST, j + DIST, DIST);
				C++;
			}
		}
		cout << "Create Tree1\n";
	}
	void Put(Place newplace)
	{
		int C = 0;
		for (double i = width1; i < width2; i += DIST * 10)
		{
			for (double j = long1; j < long2; j += DIST * 10)
			{
				if(i<newplace.width && j<newplace.height 
					&& i+DIST*10 >= newplace.width && j+DIST*10 >= newplace.height)
						tree2[C].Put(newplace);
				
				C++;
			}
		}
		//cout << "PUT Tree1\n";
	}
};

int main()
{
	double w1=INT_MAX, l1=INT_MAX, w2=-1, l2=-1;
	ifstream file("ukraine_poi.csv");
	Place* coor = readplace(file, w1, l1, w2, l2);
	Tree1 tree;
	tree.set(w1, l1, w2, l2, 10);
	for (int i = 0; i < MAX; i++)
	{
		tree.Put(coor[i]);
	}
	return 1;
}

double Distance(double width1, double long1, double width2, double long2)
{
	width1 = (width1 / 180) * PI;
	width2 = (width2 / 180) * PI;
	long1 = (long1 / 180) * PI;
	long2 = (long2 / 180) * PI;
	double Avgwidth = (width1 + width2) / 2;
	return R*sqrt((width2-width1)*(width2-width1) 
		+ (cos(Avgwidth)*(long2-long1)) 
		* (cos(Avgwidth)*(long2-long1)));
}