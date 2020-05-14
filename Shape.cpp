#include<iostream>
#include <memory>
#include"Edge.h"
#include"Shape.h"
#define PI 3.1415926
using namespace std;

// class Point
Point::Point(double x,double y):x_(x),y_(y){}
void Point::Print() const {
	cout << "(" << x_ << "," << y_ << ")" << ends;
}

// class Edge
Edge::Edge(Point p1, Point p2):p1_(p1),p2_(p2){}
double Edge::Length() const {
	return sqrt((p1_.x_ - p2_.x_) * (p1_.x_ - p2_.x_) + (p1_.y_ - p2_.y_) * (p1_.y_ - p2_.y_));
}
void Edge::Print() const {
	cout << "P1:";
	p1_.Print();
	cout << "P2:";
	p2_.Print();
}
// calculate the area of a triangle.
double operator *(const Point& p, const Edge& e) {
	double v1x = e.p1_.x_ - p.x_, v1y = e.p1_.y_ - p.y_;
	double v2x = e.p2_.x_ - e.p1_.x_, v2y = e.p2_.y_ - e.p1_.y_;
	return (v1x * v2y - v2x * v1y) / 2;
}


// class Composite Shape
void CompositeSp::Print() const {
	cout << "c = " << circ_ << " \ts = " << area_ << endl;
}

// class Circle
Circle::Circle(Point p, double r) :center_(p), radius_(r) {}
double Circle::Circumference() const{
	if (IsValid()) return radius_ * 2 * PI;
	else return UnknownValue;
}
double Circle::Area() const{
	if (IsValid()) return radius_ * radius_ * PI;
	else return UnknownValue;
}
void Circle::Print() const{
	if (!IsValid())
		cout << "Invalid Circle" << endl;
	cout << "Center:";
	center_.Print();
	cout << "R = " << radius_ << " Area = " << Area() << endl;
}

// class Polygon
Polygon::Polygon(vector<Point> ps) {
	size_t i = 1;
	for (; i < ps.size(); i++) {
		edges_.push_back(new Edge(ps[i - 1], ps[i]));
	}
	// needs 1 Point in "ps" at least!
	edges_.push_back(new Edge(ps.at(i - 1), ps[0]));
}
Polygon::Polygon(vector<Edge> es) {
	for (size_t i = 0; i < es.size(); i++) {
		edges_.push_back(new Edge(es.at(i)));
	}
}
Polygon::~Polygon() {
	int s = edges_.size() - 1;
	for (; s >= 0; s--) {
		delete edges_.at(s);
	}
	edges_.clear();
}
double Polygon::Circumference() const {
	if (!IsValid()) return UnknownValue;
	double c = 0;
	for (size_t i = 0; i < edges_.size(); i++) {
		c += edges_.at(i)->Length();
	}
	return c;
}
double Polygon::Area() const {
	if (!IsValid()) return UnknownValue;
	size_t i = 1;
	double area = 0;
	for (; i < edges_.size() - 1; i++) {
		area += edges_.at(0)->p1_ * (*edges_.at(i));
	}
	return area > 0 ? area : -area;
}
bool Polygon::IsValid() const {
	if (edges_.size() < 3) return false;
	if (edges_.at(0)->p1_ != edges_.at(edges_.size() - 1)->p2_) return false;
	for (size_t i = 0; i < edges_.size() - 1; i++)
		if (edges_.at(i)->p2_ != edges_.at(i + 1)->p1_) return false;
	return true;
}
void Polygon::Print() const {
	if (!IsValid())
		cout << "Invalid Polygon" << endl;
	cout << "Edges:" << endl;
	for (size_t i = 0; i < edges_.size(); i++) {
		cout << "Edge" << i + 1 << ":";
		edges_.at(i)->Print();
		cout << endl;
	}
	cout << "\nC = " << Circumference() << "\nS = " << Area() << endl;
}

