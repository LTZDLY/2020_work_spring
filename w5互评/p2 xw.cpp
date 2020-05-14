//���������n���������� array �� vector ���ۼ�������ֵ 
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int GetArr( int *arr,const int arr_size)
{
	int num = 0;
	for (int i = 0; i < arr_size; i++)
		cin >> *(arr + i);
	return 0;
}

void Calculate(const int* arr, const int arr_size,int &sum)
{
	for (int i = 0; i < arr_size; i++)
		sum += *(arr + i);
}

void Calculate(const vector<int>& arr,int & sum,double & average)
{
	sum = accumulate(arr.begin(), arr.end(), 0);
	average = ((double)sum) / ((double)arr.size());
}

int main()
{
	int arr_size = 0,sum = 0;
	double average = 0;
	cin >> arr_size;
	int *normal_arr = new int[arr_size];
	
	//��ͨarray���� �������
	GetArr(normal_arr,arr_size);
	Calculate(normal_arr, arr_size, sum);
	//vector������� ������� ��ƽ��ֵ
	vector<int> vector_arr(normal_arr, normal_arr + arr_size);
	Calculate(vector_arr,sum,average);
	
	cout << sum << ' ';
	cout << *noshowpoint << average;
	//�ͷſռ� ָ������
	delete[] normal_arr;
	normal_arr = NULL;
	return 0;
}
