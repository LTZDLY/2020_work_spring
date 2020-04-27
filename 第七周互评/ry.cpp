#include<iostream>
#include<math.h>
#include <iomanip>
#include<vector>
using namespace std;

class Point
{
private:
	double x = 0;
	double y = 0;

public:
	Point origin_point()  //原点
	{
		return *this;
	}

	void newPoint(double x, double y)  //创建一个点
	{
		this->x = x;
		this->y = y;
	}
	
	void setPoint(Point *point)  //设置函数
	{
		*this = *point;
	}

	double getX()  //获取横坐标
	{
		return x;
	}

	double getY()  //获取纵坐标
	{
		return y;
	}

	double distance(Point *point)  //计算距离
	{
		double distance;
		distance = sqrt(pow((this->x - point->x), 2) + pow((this->y - point->y), 2));
		return distance;
	}

	void printDis(Point *point)  //输出距离
	{
		this->printPoint();
		cout <<"*";
		point->printPoint();
		cout << "=" << fixed << setprecision(2) << distance(point) << endl;
	}

	void printPoint()  //输出点的坐标
	{
		cout << "(" << this->x << "," << this->y << ")";
	}
};

class Rectangle  //边平行于坐标轴的矩形
{
public:
	Point left_up;
	Point right_down;
	Point right_up;
	Point left_down;

	double perimeter()  //计算周长，总觉得要把point里的函数用起来，不然浪费了
	{
		right_up.newPoint(right_down.getX(), left_up.getY());
		return (right_up.distance(&left_up) * 2 + right_up.distance(&right_down)) * 2;
	}

	double area()  //计算面积，总觉得要把point里的函数用起来，不然浪费了
	{
		right_up.newPoint(right_down.getX(), left_up.getY());
		return right_up.distance(&left_up) * right_up.distance(&right_down);
	}

	void printDate()  //输出矩形相关数据，总觉得要把point里的函数用起来，不然浪费了
	{
		right_up.newPoint(right_down.getX(), left_up.getY());
		left_down.newPoint(left_up.getX(), right_down.getY());

		cout << "vertices : ";
		left_up.printPoint();
		right_up.printPoint();
		right_down.printPoint();
		left_down.printPoint();

		cout << "\nperimeter : " << perimeter() << endl;
		cout << "area : " << area() << endl;
	}
};

class Node  
{
public:
	Rectangle date;
	Node* next;
};

class List
{
private:
	Node* head;
	Node* tail;
	int size = 0;
	
public:
	List();//构造函数
	~List();//析构函数
	void append(Rectangle example);//添加数据
	Rectangle pop(int i);//删除数据
	void print();//输出数据
};

List::List()//构造函数
{
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail = NULL;
}

List::~List()//析构函数
{
	while (head->next != NULL)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	delete head;
	head = NULL;
}

void List:: append(Rectangle example)//面积升序，面积相等则周长升序
{
	Node* temp = new Node;
	temp->date = example;//新指针存输入的矩形

	Node* p = head;
	Node* q = new Node;
	while (p->next != NULL)
	{
		q = p;
		p = p->next;
		if (p->date.area() == 0 || p->date.area() > example.area())//最后一个节点前插入 || 当前节点的面积大于输入矩形的面积
		{
			temp->next = p;
			q->next = temp;
			size++;
			return;
		}
		else if (p->date.area() == example.area() && p->date.perimeter() > example.perimeter())//当前节点的面积等于输入矩形的面积
		{
			temp->next = p;
			q->next = temp;
			size++;
			return;
		}
		else continue;
	}
}

Rectangle List::pop(int i)//删除节点
{
	Node* p = head;
	Node* q = new Node;

	int num = 0;
	while (p->next != NULL && num < i)
	{
		q = p;
		p = p->next;
		num++;
	}

	Rectangle temp = p->date;
	q->next = p->next;
	size--;
	delete p;

	return temp;
}

void List::print()//输出数据
{
	Node* p = head;
	if (size >= 3)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << "\n" << i + 1 << endl;
			p = p->next;
			p->date.printDate();
		}
	}
	else if (size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			cout << "\n" << i + 1 << endl;
			p = p->next;
			p->date.printDate();
		}
	}
	else
		cout << "\n无矩形";
	return;
}

void input_date(vector<Rectangle>& rectangles, int number)
{
	double leftX = 0, leftY = 0, rightX = 0, rightY = 0, count = 0;
	while(count < number)
	{
		cout << "\n请输入矩形" << count + 1 << "的左上顶点:";
		cin >> leftX >> leftY;
		cout << "请输入矩形" << count + 1 << "的右下顶点:";
		cin >> rightX >> rightY;

		if (leftX < rightX && leftY > rightY)
		{
			rectangles[count].left_up.newPoint(leftX, leftY);
			rectangles[count].right_down.newPoint(rightX, rightY);
			count++;
		}
		else
			cout << "这两点不存在边平行于坐标轴的矩形\n";
	}
}

int main()
{
	int number = 0;
	cout << "请输入矩形的个数: ";
	cin >> number;

	vector<Rectangle> rectangles(number);
	input_date(rectangles, number);

	List A;
	for (int i = 0; i < number; i++)
		A.append(rectangles[i]);

	int goal = 0;
	Rectangle deleted;
	while (1) 
	{
		cout << "\n请输入当前矩形中你想删除的矩形序号（可输入0选择不删除)：";
		cin >> goal;
		if (goal == 0)
			break;
		deleted = A.pop(goal);
		cout << "被删除的矩形相关信息如下：\n";
		deleted.printDate();
	}
	
	cout << "\n余下矩形相关信息如下（前三甲）：\n";
	A.print();
	return 0;
}
