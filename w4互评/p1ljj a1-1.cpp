#include<iostream>
#include<cstdlib>
#include<sstream>
using namespace std;

//好人是0，坏人是1
void find_bad(int ar[],int M,const int& K) {
	int size = 2 * M, i = 0;
	while (M--) {//标记M个坏人
		int _count = 0;
		while (_count != K) //循环查找，每K个人标记一个坏人
			if (!ar[i++ % size])
				++_count;

		int j = (i - 1) % size;
		ar[j] = 1;
	}
}

void output(const int ar[], int size) {
	for (int i = 0; i < size; ++i)
		if (ar[i])
			cout << '@';
		else
			cout << '+';
	cout << endl;
}

int string_to_int(const string& s) {
	int num;
	stringstream is(s);
	is >> num;
	return num;
}

bool input_check(const string& s,unsigned int &i) {
	for (i = 0; i < s.length(); ++i)
		if ('q' == s[i])
			return true;

	for (i = 0; i < s.length(); ++i)
		if ((s[i] < '0' || s[i]>'9') && '+' != s[i])
			break;

	if (s.length() != i) 
		cout << "bad input '" << s[i] << "'" << endl
			<< "enter new input" << endl;
	return false;
}

void help() {
	cout << "please enter two positive intgers to start." << endl
		<< "like this \t M K" << endl
		<< "0<M<1000 1<K<1000" << endl
		<< "enter new datas to continue or enter 'q' to quit" << endl;
}

void input() {
	help();

	bool end = false;
	while (true) {
		string m, k;
		cin >> m >> k;

		int i = 0;
		end = input_check(m, i);
		if (!end && i != m.length())
			continue;
		if (end)
			break;
		end = input_check(k, i);
		if (!end && i != k.length())
			continue;
		if (end)
			break;

		int M = 0, K = 0;
		M = string_to_int(m);
		K = string_to_int(k);
		if (M <= 0 || K <= 1|| M >= 1000 || K >= 1000) {
			cout << "0<M<1000\t1<K<1000" << endl
				<< "try again." << endl;
			continue;
		}

		int* p = new int[M * 2];
		if (!p) {
			cout << "fail to apply memory !" << endl;
			return;//error
		}

		memset(p, 0, sizeof(int) * 2 * M);
		find_bad(p, M, K);
		output(p, 2 * M);

		delete[] p;
	}

	cout << "goodbye!" << endl;
}

int main() {
	input();
	return 0;
}