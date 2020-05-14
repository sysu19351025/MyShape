#pragma once
#ifndef __EDGE_H__
#define __EDGE_H__

struct Point {
	double x_,y_;

	Point():x_(0),y_(0) {}
	Point(double x, double y);
	void Print() const;

	bool operator !=(Point p) const {
		return x_ != p.x_ || y_ != p.y_;
	}
	bool operator ==(Point p) const {
		return x_ == p.x_ && y_ == p.y_;
	}

};

struct Edge {
	Point p1_, p2_;

	Edge(){}
	Edge(Point p1, Point p2);
	double Length() const;
	void Print() const;

	friend double operator *(const Point& p, const Edge& e);
};
#endif // !__EDGE_H__
