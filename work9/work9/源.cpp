#define PI acos(-1)
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
using std::vector;
using std::string;

class Shape {
public:
	virtual double GetArea() = 0;
	virtual double GetPeri() = 0;
	static int getVertexCount(Shape *s);
protected:
	double area_;
	int vertexCount;
	Shape();
};
class Rectangle :public Shape {
public:
	Rectangle();
	Rectangle(const Rectangle&);
	Rectangle(const int, const int, const int, const int);
	virtual double GetArea();
	virtual double GetPeri();
	void Adjust(int);
	int CheckInclude(Rectangle);
	string Print();
private:
	std::pair<int, int> upper_left_;
	std::pair<int, int> upper_right_;
	std::pair<int, int> lower_left_;
	std::pair<int, int> lower_right_;
	int width_;
	int height_;
};
class Circle :public Shape {
public:
	Circle();
	Circle(int, int, int);
	virtual double GetArea();
	virtual double GetPeri();
private:
	std::pair<int, int> center_;
	int radius_;
};

Shape::Shape() {
	vertexCount = -1;
}
inline int Shape::getVertexCount(Shape *s) { return s->vertexCount; }

Rectangle::Rectangle() {
	upper_left_ = { 0,0 };
	upper_right_ = { 0,0 };
	lower_left_ = { 0,0 };
	lower_right_ = { 0,0 };
	area_ = width_ = height_ = 0;
	vertexCount = 4;
}
Rectangle::Rectangle(const Rectangle& rec) {
	upper_left_ = rec.upper_left_;
	upper_right_ = rec.upper_right_;
	lower_left_ = rec.lower_left_;
	lower_right_ = rec.lower_right_;
	width_ = rec.width_;
	height_ = rec.height_;
	area_ = rec.area_;
	vertexCount = 4;
}
Rectangle::Rectangle(const int upper_left_x, const int upper_left_y, const int lower_right_x, const int lower_right_y) {
	upper_left_ = { upper_left_x,upper_left_y };
	upper_right_ = { lower_right_x,upper_left_y };
	lower_left_ = { upper_left_x,lower_right_y };
	lower_right_ = { lower_right_x,lower_right_y };
	width_ = abs(upper_left_x - lower_right_x);
	height_ = abs(upper_left_y - lower_right_y);
	area_ = GetArea();
	vertexCount = 4;
}
inline double Rectangle::GetArea() { return (width_ * height_); }
inline double Rectangle::GetPeri() { return (2 * (width_ + height_)); }
void Rectangle::Adjust(int area) {
	area_ = area;
	int temp = sqrt(area);
	int height = temp;
	int width = height;
	while (true) {
		int area_temp = height * width;
		if (area_temp == area) break;
		else if (area_temp < area) height++;
		else if (area_temp > area) {
			width--;
			height = temp;
		}
	}
	lower_right_ = { upper_left_.first + width,upper_left_.second - height };
	upper_right_ = { lower_right_.first,upper_left_.second };
	lower_left_ = { upper_left_.first,lower_right_.second };
	height_ = height;
	width_ = width;
}
int Rectangle::CheckInclude(const Rectangle rec) {
	int lenth = std::min(rec.lower_right_.first, lower_right_.first) - std::max(rec.upper_left_.first, upper_left_.first);
	int width = std::min(rec.upper_left_.second, upper_left_.second) - std::max(rec.lower_right_.second, lower_right_.second);
	int area = lenth * width;
	if (area <= 0) return -1;
	return area;
}
string Rectangle::Print() {
	std::stringstream ss;
	ss << "(" << upper_left_.first << ", " << upper_left_.second << ") "
		<< "(" << upper_right_.first << ", " << upper_right_.second << ") "
		<< "(" << lower_left_.first << ", " << lower_left_.second << ") "
		<< "(" << lower_right_.first << ", " << lower_right_.second << ") ";
	return ss.str();
}

Circle::Circle() {
	center_ = { 0,0 };
	area_ = radius_ = 0;
	vertexCount = 0;
}
Circle::Circle(int x, int y, int r) {
	center_ = { x,y };
	radius_ = r;
	area_ = GetArea();
	vertexCount = 0;
}
inline double Circle::GetArea() { return (PI * radius_ * radius_); }
inline double Circle::GetPeri() { return (2 * PI * radius_); }

