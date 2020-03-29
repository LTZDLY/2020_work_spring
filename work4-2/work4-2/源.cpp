#include<iostream>
#include<string>
#include<vector> 
#include<limits.h>
#include<sstream>
#define LEAP_YEAR 366
#define NON_LEAP_YEAR 365
#define LEAP_MONTH 29
#define EVEN_MONTH 28
#define BIG_MONTH 31
#define SMALL_MONTH 30

using namespace std;

int to_int(const string s) {
	stringstream ss;
	int num;
	ss << s;
	ss >> num;
	return num;
}
unsigned long long to_long (const string s) {
	stringstream ss;
	unsigned long long num;
	ss << s;
	ss >> num;
	return num;
}

void string_split(const string& s, vector<string>& v, const string& c) {
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2){
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}//分割文本函数

int leap_year_check(const unsigned long long year) {
	if (year % 100 == 0){
		if (year % 400 == 0) return 0;
		else return 1;
	}
	else if (year % 4 == 0) return 0;
	else return 1;
}
unsigned long long year_check(const unsigned long long year) {
	if (!leap_year_check(year))return LEAP_YEAR;
	else return NON_LEAP_YEAR;
}
int month_check(const unsigned long long year, const int month) {
	switch (month){
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return BIG_MONTH;
	case 4:
	case 6:
	case 9:
	case 11:
		return SMALL_MONTH;
	case 2:
		if (!leap_year_check(year))return LEAP_MONTH;
		else return EVEN_MONTH;
	default:
		return 0;
	}
}

int date_check(const unsigned long long year, const int month, const int day) {
	int day_max = 0;
	day_max = month_check(year, month);
	if (day_max < day) {
		cout << "日期格式错误，请重新输入！" << endl;
		return 1;
	}
	else return 0;
}

int date_check(string& s) {
	cin >> s;
	for (unsigned int i = 0; i < s.size(); i++) {
		if (s[i] != '-' && (s[i] < '0' || s[i] > '9')) {
			cout << "日期格式错误，请重新输入！" << endl;
			return 1;
		}
	}
	vector<string> text_spilt;
	string_split(s, text_spilt, "-");
	if (text_spilt.size() != 3 || (text_spilt[1].size() > 2 || text_spilt[2].size() > 2)) {
		cout << "日期格式错误，请重新输入！" << endl;
		return 1;
	}
	else {
		unsigned long long year = to_long(text_spilt[0]);
		int month = to_int(text_spilt[1]);
		int day = to_int(text_spilt[2]);
		if (year == 0 || month == 0 || day == 0) {
			cout << "日期格式错误，请重新输入！" << endl;
			return 1;
		}
		return date_check(year, month, day);
	}
	return 0;
}

unsigned long long to_date_stamp(const string date) {
	unsigned long long date_stamp = 0;
	vector<string> text_spilt;
	string_split(date, text_spilt, "-");
	unsigned long long year = to_long(text_spilt[0]);
	int month = to_int(text_spilt[1]);
	int day = to_int(text_spilt[2]);
	date_stamp += day;
	for (int i = 1; i < month; i++)date_stamp += month_check(year, i);
	for (unsigned long long i = 1; i < year; i++)date_stamp += year_check(i);
	return date_stamp;
}

int main() {
	vector<string> text_spilt;
	string input_before, input_after;
	cout << "请输入第一个日期(格式为YYYY-MM-DD)" << endl;
	while(date_check(input_before));
	cout << "请输入第二个日期(格式为YYYY-MM-DD)" << endl;
	while(date_check(input_after));
	unsigned long long date_stamp_before = to_date_stamp(input_before);
	unsigned long long date_stamp_after = to_date_stamp(input_after);
	unsigned long long date_interval = 0;
	if (date_stamp_before > date_stamp_after)date_interval = date_stamp_before - date_stamp_after;
	else date_interval = date_stamp_after - date_stamp_before;
	cout << date_interval << endl;
	return 0;
	}