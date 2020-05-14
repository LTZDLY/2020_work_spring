#pragma once
#include <cmath>
#include <iomanip>
#include <iostream>

class Point
{
private:
	int x_;
	int y_;

public:
	Point() :x_(0), y_(0) {}
	Point(int x, int y);
	
	int GetX()const { return x_; }
	int GetY()const { return y_; }

	Point& Set(int new_x, int new_y);
	double Distance(const Point& point)const;
	void PrintDistance(const Point& point)const;
};

