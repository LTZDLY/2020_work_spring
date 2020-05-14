#include "Matrix.h"

int main()
{
	Matrix a(2, 3, { 1,2,3,4,5,6 });
	Matrix b(2, 3, { 1,2,3,4,5,6 });
	a.Print();
	a.Transpose();
	a.Print();
	Matrix c = a * b;
	//copy constructor on b and move constructor on c
	c.Print();
	a.Transpose().Print();
	Matrix d = a + b;
	d.Print();
	Matrix e = d.Transpose()*b;
	std::cout << (d == e) << '\n';
	system("pause");
	return 0;
}