// operator reload
shared_ptr<Shape> operator |(const shared_ptr<Shape>& s1, const shared_ptr<Shape>& s2) {
	if (typeid(s1) == typeid(s2)) {

		if (typeid(s1) == typeid(shared_ptr<Circle>)) {
			Circle c1 = *(dynamic_pointer_cast<Circle>(s1)), c2 = *(dynamic_pointer_cast<Circle>(s2));
			double dist = sqrt((c1.CtrX() - c2.CtrX()) * (c1.CtrX() - c2.CtrX()) + (c1.CtrY() - c2.CtrY()) * (c1.CtrY() - c2.CtrY()));
			double Rmax = c1.R() > c2.R() ? c1.R() : c2.R();
			double Rmin = c1.R() < c2.R() ? c1.R() : c2.R();
			if (dist >= Rmax + Rmin) {	// Both of c1 & c2
				shared_ptr<CompositeSp> p(new CompositeSp(c1.Circumference() + c2.Circumference(), c1.Area() + c2.Area()));
				return p;
			}
			if (dist <= Rmax - Rmin) {	// the larger circle
				shared_ptr<Circle> p(new Circle(c1.R() == Rmax ? c1 : c2));
				return p;
			}
			double Amin = 2 * acos((Rmin * Rmin + dist * dist - Rmax * Rmax) / (2 * Rmin * dist));
			double Amax = 2 * acos((Rmax * Rmax + dist * dist - Rmin * Rmin) / (2 * Rmax * dist));
			double C = c1.Circumference() + c2.Circumference() - (Amin * Rmin + Amax * Rmax);
			double S = c1.Area() + c2.Area() - (Amin - sin(Amin)) * Rmin * Rmin / 2 - (Amax - sin(Amax) * Rmax * Rmax / 2);
			shared_ptr<CompositeSp> p(new CompositeSp(C,S));
			return p;
		}

		if (typeid(s1) == typeid(shared_ptr<Polygon>)) {
			shared_ptr<Polygon> p(new Polygon(*(dynamic_pointer_cast<Polygon>(s1)) | *s2));
			return p;
		}
	}

	// calculate omitted
	shared_ptr<CompositeSp> p(new CompositeSp());
	return p;
}
shared_ptr<Shape> operator &(const shared_ptr<Shape>& s1, const shared_ptr<Shape>& s2) {
	if (typeid(s1) == typeid(s2)) {

		if (typeid(s1) == typeid(shared_ptr<Circle>)) {
			Circle c1 = *(dynamic_pointer_cast<Circle>(s1)), c2 = *(dynamic_pointer_cast<Circle>(s2));
			double dist = sqrt((c1.CtrX() - c2.CtrX()) * (c1.CtrX() - c2.CtrX()) + (c1.CtrY() - c2.CtrY()) * (c1.CtrY() - c2.CtrY()));
			double Rmax = c1.R() > c2.R() ? c1.R() : c2.R();
			double Rmin = c1.R() < c2.R() ? c1.R() : c2.R();
			if (dist >= Rmax + Rmin) {	// empty set
				shared_ptr<CompositeSp> p(new CompositeSp());
				return p;
			}
			if (dist <= Rmax - Rmin) {	// the smaller circle
				shared_ptr<Circle> p(new Circle(c1.R() == Rmin ? c1 : c2));
				return p;
			}
			double Amin = 2 * acos((Rmin * Rmin + dist * dist - Rmax * Rmax) / (2 * Rmin * dist));
			double Amax = 2 * acos((Rmax * Rmax + dist * dist - Rmin * Rmin) / (2 * Rmax * dist));
			double C = Amin * Rmin + Amax * Rmax;
			double S = (Amin - sin(Amin)) * Rmin * Rmin / 2 + (Amax - sin(Amax) * Rmax * Rmax / 2);
			shared_ptr<CompositeSp> p(new CompositeSp(C, S));
			return p;
		}

		if (typeid(s1) == typeid(shared_ptr<Polygon>)) {
			shared_ptr<Polygon> p(new Polygon(*(dynamic_pointer_cast<Polygon>(s1)) & *s2));
			return p;
		}
	}
	
	// calculate omitted
	shared_ptr<CompositeSp> p(new CompositeSp());
	return p;
}

Polygon Polygon::operator |(const Shape& s) {
	// calculation omitted
	return Polygon();
}
Polygon Polygon::operator &(const Shape& s) {
	// calculation omitted
	return Polygon();
}