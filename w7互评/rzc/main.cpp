#include "RectangleList.h"

int main()
{
	//Point类
	std::cout << "Point:\n\n";
	Point point_1(1, 2), point_2(2, 1), point_3(3, 6), point_4(1, 2);
	point_1.PrintDistance(point_2);
	std::cout << "------------------------------------------------------------------------------\n";

	//Rectangle类
	std::cout << "\nRectangle:\n\n";
	Rectangle rec_1(point_1, point_2);
	rec_1.Print();
	Rectangle rec_2(-1, 3, 3, 0);
	rec_2.Print();
	Rectangle rec_4;
	rec_4.Print();
	Rectangle rec_5(3, 6, 1, 2);
	rec_5.Print();
	Rectangle rec_6(point_3,point_4);
	rec_6.Print();
	std::cout << "------------------------------------------------------------------------------\n";

	//RectangleList类
	std::cout << "\nRectangleList:\n\n";
	Rectangle rec_3(1, 6, 5, 2);
	HandMade::RectangleList rec_list(rec_2);
	rec_list.Print();
	std::cout << "------------------------------------------------------------------------------\n";
	rec_list.Append(rec_3).Print();//尾插
	std::cout << "------------------------------------------------------------------------------\n";
	rec_list.Append(rec_1).Print();//头插
	std::cout << "------------------------------------------------------------------------------\n";

	HandMade::RectangleList rec_list_2(rec_list);//拷贝构造函数
	std::cout << "In rec_list_2:\n";
	rec_list_2.Print();
	std::cout << "------------------------------------------------------------------------------\n";

	HandMade::RectangleList rec_list_3 = rec_list_2;//等号赋值
	std::cout << "In rec_list_3:\n";
	rec_list_3.Print();
	std::cout << "------------------------------------------------------------------------------\n";

	rec_list.Pop(3);//尾删
	rec_list.Print();
	std::cout << "------------------------------------------------------------------------------\n";
	rec_list.Pop(1);//头删
	rec_list.Print();
	std::cout << "------------------------------------------------------------------------------\n";
	rec_list.Pop(2);//错误输入
	std::cout << "------------------------------------------------------------------------------\n";

	std::cout << "In rec_list_3:\n";//通过拷贝构造函数以及赋值得到的对象与原对象独立
	rec_list_3.Print();
	std::cout << "------------------------------------------------------------------------------\n";

	//你可以在这里编写代码测试
	system("pause");
	return 0;
}