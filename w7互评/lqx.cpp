#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <utility>
#include <stdio.h>

using namespace std;
//8然point里面用不了cin，就难顶

class Point {
	friend class Rectangle;
private:
	int x, _x;
	int y, _y;
	double length;
	void Set(int x, int y) {
		this->_x = x2;
		this->_y = y2;
	}
	void outputPoint(double length) {
		cout << "(" << x << "," << y << ")*(" << _x << "," << _y << ") = ";
		printf("%.2f\n", length);
	}
public:
	int x2, y2;
	int len = 0, high = 0;
	Point() {};
	Point(int x1, int y1) {
		//用给定的参数创造点，x1，y1由main传入
		this->x = x1;
		this->y = y1;
	}
	void Get() {
		cin >> x2;
		getchar();
		cin >> y2;
		Set(x2, y2);
	}
	void EuclidDistance() {
		len = sqrt((x - _x) * (x - _x));
		high = sqrt((y - _y) * (y - _y));
		length = sqrt((len * len) + (high * high));
		outputPoint(length);
	}
}point;

class Rectangle
{
public:
	int per;
	int are;
	int perimeter()
	{
		point.len = sqrt((point.x - point._x) * (point.x - point._x));
		point.high = sqrt((point.y - point._y) * (point.y - point._y));
		return 2 * (point.len + point.high);
	}

	int area()
	{
		point.len = sqrt((point.x - point._x) * (point.x - point._x));
		point.high = sqrt((point.y - point._y) * (point.y - point._y));
		return point.len * point.high;
	}

	void outputRectangular()
	{
		if (point.x > point._x)
			swap(point.x, point._x);
		if (point.y > point._y)
			swap(point.y, point._y);
		cout << "(" << point.x << "," << point._y << ") (" << point._x << "," << point._y << ") (" << point._x << "," << point.y << ") (" << point.x << "," << point.y << ")" << endl;
		cout << per << " " << are << endl;
	}
}rectangle;

class Node {
public:
	Rectangle _data;
	Node* _pnext;
	Node() {}
	Node(Rectangle rectangle) { this->_data; }
	~Node() {}
};

class ListRect
{
	friend class Rectangle;
public:
	Node* _phead;
	int _size;
	ListRect()
	{
		_phead = new Node;//链表头
		_phead->_pnext = NULL;//连接
		_size = 0;
	}

	~ListRect()
	{
		Node* pcur = NULL;
		for (int i = 0; i <= _size; i++)
		{
			pcur = _phead;
			_phead = _phead->_pnext;
			delete pcur;
			pcur = NULL;
		}
	}

	Node* pop(int aim)//返回第i个矩形并删除
	{
		Node* temp = _phead;
		Node* pcur = NULL;
		if (aim == 1)//第一个
		{
			_phead = _phead->_pnext;
			_size--;
			pcur = _phead;
			return pcur;
		}
		for (int i = 1; i < aim; i++)
		{
			temp = temp->_pnext;
		}
		pcur = temp->_pnext;
		temp->_pnext = temp->_pnext->_pnext;
		_size--;
		return pcur;
	}

	void append(Rectangle data)//插入
	{
		Node* temp = _phead;
		Node* pcur = new Node;//插入的结点
		pcur->_data = data;
		pcur->_pnext = NULL;
		int pos = 0;
		int i = 0;
		for (i = 0; i < _size; i++)//遍历找到插入的位置
		{
			temp = temp->_pnext;
			if ((data.per - temp->_data.per) < 0)
			{
				break;
			}
			else if ((data.per - temp->_data.per) == 0)
			{
				if ((data.are - temp->_data.are) <= 0)
				{
					break;
				}
			}
		}
		pos = i;//插在i后
		if (pos == 0)
		{
			pcur->_pnext = temp;
			_phead = pcur;
			_size++;
			return;
		}
		i = 0;
		while (temp != NULL && i < pos)
		{
			temp = temp->_pnext;
			i++;
		}
		pcur->_pnext = temp->_pnext;
		temp->_pnext = pcur;
		_size++;
	}

	int Output()
	{
		if (_size < 3)
		{
			cout << "size<3,can't output" << endl;
			return 0;
		}
		Node* pcur = _phead;
		for (int i = 0; i <= _size - 3; i++)//输出最大
		{
			pcur = pcur->_pnext;
		}
		for (int i = 0; i < 3; i++)
		{
			Rectangle data = pcur->_data;
			data.outputRectangular();
			pcur = pcur->_pnext;
		}
		return 1;
	}
}listrec;

int main() {
	return 0;
}