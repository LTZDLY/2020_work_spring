#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


class Student {
	friend Student findStudent(const vector<Student>&, string);
	friend istream &read(Student, istream &);
	friend ostream &print(const Student, ostream &);

public:
	Student() = default;
	Student(string stuName, string stuNo, vector<int> stuGrade) :
		name(stuName), no(stuNo), grade(stuGrade) {};
	Student(string stuName, string stuNo, int math, int English, int physics):	Student(){
		vector<int> tGrade = { math,English,physics };
		name = stuName;
		no = stuNo;
		grade = tGrade;
	}

	vector<int> getGrade()const { return grade; };
	int totalGrade()const;

private:
	string name;
	string no;
	vector<int> grade;
};

//求成绩和
inline int Student::totalGrade()const {
	int result = 0;
	for (auto i : grade) {
		result += i;
	}
	return result;
}


//输入
istream &read(Student stu, istream &is = cin) {
	vector<int> tGrades;
	int tGrade;
	is >> stu.name >> stu.no;
	while (cin >> tGrade) {
		tGrades.push_back(tGrade);
	}
	stu.grade = tGrades;
	return is;
}

//输出
ostream &print(const Student stu, ostream &os = cout) {
	os << stu.name << '\t' << stu.no << '\t';
	for (auto i : stu.grade) {
		os << i<<'\t';
	}
	return os;
}

//find函数
Student findStudent(const vector<Student> &stu, string stuNo) {
	for (auto i : stu) {
		if (i.no == stuNo) {
			return i;
		}
	}
	return Student();
}

//排序
bool studentCmp(Student a, Student b) {
	return a.totalGrade() > b.totalGrade();
}
void sortStudent(vector<Student> &stu) {
	sort(stu.begin(), stu.end(), studentCmp);
}

int main(void) {
	vector<Student> students;
	students.push_back(Student("Mike", "2345678", 80, 90, 80));
	students.push_back(Student("Jessica", "1234567", 60, 100, 60));
	students.push_back(Student("Sam", "3456789", 90, 60, 70));

	print(findStudent(students, "2345678")) << endl << endl;

	
	sortStudent(students);
	for (auto i : students) {
		print(i) << endl;
	}
	return 0;
}
