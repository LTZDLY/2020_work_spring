//gbk!gbk!再说乱码自杀:(
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "./RECT.h"

using namespace std;//别骂了别骂了我偷懒喜欢这样写

//Point成员函数
Point::Point() { m_x = m_y = 0; }

Point::Point(int x, int y) {
    this->m_x = x;
    this->m_y = y;
}
//set
void Point::setX(int x) { m_x = x; }
void Point::setY(int y) { m_y = y; }
void Point::setXY(int x, int y) {
    m_x = x;
    m_y = y;
}
//get
int Point::getX() { return m_x; }
int Point::getY() { return m_y; }
//欧氏距离
double Point::getDistance(int x2, int y2) {
    int dx=m_x-x2;
    int dy=m_y-y2;
    double distance = sqrt((dx*dx) + (dy*dy));
    return distance;
}
//print
void Point::printPoint() { cout << '(' << m_x << ',' << m_y << ')' << ' '; }

void Point::printDistance(int x2, int y2) {
    printPoint();
    cout << '*';
    Point point2(x2,y2);
    point2.printPoint();
    cout << '=' << setiosflags(ios::fixed) << setprecision(2) << getDistance(x2,y2) << endl;
}
//Rectangle成员函数
Rectangle::Rectangle() {
    m_length = 0;
    m_width = 0;
}
Rectangle::Rectangle(Point& point1, Point& point2) {
    m_point1 = point1;
    m_point2 = point2;
    m_length = point2.getX() - point1.getX();
    m_width = point1.getY() - point2.getY();
}
long long Rectangle::perimeter() { return 2 * ((long long)m_length + m_width); }//周长
long long Rectangle::area() { return (long long)m_length * m_width; }//面积
void Rectangle::vertices() {//顶点
    cout << "vertices: ";
    Point point3(m_point2.getX(), m_point1.getY());
    Point point4(m_point1.getX(), m_point2.getY());
    m_point1.printPoint();//左上
    point3.printPoint();//右上
    m_point2.printPoint();//右下
    point4.printPoint();//左下
    cout << endl;
}
void Rectangle::diagonal() {//对角线
    cout << "diagonal: ";
    m_point1.printDistance(m_point2.getX(), m_point2.getY());
}
void Rectangle::printRectangle() {
    vertices();
    cout << "perimeter: " << perimeter() << endl;
    cout << "area: " << area() << endl;
}

//Node构造函数
Node::Node() {
    m_next = nullptr;
    m_pre = nullptr;
}
//node运算符重载
bool Node::operator<=(const Node& b) const {
    Rectangle rectangle1 = this->m_rectangle;
    Rectangle rectangle2 = b.m_rectangle;
    if (rectangle1.area() < rectangle2.area())
        return true;
    else if (rectangle1.area() == rectangle2.area() && rectangle1.perimeter() <= rectangle2.perimeter())
        return true;
    else
        return false;
}

//List成员函数
List::List() {
    m_head = nullptr;
    m_tail = nullptr;
}

List::~List() {
    for (Node* tmp = m_head;tmp != nullptr;tmp=m_head)
    {
        m_head = m_head->m_next;
        delete tmp;
    }
}

void List::addNode(Node* i, Node* node) {//头插：插在i前
    node->m_next = i;
    node->m_pre = i->m_pre;
    if (i == m_head)
    {
        i->m_pre = node;
        m_head = node;
        return;
    }    
    Node* tmp = i->m_pre;
    tmp->m_next = node;
    i->m_pre = node;
    tmp = nullptr;
}

void List::deleteNode(Node* i) {
    if (i == nullptr) return;
    if (i == m_head) {
        if (m_head->m_next != nullptr) {
            m_head = m_head->m_next;
            m_head->m_pre = nullptr;
        }
        else {
            m_head = m_tail = nullptr;
            throw i; //此时已pop链表中唯一的节点，删去该矩形链表将为空
        }    
    }
    else if (i == m_tail) {
        m_tail = m_tail->m_pre;
        m_tail->m_next = nullptr;
    }     
    else {
        Node* tmp1 = i->m_pre;
        Node* tmp2 = i->m_next;
        tmp1->m_next = i->m_next;
        tmp2->m_pre = i->m_pre;
        tmp1 = tmp2 = nullptr;
    }
    delete i;
    i = nullptr;
}

