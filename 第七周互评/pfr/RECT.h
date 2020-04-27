#pragma once
#ifndef RECT_H_INCLUDED
#define RECT_H_INCLUDED

class Point {
    private:
        int m_x;
        int m_y;
    public:
        Point();//默认为原点
        Point(int x, int y);//以x y为参数创建一个点
        ~Point()=default;
        //设置函数
        void setX(int x);
        void setY(int y);
        void setXY(int x, int y);
        //获取函数
        int getX();
        int getY();
        //欧氏距离
        double getDistance(int dx, int dy);//计算两点间欧氏距离
        void printPoint();//输出本点坐标
        void printDistance(int x2, int y2);//输出欧氏距离
};

class Rectangle {
    private:
        Point m_point1; //左上
        Point m_point2; //右下
        int m_length;
        int m_width;
    public:
        Rectangle();
        Rectangle(Point& point1, Point& point2);
        ~Rectangle()=default;
        long long perimeter();//计算周长
        long long area();//计算面积
        void vertices();//顺时针输出四个顶点
        void diagonal();//输出对角线长度（检测欧氏距离函数的功能）
        void printRectangle();//输出矩形的顶点、周长和面积
};

struct Node {
    Rectangle m_rectangle;
    Node* m_next;
    Node* m_pre;
    Node();
    bool operator<=(const Node& b) const;//用于两矩形面积和周长的比较
};

class List {
    private:
        Node* m_head;//指向最小矩形的节点
        Node* m_tail;//指向最大矩形的节点
    public:
        List();
        ~List();
        void addNode(Node* i, Node* node);//头插添加节点：node插在i前
        void deleteNode(Node* i);//删除本节点
        void append(Rectangle& rectangle);//append函数
        void creatNode();//创建一个节点并调用append插入
        Rectangle pop(int i);//查找第i个矩形
        void print();//输出链表面积最大的三个矩形的信息
};

#endif