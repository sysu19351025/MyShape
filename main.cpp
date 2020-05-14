#include"Edge.h"
#include"Shape.h"
#include"ShapeFile.h"
#include<iostream>
using namespace std;
/*vector<Point> Ps;
	
	Ps.push_back(Point(0, 2));
	Ps.push_back(Point(1, 2));
	Ps.push_back(Point(1, 1));
	Ps.push_back(Point(2, 1));
	Ps.push_back(Point(2, 0));
	Ps.push_back(Point(0, 0));

	Ps.push_back(Point(0, 1));
	Ps.push_back(Point(1, 1));
	Ps.push_back(Point(1, 0));
	Ps.push_back(Point(-1, 0));
	Ps.push_back(Point(-1, -1));
	Ps.push_back(Point(0, -1));
	Polygon p1(Ps);
	cout << p1.Area() << endl;
	Point pt1(1, 1), pt2(-2, -3), pt3(4, 5);*/

int main(int argc, char** argv) {
	// input file.
	ifstream infile;
	if (!(infile.open(argv[1]), infile) || argc < 2) {
		cerr << "No input file!" << endl;
		return -1;
	}
	
	ShapeFile sfile(infile);

	sfile.Print();
	return 0;
}