void List::append(Rectangle& rectangle) {
    Node* node = new Node;
    node->m_rectangle = rectangle;
    node->m_pre = node->m_next = nullptr;
    if (m_head == nullptr) m_head= m_tail = node;
    else {   
        for(Node* i = m_head;i != nullptr;i = i->m_next) {
            if (*node<=*i) {
                addNode(i, node); //插在i前
                return;
            }  
        } 
        m_tail->m_next = node;
        node->m_pre = m_tail;
        m_tail = node;
    }
}
void List::creatNode() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    Point point1, point2;
    point1.setXY(x1, y1);
    point2.setXY(x2, y2);
    Rectangle rectangle(point1, point2);
    append(rectangle);
}

Rectangle List::pop(int i) {
    Node* find = m_head;
    if (m_head == nullptr) throw "NOT FOUND";//无第i个矩形
    for (int j = 1; j < i; j++) {
        find = find->m_next;
        if (find == nullptr)
            throw "NOT FOUND";//无第i个矩形
    }
    Rectangle rect = find->m_rectangle;
    deleteNode(find);
    return rect;
}

void List::print() {
    if (m_head == nullptr) throw "EMPTY LIST";//链表为空
    else {
        Node* tmp = m_tail;
        for (int i = 1; i < 4; i++) {
            cout << i << endl;
            Rectangle rect = tmp->m_rectangle;
            rect.printRectangle();
            tmp = tmp->m_pre;
            if (tmp == nullptr && i < 3) throw "NOT ENOUGH RECTANGLE";//链表矩形<3个
        }
    }
}

void createList(List &rectList) {//创建链表
    int num;
    cout << "Please enter the number of rectangles." << endl;
    cin >> num;
    cout << "Please enter the coordinates of the upper-left and " << '\n'
        << "bottom-right vertices of each rectangle in order." << endl;
    cout << "Example input: 2 4 5 1 " << '\n' << "It means for a rectangle the coordinate of the upper-left vertice is (2,4)"
        << '\n' << "and the bottom-right vertice's is (5,1)" << endl;
    for (int i = 0; i < num; i++)
        rectList.creatNode();
}

int main() {
    List rectList;
    createList(rectList);
    cout << "Please enter the serial number of the operation you want to perform.\n"
        << "1:Enter a number 'i',search the No.i rectangle ranked according to area and display its information.\n"
        << "2:Display the top 3 rectangle ranked according to area.\n" << "other:End." << endl;
    int flag;
    while (cin >> flag) {
		switch (flag) {
		case 1:
			int i;
			cout << "Please input the number 'i'." << endl;
			cin >> i;
			try {
				if (i <= 0) //输入检查
					throw "WRONG DATA";
				Rectangle found = rectList.pop(i);
				found.printRectangle();
				found.diagonal();
				cout << endl;
			}
			catch (const char* msg) {
				cerr << msg << endl;
			}
			catch (Node*i) {//输出链表唯一的矩形并删去该节点，提示链表已空
				Rectangle found = i->m_rectangle;
				found.printRectangle();
				cout << "diagonal: ";
				found.diagonal();
				cout << endl;
				delete i;
				cerr << "ATTENTION!" << endl;
				cerr << "All rectangles have been deleted.Please press 3 to end it." << endl;
			}
			break;
		case 2:
			try {
				rectList.print();
			}
			catch (const char* msg) {//提示矩形小于三个或链表已空
				cerr << msg << endl;
			}
			break;
		default:
			return 0;
		}
        cout << '\n' <<"Please enter the serial number of the next operation." << endl;
    }
    return 0;
}