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
			shared_ptr<Circle> cp(new Circle(points.at(num - 1), r));
			shapes_.push_back(cp);
		}
		if (line.find("Polygon") != string::npos) {
			size_t j = line.find(":");
			vector<Point> Polyps;
			while ((i=line.find_first_of("P",j))!=string::npos)
			{
				j = line.find_first_of(",", i);
				int num = stoi(string(line, i + 1, j - i - 1));
				Polyps.push_back(points.at(num - 1));
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
	Generate();
}
void ShapeFile::Generate() {
	for (size_t i = 0; i < shapes_.size() - 1; i++) {
		for (size_t j = i + 1; j < shapes_.size(); j++) {
			auto sp1 = shapes_.at(i) | shapes_.at(j);
			auto sp2 = shapes_.at(i) & shapes_.at(j);
			if (sp1->IsValid()) compositeShapes_.push_back(sp1);
			if (sp2->IsValid()) compositeShapes_.push_back(sp2);
		}
	}
}

void ShapeFile::Print() const {
	cout << "------Shapes------" << endl;
	for (size_t i = 0; i < shapes_.size(); i++) {
		if (dynamic_pointer_cast<Circle>(shapes_.at(i))) cout << "---Circle---" << endl;
		if (dynamic_pointer_cast<Polygon>(shapes_.at(i))) cout << "---Polygon---" << endl;
		shapes_.at(i)->Print();
		cout << endl;
	}
	cout << "------Composite Shapes------" << endl;
	for (size_t i = 0; i < compositeShapes_.size(); i++) {
		if (dynamic_pointer_cast<Circle>(compositeShapes_.at(i))) cout << "---Circle---" << endl;
		if (dynamic_pointer_cast<Polygon>(compositeShapes_.at(i))) cout << "---Polygon---" << endl;
		if (dynamic_pointer_cast<CompositeSp>(compositeShapes_.at(i))) cout << "---Odd Shape---" << endl;
		compositeShapes_.at(i)->Print();
		cout << endl;
	}
}