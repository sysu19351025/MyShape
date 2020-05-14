#include"ShapeFile.h"
#include<iostream>
#include<string>
#include"Shape.h"
using namespace std;

ShapeFile::ShapeFile(ifstream& sf) {
	string line;
	vector<Point> points;
	while (getline(sf, line)) {
		if (line.size() > 0 && line[0] == '#') continue;
		size_t i;
		if (line.find("Circle") != string::npos) {
			i = line.find("P");
			size_t j = line.find(",");
			int num = stoi(string(line, i + 1, j - i - 1));
			double r = stod(string(line, j + 1));
			shared_ptr<Circle> cp(new Circle(points.at(num), r));
			shapes_.push_back(cp);
		}
		if (line.find("Polygon") != string::npos) {
			size_t j = 0;
			vector<Point> Polyps;
			while ((i=line.find_first_of("P",j)!=string::npos))
			{
				j = line.find_first_of(",", i);
				int num = stoi(string(line, i + 1, j - i - 1));
				Polyps.push_back(points.at(num));
			}
			shared_ptr<Polygon> pp(new Polygon(Polyps));
			shapes_.push_back(pp);
		}
		if ((i = line.find_first_of("(")) != string::npos) {
			size_t j = line.find_first_of(",", i);
			string str1(line, i + 1, j - i - 1);
			i = line.find_first_of(")");
			string str2(line, j + 1, i - j - 1);
			points.push_back(Point(stod(str1), stod(str2)));
		}
	}
}

void ShapeFile::Generate() {

}
void ShapeFile::Print() {
	for (size_t i = 0; i < shapes_.size(); i++) {
		shapes_.at(i)->Print();
	}
}