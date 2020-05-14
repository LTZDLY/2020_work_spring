#include<iostream>
#include<vector>

using namespace std;

bool input(vector<char>&);
void Transform(int, vector<char>&);
void Output(const vector<char>);

int main(void)
{
	int n;
	vector<char> Cipher;
	cin >> n;
	if (input(Cipher))
	{
		Transform(n, Cipher);
		Output(Cipher);
		return 0;
	}
	else return 0;
}

bool input(vector<char>& vec)
{
	char InputChar;
	while (cin >> InputChar)
	{
		vec.push_back(InputChar);
		if (cin.peek() == '\n')
			break;

		//异常处理
		
	}
	if (cin.fail())
	{
		cerr << "Wrong Input!";
		return false;
	}
	return true;
}

void Transform(int n, vector<char>& vec)
{
	for (int i = 0;i < vec.size();i++)
	{
		if (vec[i] >= 'A' && vec[i] <= 'Z')
		{
			vec[i] = vec[i] + n;
			if (vec[i] > 'Z')
			{
				vec[i] = 'A' + vec[i] % 'Z' - 1;//-1是因为从A开始
			}
		}
		else if (vec[i] >= 'a' && vec[i] <= 'z')
		{
			vec[i] = vec[i] + n;
			if (vec[i] > 'z')
			{
				vec[i] = 'a' + vec[i] % 'z' - 1;
			}
		}
		else continue;//非英文字母
	}
}

void Output(const vector<char> vec)
{
	for (int i = 0;i < vec.size();i++)
		cout << vec[i];
}