#pragma once
#ifndef __SHAPEFILE_H__
#define __SHAPEFILE_H__
#include <memory>
#include <fstream>
#include <vector>

class Shape;
class ShapeFile{
public:
	ShapeFile(std::ifstream& sf);
	void Print() const;

private:
	void Generate();	// called only once by the constructor

	std::vector<std::shared_ptr<Shape>> shapes_;
	std::vector<std::shared_ptr<Shape>> compositeShapes_;
};

#endif // !__SHAPEFILE_H__
