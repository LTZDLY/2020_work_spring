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
	n= nums.size();//�������ֲ����n�Ĵ�С

	sum = (n * (n + 1)) / 2;
	for (i = 0; i < n; i++)
	{
		sum -= nums[i];
	}//�ҵ�ȱ�ٵ�����

	cout << sum;

	system("pause");
	return 0;

}