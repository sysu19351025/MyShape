#pragma once
#ifndef __SHAPE_H__
#define __SHAPE_H__
#include<vector>
#include <memory>
#include"Edge.h"

class Shape {
public:
	virtual ~Shape() {};
	virtual double Circumference() const = 0 ;
	virtual double Area() const = 0;
	virtual void Print() const = 0;
	virtual bool IsValid() const { return true; }
	static const int UnknownValue = -1;
};
std::shared_ptr<Shape> operator |(const std::shared_ptr<Shape>& s1, const std::shared_ptr<Shape>& s2);
std::shared_ptr<Shape> operator &(const std::shared_ptr<Shape>& s1, const std::shared_ptr<Shape>& s2);

class CompositeSp :public Shape {
	double circ_ = UnknownValue, area_ = UnknownValue;
public:
	CompositeSp() {}
	CompositeSp(double circ,double area): area_(area),circ_(circ) {}
	double Circumference() const override { return circ_; }
	double Area() const override { return area_; }
	void Print() const override;
	bool IsValid() const override { return circ_ != UnknownValue && area_ != UnknownValue; }
};

class Circle :public Shape {
	Point center_;
	double radius_;
public:
	Circle():radius_(UnknownValue),center_(Point(0,0)) {}
	Circle(Point p,double r);
	~Circle(){}
	double CtrX() { return center_.x_; }
	double CtrY() { return center_.y_; }
	double R() { return radius_; }
	virtual double Circumference() const override;
	virtual double Area() const override;
	virtual void Print() const override;
	virtual bool IsValid() const override {
		return radius_ >= 0; }
};

class Polygon :public Shape {
public:
	Polygon() {}
	Polygon(std::vector<Point> ps);
	Polygon(std::vector<Edge> es);
	~Polygon();
	virtual double Circumference() const override;
	virtual double Area() const override;
	virtual void Print() const override;
	virtual bool IsValid() const override;

	Polygon operator |(const Shape& s);
	Polygon operator &(const Shape& s);
private:
	std::vector<Edge*> edges_;
};


#endif // !__SHAPE_H__
