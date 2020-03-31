#include <iostream>
#include <stdio.h>
using namespace std;

struct Date
{
	int year;
	int month;
	int day;
};

void setDate(int y, int m, int d, Date*date)
{
	date->year = y;
	date->month = m;
	date->day = d;
}

int compare(Date begin, Date finish)
{
	if (begin.year < finish.year)
		return 1;
	if (begin.year <= finish.year && begin.month < begin.month)
		return 1;
	if (begin.year <= finish.year && begin.month <= finish.month && begin.day < finish.day)
		return 1;

	return 0;
}

int leapYear(int y)
{
	return ((y % 100 != 0) && (y % 4 == 0)) || (y % 400 == 0);
}
int monthDate(int m,int y)
{
	if (m == 2)
	{
		if (leapYear(y))
			return 29;
		else
			return 28;
	}
	else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		return 31;
	else
		return 30;
}

int calculate(Date begin,Date finish)
{
	int num = 0;
	Date temp;
	if(compare(begin,finish)==0)
	{
		temp = begin;
		begin = finish;
		finish = temp;
	}

	while (compare(begin, finish))
	{
		begin.day++;
		if (begin.day > monthDate(begin.month, begin.year))
		{
			begin.day = 1;
			begin.month++;
			if (begin.month > 12)
			{
				begin.month = 1;
				begin.year++;
			}
		}
		num++;
	}
	return num;

}


int main()
{
	Date begin, finish;
	int y, m, d;
	int num;
	scanf_s("%d-%d-%d", &y, &m, &d);
	setDate(y, m, d, &begin);
	scanf_s("%d-%d-%d", &y, &m, &d);
	setDate(y, m, d, &finish);
	num = calculate(begin, finish);
	cout << num;
	
	return 0;

}

