#include<iostream>
#include<math.h>
#include<iomanip>
#include<list>
using namespace std;
//CPoint
class CPoint {
private:
	int x;
	int y;
public:
	CPoint() {};
	CPoint(int a, int b)
	{
		x = a;
		y = b;
	}
	void Set(int, int);
	inline int GetX() { return x; }
	inline int GetY() { return y; }
	double euclidean_dis(int, int);
	void print_dis(int, int);
};

void CPoint::Set(int a, int b)
{
	x = a;
	y = b;
}
double CPoint::euclidean_dis(int x2, int y2)
{
	auto dis = sqrt(pow(x2 - this->x, 2) + pow(y2 - this->y, 2));//自动就是double
	return dis;
}
void CPoint::print_dis(int x2, int y2)
{
	double dis = 0;
	dis = this->euclidean_dis(x2, y2);
	cout << fixed << setprecision(2) << dis;//小数点后两位
}

class CRectangle
{
private:
	CPoint left_up;
	CPoint right_down;
public:
	CRectangle() {};
	CRectangle(const CPoint a, const CPoint b)
	{
		left_up = a;
		right_down = b;
	}
	void Set(const CPoint a, const CPoint b)
	{
		left_up = a;
		right_down = b;
	}
	inline int rec_perimeter();
	inline int rec_area();
	inline void print_all();
	bool is_rect();
};
inline int CRectangle::rec_perimeter()
{
	int Perimeter = 0;
	Perimeter = abs(this->left_up.GetX() - this->right_down.GetX()) * 2 + abs(this->left_up.GetY() - this->right_down.GetY()) * 2;
	return Perimeter;
}

inline int CRectangle::rec_area()
{
	int area = 0;
	area = abs(this->left_up.GetX() - this->right_down.GetX()) * abs(this->left_up.GetY() - this->right_down.GetY());
	return area;
}

inline void CRectangle::print_all()
{
	CPoint left_down, right_up;
	left_down.Set(left_up.GetX(), right_down.GetY());
	right_up.Set(right_down.GetX(), left_up.GetY());
	cout << "vertices: "
		<< '(' << left_up.GetX() << ',' << left_up.GetY() << ')' << ' '
		<< '(' << right_up.GetX() << ',' << right_up.GetY() << ')' << ' '
		<< '(' << right_down.GetX() << ',' << right_down.GetY() << ')' << ' '
		<< '(' << left_down.GetX() << ',' << left_down.GetY() << ')' << endl;
	cout << "perimeter: " << this->rec_perimeter() << endl;
	cout << "area: " << this->rec_area() << endl;
}

bool CRectangle::is_rect()
{
	return this->rec_perimeter() > 0;
}
//rectangle

class CMylist
{
private:
	list<CRectangle> rect_list;
public:
	CMylist(){}
	CMylist(list<CRectangle>& temp_list)
		:rect_list(temp_list)
	{}
	~CMylist() {
		rect_list.clear();//清空
	}
	bool append(CRectangle&);
	bool pop(int);
	void print_rectangle();
};

bool CMylist::append(CRectangle& rect)
{
	if (!rect.is_rect())
	{
		cerr << "This rectangle is wrong" << endl;
		return -1;
	}//如果插入的不符合矩形，便不插入；
	if (rect_list.empty())
	{
		rect_list.push_back(rect);
		return true;
	}//如果是空的直接插入
	else
	{
		list<CRectangle>::iterator iter;
		list<CRectangle>::iterator iter_end;
		iter = rect_list.begin();
		iter_end = rect_list.end();
		for (; iter != iter_end;)
		{
			if (iter->rec_area() > rect.rec_area() || (iter->rec_area() == rect.rec_area() && iter->rec_perimeter() > rect.rec_perimeter()))
			{
				iter++;//不符合条件，下一个
			}
			else
			{
				rect_list.insert(iter, rect);
				return true;
			}
		}
		if (iter == iter_end)
		{
			rect_list.push_back(rect);
			return true;
		}//最小，直接最后一个
	}
}

bool CMylist::pop(int n)
{
	int gold_num = n;
	list<CRectangle>::iterator iter;
	if (n <= 0 || n>rect_list.size())
	{
		cerr << "The n is error";
		return false;
	}
	else
	{
		iter = rect_list.begin();
		while (--n)
		{
			iter++;
		}
		rect_list.erase(iter);
		cout << "you deleted the num " << gold_num << " rectangle" << endl;
		return true;
	}
}

void CMylist::print_rectangle()
{
	list<CRectangle>::iterator iter;
	list<CRectangle>::iterator iter_end;
	int print_num = 1;
	iter = rect_list.begin();
	iter_end = rect_list.end();
	//list里面的矩阵小于三个
	if (rect_list.size() < 3)
	{
		while (iter != iter_end)
		{
			cout << print_num << endl;
			iter->print_all();
			iter++;
			print_num++;
		}
	}
	//list里的矩阵大于等于三个
	else
	{
		for (int ix = 0; ix < 3; ix++)
		{
			cout << print_num << endl;
			iter->print_all();
			iter++;
			print_num++;
		}
	}
}
int main()
{
	CPoint p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;
	p1.Set(0, 4); p2.Set(4, 0); p3.Set(0, 3); p4.Set(3, 0); p5.Set(0, 5); p6.Set(5, 0), p7.Set(1, 4), p8.Set(6, 2), p9.Set(1, 1), p10.Set(1, 1);
	CRectangle rect1, rect2, rect3, rect4, rect6;
	rect1.Set(p1, p2);
	rect2.Set(p3, p4);
	rect3.Set(p5, p6);
	rect4.Set(p7, p8);
	rect6.Set(p9, p10);
	CRectangle rect5(rect2);
	CMylist mylist;
	mylist.append(rect6);
	mylist.append(rect1);
	mylist.append(rect2);
	mylist.append(rect3);
	mylist.append(rect4);
	mylist.append(rect5);
	mylist.print_rectangle();
	mylist.pop(1);//删除第一个矩阵
	mylist.print_rectangle();
	return 0;
	
}