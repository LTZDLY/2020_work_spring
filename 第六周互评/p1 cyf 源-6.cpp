#include <iostream>
#include <string>

using namespace std;

void lock(string &str, int n) {
	for (auto &c : str) {
		if (c >= 'a'&&c <= 'z') {
			c = (c - 'a' + n) % 26 + 'a';
		}
		else if (c >= 'A'&&c <= 'Z') {
			c = (c - 'A' + n) % 26 + 'A';
		}
	}
}

int main() {
	int n;
	string input;
	cin >> n ;
	cin.get();
	getline(cin, input);
	
	lock(input, n);

	cout << input;
	return 0;
}