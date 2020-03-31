#include <iostream>
using namespace std;
int normal_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
int special_month[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
struct date
{
	int year;
	int month;
	int day;
};
struct date date1;
struct date date2;

int compare()
//比较两个日期的大小，如果第一个日期早于第二个日期，返回1，反之返回-1；
{
	if (date1.year > date2.year)
		return -1;
	else if (date1.year < date2.year)
		return 1;
	else
	{
		if (date1.month < date2.month)
			return 1;
		else if (date1.month > date2.month)
			return -1;
		else
		{
			if (date1.day < date2.day)
				return 1;
			else if (date1.day > date2.day)
				return -1;
			else
			{
				cout << '0';
				system("pause");
				exit(0);//如果日期相同直接退出程序
			}
		}
	}
}
int is_special(int year)//判断该年是否为闰年,返回1为闰年，反之返回-1
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;
	else
		return -1;
}
int day_num(struct date date1, struct date date2)
{
	int final_day = 0;//记录最终相距的天数
	for (;;)
	{
		date1.day++;
		final_day++;
		if (date1.day > (is_special(date1.year) == 1 ? special_month[date1.month - 1] : normal_month[date1.month - 1]))
		{
			date1.month++;
			date1.day = 1;
		}
		if (date1.month > 12)
		{
			date1.year++;
			date1.month = 1;
			date1.day = 1;
		}
		if (date1.year == date2.year&&date1.month == date2.month&&date1.day == date2.day)
			break;
	}

	return final_day;
}
int main()
{
	char link1,link2,link3,link4;
	int final_num = 0;
	cin >> date1.year>>link1>>date1.month>>link2>>date1.day;
	cin >> date2.year >> link3 >> date2.month >> link4 >> date2.day;
	if (compare() == 1)
		final_num = day_num(date1, date2);
	else if (compare() == -1)
		final_num = day_num(date2, date1);
	cout << final_num;
	system("pause");
	return 0;

}