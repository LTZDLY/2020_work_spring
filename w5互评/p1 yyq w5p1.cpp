#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int n, i, sum, temp;
	vector<int>nums;
	while (cin.peek() != '\n')
	{
		cin >> temp;
		nums.push_back(temp);
	}
	n= nums.size();//输入数字并获得n的大小

	sum = (n * (n + 1)) / 2;
	for (i = 0; i < n; i++)
	{
		sum -= nums[i];
	}//找到缺少的整数

	cout << sum;

	system("pause");
	return 0;

}