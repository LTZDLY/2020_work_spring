#include<iostream>
#include<string>
using namespace std;
struct datenum 
{
	int year;
	int month;
	int day;
};
int ifLeapYear(int year)//判断是否是闰年
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return 1;
	else
		return 0;
}
int dayOfYear(int year,int month,int day) //判断这是一年的第几天
{
	int months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int dayofyear=0;
	if (ifLeapYear(year) == 1)
	{
		months[1] = 29;
	}
	for (int i = 0; i < month-1; i++) 
	{
		dayofyear = dayofyear + months[i];
	}
	dayofyear = dayofyear + day;
	return dayofyear;
}
int main()
{
	string str1;
	string str2;
	int day;
	cin >> str1;
	cin >> str2;//输入年份
	datenum date1, date2;
	date1.year = (str1[0] - 48) * 1000 + (str1[1] - 48) * 100 + (str1[2] - 48) * 10 + (str1[3] - 48);//将字符串转换
	date1.month = (str1[5] - 48) * 10 + (str1[6] - 48);
	date1.day = (str1[8] - 48) * 10 + (str1[9] - 48);
	date2.year = (str2[0] - 48) * 1000 + (str2[1] - 48) * 100 + (str2[2] - 48) * 10 + (str2[3] - 48);
	date2.month = (str2[5] - 48) * 10 + (str2[6] - 48);
	date2.day = (str2[8] - 48) * 10 + (str2[9] - 48);
	int d1 = dayOfYear(date1.year, date1.month, date1.day);
	int d2 = dayOfYear(date2.year, date2.month, date2.day);
	int d3 = 0;
	if (date1.year == date2.year)//如果两个日期是同一年
	{
		day = d1 - d2;
	}
	else
	{
		for (int i = date2.year + 1; i < date1.year; i++)
		{
			if (ifLeapYear(i))
				d3 = d3 + 366;
			else
				d3 = d3 + 365;
		}
		if (ifLeapYear(date2.year))
			d2 = 366 - d2;
		else
			d2 = 365 - d2;
		day = d1 + d2 + d3;
	}
	cout << day<<endl;
	system("pause");
}