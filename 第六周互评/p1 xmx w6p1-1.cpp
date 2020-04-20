/*
input:
2
AZby()&q

expected output:
CBda()&s
*/

#include <iostream>
#include <string>
#include <iterator>
using namespace std;

const int num_of_alpha = 26;

bool transfer_str(int n, string& str);
inline bool is_last_n_alpha(int n, char alpha);

int main()
{
	int n;
	string str;
	cin >> n >> str;
	if (!transfer_str(n, str))
		return 0;
	cout << str;
	return 0;
}

bool transfer_str(int n, string& str)
{
	if (n < 0) {
		cerr << "Opps!transfer_str():invalid data n : "
			<< n;
		return false;
	}

	for (string::iterator iter = str.begin(); iter != str.end(); iter++)
		if (isalpha(*iter)) {
			if (is_last_n_alpha(n, *iter))
				*iter -= num_of_alpha;
			*iter += n;
		}
	return true;
}

bool is_last_n_alpha(int n, char alpha)
{
	if ((alpha <= 'z' && alpha > 'z' - n) || (alpha <= 'Z' && alpha > 'Z' - n))
		return true;
	return false;
}