#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void input(vector<double>& vec)
{
	double num = 0;
	do
	{
		cin >> num;
		vec.push_back(num);
	} while (getchar() != '\n');
}

double add(const vector<double>& vec)
{
	double sum = 0;
	for (double i = 0; i < vec.size(); i += 2) {
		//every two numbers are bind as one group
		//add up all the smaller ones of the two numbers
		sum += vec[i];
	}
	return sum;
}

int main()
{
	vector<double> iVec;
	input(iVec);
	sort(iVec.begin(), iVec.end());//small to big
	cout << add(iVec);
	return 0;
}