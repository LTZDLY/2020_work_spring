
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Student;
istream &operator>>(istream &is, Student &rhs);
ostream &operator<<(ostream &os, const Student &rhs);

//Student声明和定义 
class Student {
public:
	friend istream &operator>>(istream &is, Student &rhs);
	friend ostream &operator<<(ostream &os, const Student &rhs);

	//构造函数 
	Student() {};
	Student(string name, string number, int math, int english, int physics) :name_(name), number_(number) {
		math_ = math;
		english_ = english;
		physics_ = physics;
	}

	int scores(string)const;
	int sum_scores()const { return math_ + english_ + physics_; };
	const string &number()const { return number_; }

private:
	string name_;
	string number_;
	int math_;
	int english_;
	int physics_;
};
inline int Student::scores(string subject)const {
	if (subject == "math" || subject == "Math" || subject == "MATH") {
		return math_;
	}
	else if (subject == "physics" || subject == "Physics" || subject == "PHYSICS") {
		return physics_;
	}
	else if (subject == "english" || subject == "English" || subject == "ENGLISH") {
		return english_;
	}
	else {
		cout << "invalid subject——" << subject << endl;
		return 0;
	}
}

//提供function object给sort函数 的类 
class MoreThan {
public:
	bool operator()(const Student& s1, const Student&s2) {
		return s1.sum_scores() > s2.sum_scores() ? true : false;
	}
};

//对operator>>和operator<<的重载 
istream &operator>>(istream &is, Student &rhs) {
	is >> rhs.name_ >> rhs.number_
		>> rhs.math_ >> rhs.english_ >> rhs.physics_;
	return is;
}
ostream &operator<<(ostream &os, const Student &rhs) {
	os << rhs.name_ << " " << rhs.number_
		<< " " << rhs.math_ << " " << rhs.english_ << " " << rhs.physics_ << endl;
	return os;
}

vector<Student>::const_iterator find_student(const vector<Student> &students, const string &search_number);
bool sort_students(vector<Student> &students);
void display_students(const vector<Student> &students, ostream &os = cout);
int main() {
	vector<Student> students(3);
	Student s;
	for (int i = 0; i < 3; i++) {
		cin >> s;
		students[i] = s;
	}

	string to_search;
	cin >> to_search;
	vector<Student>::const_iterator it = find_student(students, to_search);
	if (it != students.end()) {
		cout << *it;
	}
	else {
		cout << "Can not find the student in students." << endl;
	}

	if (sort_students(students)) {
		display_students(students);
	}

	return 0;
}

//根据学号查找vector中的学生 
vector<Student>::const_iterator find_student(const vector<Student> &students, const string &search_number) {
	vector<Student>::const_iterator first = students.begin();
	while (first != students.end()) {
		if (first->number() == search_number) {
			break;
		}
		first++;
	}

	return first;
}

//按照总成绩从高到低排序 
bool sort_students(vector<Student> &students) {
	if (!students.size()) {
		cout << "students is empty!" << endl;
		return false;
	}
	sort(students.begin(), students.end(), MoreThan());
	return true;
}

//将vector中的元素输出 
void display_students(const vector<Student> &students, ostream &os) {
	for (int i = 0; i < students.size(); i++) {
		os << students[i];
	}
	return;
}