void CommandInputRec(vector<Rectangle>&);
void CommandDetermineRec(vector<Rectangle>&);
void CommandAdjustRec(vector<Rectangle>&);
void StringSplit(const string, vector<string>&, const string);
void loop();

int main() {
	loop();
	return 0;
}

void loop() {
	using std::cout;
	using std::cin;
	using std::endl;
	cout << "W9" << endl
		<< "Use number to choose what you want to do." << endl
		<< "1: Input a rectangle." << endl
		<< "2: Determine if two rectangles have overlapping parts." << endl
		<< "3: Adjust a rectangle." << endl
		<< "Enter any other to exit the program." << endl << endl
		<< "To input a rectangle, you will need to enter the coordinates of the upper left and lower right points of the rectangle like this:" << std::endl
		<< "upper_left.x  upper_left.y  lower_right.x  lower_right.y" << endl << endl
		<< "To Determine if two rectangles have overlapping parts, you will need to enter the number you want to determine." << endl
		<< "To Adjust a rectangle, you will need to enter the number and the area you want to adjust." << endl
		<< "Have your time!" << endl;
	vector<Rectangle> obj;
	int temp = 0;
	cout << "Now enter your command." << endl;
	while (cin >> temp) {
		switch (temp) {
		case 1:
			CommandInputRec(obj);
			break;
		case 2:
			CommandDetermineRec(obj);
			break;
		case 3:
			CommandAdjustRec(obj);
			break;
		default:
			return;
		}
		cout << "Now enter your command." << endl;
	}
}
void CommandInputRec(vector<Rectangle>& obj) {
	std::cout << "command 1: enter a rectangle." << std::endl;
	string temp_str;
	while (true) {
		while (temp_str.size() == 0)std::getline(std::cin, temp_str);
		int dir = 0;
		vector<string> text_spilt;
		StringSplit(temp_str, text_spilt, " ");
		if (text_spilt.size() == 4) {
			int x1, y1, x2, y2;
			std::istringstream input_buf(temp_str);
			if (!(input_buf >> x1 >> y1 >> x2 >> y2)) {
				std::cout << "ERROR: Invalid input detected, please try again.";
				return;
			}
			Rectangle temp_rec(x1, y1, x2, y2);
			obj.push_back(std::move(temp_rec));
			std::cout << "Add success! The number of the rectangle is " << obj.size() << "." << std::endl;
			return;
		}
	}
}
void CommandDetermineRec(vector<Rectangle>& obj) {
	std::cout << "command 2: Determine if two rectangles have overlapping parts." << std::endl;
	int a, b;
	while (std::cin >> a >> b) {
		if (a <= 0 || b <= 0) {
			std::cout << "ERROR: Invalid input detected, please try again." << std::endl;
			return;
		}
		if (a > obj.size() || b > obj.size()) {
			std::cout << "ERROR: There are not enough matricse here, please try again." << std::endl;
			return;
		}
		a--;
		b--;
		auto area = obj[a].CheckInclude(obj[b]);
		if (area == -1) std::cout << "The two rectangles do not overlap." << std::endl;
		else std::cout << "The overlapping area of the two rectangles is " << area << "." << std::endl;
		return;
	}
}
void CommandAdjustRec(vector<Rectangle>& obj) {
	std::cout << "command 3: Adjust a rectangle." << std::endl;
	int temp;
	int area;
	while (std::cin >> temp >> area) {
		if (temp <= 0) {
			std::cout << "ERROR: Invalid input detected, please try again." << std::endl;
			return;
		}
		if (temp > obj.size()) {
			std::cout << "ERROR: There are not enough matricse here, please try again." << std::endl;
			return;
		}
		temp--;
		obj[temp].Adjust(area);
		std::cout << "Adjust success! the rectangle after adjust is" << std::endl << obj[temp].Print() << std::endl;
		return;
	}
}
void StringSplit(const string s, vector<string>& v, const string c) {
	//Use string c to split string s into x parts, store them in vector v and return.
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2) {
		v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}