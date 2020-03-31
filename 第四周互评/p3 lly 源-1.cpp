#include<iostream>
#include<string.h>
#include <typeinfo.h>
using namespace std;
template <typename T>
void  arr(T array[], int size) {
	int i, j;
	T temp;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size - 1; j++) {
			if (array[j] > array[j + 1]) {
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}
template <typename T>
void show(T array[], int size) {
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << endl;
	}
}
int main()
{
	int A[] = { 1,4,2 };
	arr(A, 3);
	show(A, 3);
	double B[] = { 1.6,2.2,4.1,2.4 };
	arr(B, 4);
	show(B, 4);
	char C[] = {'A','C','B'};
	arr(C, 3);
	show(C, 3);
	system("pause");
	return 0;
}