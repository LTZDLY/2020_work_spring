#include<iostream>
#include<vector>

using namespace std;

int main() 
{
	int temp = 0;
	long long sum = 0;
	int i, j;
	vector<int>Numbers;

	do
	{
		cin >> temp;

		if (temp > 2147483647 || temp < -2147483647) //�����飬����int��Χ�ı���
			return -1;

		Numbers.push_back(temp);

	} while (cin.get() != '\n');

	for (i = Numbers.size() - 1; i > 0; i--) //ð������vector
	{
		for (j = 0; j < i ; j++)
		{
			if (Numbers[j] > Numbers[j + 1])
			{
				temp = Numbers[j];
				Numbers[j] = Numbers[j + 1];
				Numbers[j + 1] = temp;
			}
		}
	}

	for (i = 0; i < Numbers.size() / 2; i++) //��С���������ȡvector��ż��λ�������ͺ���
		sum += Numbers[i * 2];
	
	cout << sum;

	return 0;
}