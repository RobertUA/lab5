#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

#define MAX 129266
#define PI 3.1415926535
#define R 6371

class Tree2;
class Tree1;
struct Place;

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

class Tree2
{
private:
	int count = 0;
	Place* place = new Place [MAX];
public:
	void Put(Place newplace)
	{
		place[count] = newplace;
		count++;
	}
	void Find(double w, double l, int dist)
	{
		int cc=0;
		for (int i = 0; i < count; i++)
		{
			//cout << Distance(w, l, place[i].width, place[i].height) << endl;
			if (Distance(w, l, place[i].width, place[i].height) <= dist)
			{
				//cout << i << ") ";
				cout << place[i].type
					<< " " << place[i].undertype << " " 
					<< place[i].name << " " << place[i].address << endl;
				cc++;
			}
		}
		cout << endl << "COUNT: " <<  cc;
	}
};

class Tree1
{
private:
	int DIST;
	double width1, width2, long1, long2;
	Tree2* tree2;
public:
	Tree1(double w1, double l1, double w2, double l2, int dist)
	{
		DIST = dist;
		width1 = w1;
		long1 = l1;
		width2 = w2;
		long2 = l2;
		/*cout << (width2 - width1) * (long2 - long1) / DIST + 1;*/															if (DIST <= 5) DIST = 6;
		tree2 = new Tree2[int((width2 - width1) * (long2 - long1) / DIST + 1)];
	}
	void Put(Place newplace)
	{
		int C = 0;
		for (double i = width1; i <= width2; i += DIST)
		{
			for (double j = long1; j <= long2; j += DIST)
			{
				if (i <= newplace.width && i + DIST > newplace.width
					&& j <= newplace.height && j + DIST > newplace.height)
						tree2[C].Put(newplace);
				C++;
				//cout << i << " " << j;
			}
		}
		//cout << "PUT 1\n";
	}
	void Find(double w, double l, int dist)
	{
		int C = 0;
		for (double i = width1; i <= width2; i += DIST)
		{
			for (double j = long1; j <= long2; j += DIST)
			{
				if (i <= w && i + DIST > w
					&& j <= l && j + DIST > l)
						tree2[C].Find(w, l, dist);
				C++;
			}
		}
	}

};

int main()
{
	double w1=INT_MAX, l1=INT_MAX, w2=-1, l2=-1;
	ifstream file("ukraine_poi.csv");
	int DIST;
	double width, longg;
	cout << "Print Width, Long and Radius: ";
	cin >> width >> longg >> DIST;
	cout << "\nRead...\n";
	Place* coor = readplace(file, w1, l1, w2, l2);
	cout << "Create and search...\n";
	Tree1 tree(w1, l1, w2, l2, DIST);
	for (int i = 0; i < MAX; i++)
	{
		tree.Put(coor[i]);
	}
	//cout << "Search...\n";
	tree.Find(width, longg, DIST);
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