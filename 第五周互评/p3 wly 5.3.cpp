#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool GetData(vector<int>& data) {
	int num;
	while (cin >> num) {
		data.push_back(num);
	}
	if (data.size() % 2) {
		cout << "Please provide the even number!" << endl;
		return false;
	}
	return true;
}
int GetMax(vector<int>& data) {
	
	sort(data.begin(), data.end());
	int max = 0;
	for (vector<int>::iterator it = data.begin(); it != data.end(); it+=2) {
		max += *it;
	}
	return max;
}
int main() {
	vector<int> my_data;
	if (GetData(my_data)) {
		cout << GetMax(my_data) << endl;
	}
	return 0;
}