#include "Point.h"

Point::Point(int x, int y)
{
	this->x_ = x;
	this->y_ = y;
}

Point& Point::Set(int new_x, int new_y)
{
	this->x_ = new_x;
	this->y_ = new_y;
	return *this;
}

double Point::Distance(const Point& point)const
{
	return sqrt((x_ - point.GetX())*(x_ - point.GetX()) + (y_ - point.GetY())*(y_ - point.GetY()));
}

void Point::PrintDistance(const Point& point)const
{
	std::cout << '(' << this->GetX() << ',' << this->GetY() << ")*"
		<< '(' << point.GetX() << ',' << point.GetY() << ")="
		<< ' ' << setiosflags(std::ios::fixed) << std::setprecision(2) << Distance(point) << '\n';
	std::cout << '\n';
}