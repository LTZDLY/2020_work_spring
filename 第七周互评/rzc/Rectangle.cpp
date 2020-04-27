#include "Rectangle.h"

Rectangle::Rectangle(const Point& top_left_vertex, const Point& bottom_right_vertex)
{
	if (!CheckInput(top_left_vertex, bottom_right_vertex))
	{
		std::cerr << "Wrong input! This rectangle will be initialized by default constructor.\n";
		top_left_vertex_ = bottom_right_vertex_ = Point();
	}
	else
	{
		top_left_vertex_ = top_left_vertex;
		bottom_right_vertex_ = bottom_right_vertex;
	}
}

Rectangle::Rectangle(int x1, int y1, int x2, int y2)
{
	if (!CheckInput({ x1,y1 }, { x2,y2 }))
	{
		std::cerr << "Wrong input! This rectangle will be initialized by default constructor.\n";
		top_left_vertex_ = bottom_right_vertex_ = Point();
	}
	else
	{
		top_left_vertex_ = { x1,y1 };
		bottom_right_vertex_ = { x2,y2 };
	}
}

bool Rectangle::operator<(const Rectangle& rhs)const
{
	if (this->CalArea() == rhs.CalArea())
	{
		return this->CalPerimeter() < rhs.CalPerimeter();
	}
	return this->CalArea() < rhs.CalArea();
}

bool Rectangle::CheckInput(const Point& top_left_vertex, const Point& bottom_right_vertex)
{
	if ((top_left_vertex.GetX() < bottom_right_vertex.GetX()) && (top_left_vertex.GetY() > bottom_right_vertex.GetY()))
	{
		return true;
	}
	return false;
}

int Rectangle::CalPerimeter()const
{
	return 2 * ((top_left_vertex_.GetY() - bottom_right_vertex_.GetY()) + bottom_right_vertex_.GetX() - top_left_vertex_.GetX());
}

int Rectangle::CalArea()const
{
	return (top_left_vertex_.GetY() - bottom_right_vertex_.GetY())*(bottom_right_vertex_.GetX() - top_left_vertex_.GetX());
}

void Rectangle::Print()const
{
	std::cout << "vertices: "
		<< '(' << top_left_vertex_.GetX() << ',' << top_left_vertex_.GetY() << ") "
		<< '(' << bottom_right_vertex_.GetX() << ',' << top_left_vertex_.GetY() << ") "
		<< '(' << bottom_right_vertex_.GetX() << ',' << bottom_right_vertex_.GetY() << ") "
		<< '(' << top_left_vertex_.GetX() << ',' << bottom_right_vertex_.GetY() << ")\n";

	std::cout << "perimeter: " << CalPerimeter() << '\n';
	std::cout << "area: " << CalArea() << '\n';
	std::cout << '\n';
}