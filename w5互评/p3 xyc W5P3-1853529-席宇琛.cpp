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

		if (temp > 2147483647 || temp < -2147483647) //输入检查，超过int范围的报错
			return -1;

		Numbers.push_back(temp);

	} while (cin.get() != '\n');

	for (i = Numbers.size() - 1; i > 0; i--) //冒泡排序vector
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

	for (i = 0; i < Numbers.size() / 2; i++) //从小到大排序后，取vector里偶数位加起来就好了
		sum += Numbers[i * 2];
	
	cout << sum;

	return 0;
}