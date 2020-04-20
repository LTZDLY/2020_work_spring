////复制代码到IDE中，格式会恢复正常

#include<iostream>
#include<string>

using namespace std;

//字母转换
void turn(char *password, int len, int changeWay)
{
	for (int i = 0; i < len; i++)
	{
		if ('A' <= password[i] && password[i] <= 'Z')
			password[i] = 64 + (password[i] - 64 + changeWay) % 26;
		else if ('a' <= password[i] && password[i] <= 'z')
			password[i] = 96 + (password[i] - 96 + changeWay) % 26;
	}
}

int main()
{
	int changeWay;
	string temp;
	cin >> changeWay;
	if (changeWay < 0 || changeWay>25) //判断输入的n是否合法
	{
		cout << "输入数据不合法，请退出后重新输入" << endl;
		return 0;
	}
	cin >> temp; //输入需要转换的电报字符
	const int len = temp.size();
	char* password = new char[len];
	temp.copy(password, len, 0);
	turn(password, len, changeWay);
	for (int i = 0; i < len; i++) //输出转换后的字符串
	{
		cout << password[i];
	}
	cout << endl;
	delete[]password;
	return 0;
}