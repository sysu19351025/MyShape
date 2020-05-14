#include"Edge.h"
#include"Shape.h"
#include"ShapeFile.h"
#include<iostream>
using namespace std;

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