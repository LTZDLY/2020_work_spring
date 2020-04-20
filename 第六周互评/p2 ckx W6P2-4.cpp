#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Student {
public:
	//ctor&destructor
	Student() = default;
	Student(const string& n, const string& sN,
		float m, float e, float p);
	~Student() { };
	//overloaded operator>>

	//member:total&scores
	/*float grades() const{ return this->_grade; }*/
	float* scores() { return _grade; }
	float total() { return _total_grade; }

	friend istream& operator>>(istream& in, Student& stu);
	//there are two kinds of output form,only name&grades and full information of a student
	void print_name_grades()const; 
	void print_full_info()const;
	bool found_number(const string& s) const{ return (this->_sNo == s); }
	//overloaded compare operator:featuring ==,!=,>,>=,<,<=
	//to compare two Student's class judging to their total grade
	bool operator==(const Student& s)const;
	bool operator!=(const Student& s)const;
	bool operator>(const Student& s)const;
	bool operator<(const Student& s)const;
	bool operator>=(const Student& s)const;
	bool operator<=(const Student& s)const;

private:
	string _name;
	string _sNo;
	float _grade[3];//0 for math,1 for english,2 for physics
	float _total_grade;
	void _can_outPut()const {
		if (this->_name.empty() || this->_sNo.empty()) {
			cerr << "invalid result:empty Student." << endl;
			exit(0);
		}
	}
};

Student::Student(const string& n, const string& sN,
	float m, float e, float p) :
	_name(n), _sNo(sN) {
	_grade[0] = m;
	_grade[1] = e;
	_grade[2] = p;
	_total_grade = m + e + p;
}

istream& operator>>(istream& in, Student& stu) {
	in >> stu._name >> stu._sNo >> stu._grade[0] >> stu._grade[1] >> stu._grade[2];
	stu._total_grade = stu._grade[0] + stu._grade[1] + stu._grade[2];
	return in;
}

//output form for W6P3
inline void Student::print_name_grades()const {
	//check whether this Student has data to show
	this->_can_outPut();
	cout << _name << " " << _grade[0] << " " <<
		_grade[1] << " " << _grade[2] << endl;
}

//output form for W6P4
inline void Student::print_full_info()const {
	//check whether this Student has data to show
	this->_can_outPut();
	cout << _name << " " << _sNo << " "
		<< _grade[0] << " " << _grade[1] << " "
		<< _grade[2] << endl;
}

//overloaded compare operator
//used in W6P4
bool Student::operator<(const Student& s)const {
	return _total_grade < s._total_grade;
}
//other overloaded compare operator(not used in this program)
bool Student::operator==(const Student& s)const {
	return _total_grade == s._total_grade;
}
bool Student::operator!=(const Student& s)const {
	return !(*this == s);
}
bool Student::operator>(const Student& s)const {
	return _total_grade > s._total_grade;
}

bool Student::operator>=(const Student& s)const {
	return _total_grade >= s._total_grade;
}
bool Student::operator<=(const Student& s)const {
	return _total_grade <= s._total_grade;
}



//W6P3:function find
void find(const vector<Student>& svec, const string& s) {
	//check if it's an empty vector
	if (svec.size() == 0) {
		cerr << "ERROR:empty svec" << endl;
		exit(0);
	}
	auto iter1 = svec.begin();
	auto iter2 = svec.end();
	//debug error report: can't derefrence end(),so (!iter1->...)&&iter1!=iter2 is wrong.
	while (iter1 != iter2) {
		if (iter1->found_number(s))
			break;
		++iter1;
	}
	if (iter1 == iter2) {
		cout << "Student number not found." << endl;
	}
	else {
		//print founded student's info
		iter1->print_name_grades();
	}

}

//W6P4 function
//1.see line 17-18
//2.sort a Student vector and print the result
vector<Student>& sort_and_output(vector<Student>& svec) {
	//check if it's an empty vector
	if (svec.size() == 0) {
		cerr << "ERROR:empty svec" << endl;
		exit(0);
	}
	sort(svec.begin(), svec.end(),
		[](const Student& s1, const Student& s2) {return s1 > s2; });

	//print student info in order
	for (auto i : svec)
		i.print_full_info();
	return svec;
}

int main(int argc, char* argv[]) {
	//Week 6 Assignment 2
	Student stu;
	cin >> stu;

	//Week 6 Assignment 3
	Student s1("Jessica", "1234567", 60, 100, 60);
	Student s2("Mike", "2345678", 80, 90, 80);
	Student s3("Sam", "3456789", 90, 60, 70);
	vector<Student> svec = { s1,s2,s3 };
	//find Mike with his sNo
	find(svec, "2345678");
	//can't find studet with sNo "G19887"
	find(svec, "G19887");

	//Week 6 Assignment 4
	sort_and_output(svec);
}