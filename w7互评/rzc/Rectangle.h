#pragma once
#include "Point.h"

class Rectangle
{
private:
	Point top_left_vertex_;
	Point bottom_right_vertex_;
public:
	Rectangle() :
		top_left_vertex_(), bottom_right_vertex_() {}
	Rectangle(const Point& top_left_vertex, const Point& bottom_right_vertex);
	Rectangle(int x1, int y1, int x2, int y2);

	bool operator<(const Rectangle& rhs)const;
	bool CheckInput(const Point& top_left_vertex,const Point& bottom_right_vertex);

	int CalPerimeter()const;
	int CalArea()const;
	void Print()const;
};

