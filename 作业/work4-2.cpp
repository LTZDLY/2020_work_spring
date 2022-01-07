#include<iostream>
#include<string>
#include<vector> 
#include<sstream>
#define YEAR_LEAP 366
#define YEAR_NON_LEAP 365
#define MONTH_LEAP 29
#define MONTH_EVEN 28
#define MONTH_BIG 31
#define MONTH_SMALL 30

using namespace std;
//不考虑任何日期上的特殊事件如被删去的10天，将所有的符合满百被400整除其余被4整除的年份认为是闰年

//将只含数字字符的字符串转换成短整型
int to_int(const string s) {
	stringstream ss;
	int num;
	ss << s;
	ss >> num;
	return num;
}
//将只含数字字符的字符串转换成长整型
unsigned long long to_long (const string s) {
	stringstream ss;
	unsigned long long num;
	ss << s;
	ss >> num;
	return num;
}
//分割文本函数
void string_split(const string& s/*被分割字符串*/, vector<string>& v/*保存被分割后的字符串*/, const string& c/*被分割的依据*/) {
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
}
//检查是否为闰年
int check_leap_year(const unsigned long long year) {
	if (year % 100 == 0){
		if (year % 400 == 0) return 0;
		else return 1;
	}
	else if (year % 4 == 0) return 0;
	else return 1;
}
//根据是否为闰年返回一年中的天数
unsigned long long year_check(const unsigned long long year) {
	if (!check_leap_year(year))return YEAR_LEAP;
	else return YEAR_NON_LEAP;
}
//根据年份和月份返回一个月中的日期
int check_month(const unsigned long long year, const int month) {
	switch (month){
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return MONTH_BIG;
	case 4:
	case 6:
	case 9:
	case 11:
		return MONTH_SMALL;
	case 2:
		if (!check_leap_year(year))return MONTH_LEAP;
		else return MONTH_EVEN;
	default:
		return 0;
	}
}
//检查日是否合理
int check_day(const unsigned long long year, const int month, const int day) {
	int day_max = 0;//表示该年月下的日的最大值
	day_max = check_month(year, month);
	if (day_max < day) {
		cout << "日期格式错误，请重新输入！" << endl;
		return 1;
	}
	else return 0;
}
//检查日期是否合理
int check_date(string& s) {
	cin >> s;//输入
	for (unsigned int i = 0; i < s.size(); i++) {
		if (s[i] != '-' && (s[i] < '0' || s[i] > '9')) {//若输入中除了'-'含有其他非数字字符则报错
			cout << "日期格式错误，请重新输入！" << endl;
			return 1;
		}
	}
	vector<string> text_spilt;
	string_split(s, text_spilt, "-");
	if (text_spilt.size() != 3 || (text_spilt[1].size() > 2 || text_spilt[2].size() > 2)) {//若格式不为"YYYY-MM-DD"则报错
		cout << "日期格式错误，请重新输入！" << endl;
		return 1;
	}
	else {
		unsigned long long year = to_long(text_spilt[0]);
		int month = to_int(text_spilt[1]);
		int day = to_int(text_spilt[2]);
		if (year == 0 || month == 0 || day == 0) {//若有一个值为0则报错
			cout << "日期格式错误，请重新输入！" << endl;
			return 1;
		}
		return check_day(year, month, day);//检查日是否合理
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
	for (int i = 1; i < month; i++)date_stamp += check_month(year, i);
	for (unsigned long long i = 1; i < year; i++)date_stamp += year_check(i);
	return date_stamp;
}

int main() {
	vector<string> text_spilt;
	string input_before, input_after;
	cout << "请输入第一个日期(格式为YYYY-MM-DD)" << endl;
	while(check_date(input_before));
	cout << "请输入第二个日期(格式为YYYY-MM-DD)" << endl;
	while(check_date(input_after));
	unsigned long long date_stamp_before = to_date_stamp(input_before);
	unsigned long long date_stamp_after = to_date_stamp(input_after);
	unsigned long long date_interval = 0;
	if (date_stamp_before > date_stamp_after)date_interval = date_stamp_before - date_stamp_after;
	else date_interval = date_stamp_after - date_stamp_before;
	cout << date_interval << endl;
	return 0;
	}