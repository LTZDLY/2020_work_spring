#include<iostream>
#include<vector>

using namespace std;

int Add(const int*begin, const int*last)
{
	int SumValue = 0; const int *pt = NULL;
	if ((!begin) || (!last))
	{
		return 0;
	}

	for (pt = begin; pt <= last; pt++)
	{
		SumValue += *pt;
	}

	return SumValue;
}

int main()
{
	int n;
	cin >> n;

	if (n <= 0)
	{
		cout << "请重新输入一个正整数";
	}
	else
	{
		int a = 0;
		vector <int> VecNum(n);
		int *ArrNum = new int[n];

		for (int i = 0; i < n; i++)
		{
			cin >> a;
			VecNum.push_back(a);
			ArrNum[i] = a;
		}

		int SumForVec = Add(&VecNum[0], &VecNum[VecNum.size() - 1]);
		int SumForArr = Add(ArrNum, ArrNum + n - 1);

		int Average = SumForVec / n;
		cout << SumForArr << ' ' << Average;
		delete[]ArrNum;
	}

	return 0;
}
