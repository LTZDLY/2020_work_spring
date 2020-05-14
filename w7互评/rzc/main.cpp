#include "RectangleList.h"

int main()
{
	//Point��
	std::cout << "Point:\n\n";
	Point point_1(1, 2), point_2(2, 1), point_3(3, 6), point_4(1, 2);
	point_1.PrintDistance(point_2);
	std::cout << "------------------------------------------------------------------------------\n";

	//Rectangle��
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

	//RectangleList��
	std::cout << "\nRectangleList:\n\n";
	Rectangle rec_3(1, 6, 5, 2);
	HandMade::RectangleList rec_list(rec_2);
	rec_list.Print();
	std::cout << "------------------------------------------------------------------------------\n";
	rec_list.Append(rec_3).Print();//β��
	std::cout << "------------------------------------------------------------------------------\n";
	rec_list.Append(rec_1).Print();//ͷ��
	std::cout << "------------------------------------------------------------------------------\n";

	HandMade::RectangleList rec_list_2(rec_list);//�������캯��
	std::cout << "In rec_list_2:\n";
	rec_list_2.Print();
	std::cout << "------------------------------------------------------------------------------\n";

	HandMade::RectangleList rec_list_3 = rec_list_2;//�ȺŸ�ֵ
	std::cout << "In rec_list_3:\n";
	rec_list_3.Print();
	std::cout << "------------------------------------------------------------------------------\n";

	rec_list.Pop(3);//βɾ
	rec_list.Print();
	std::cout << "------------------------------------------------------------------------------\n";
	rec_list.Pop(1);//ͷɾ
	rec_list.Print();
	std::cout << "------------------------------------------------------------------------------\n";
	rec_list.Pop(2);//��������
	std::cout << "------------------------------------------------------------------------------\n";

	std::cout << "In rec_list_3:\n";//ͨ���������캯���Լ���ֵ�õ��Ķ�����ԭ�������
	rec_list_3.Print();
	std::cout << "------------------------------------------------------------------------------\n";

	//������������д�������
	system("pause");
	return 0;
}