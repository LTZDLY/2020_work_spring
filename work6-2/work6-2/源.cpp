#include<iostream>
#include<string>
#include<sstream>
#include<vector>

using std::vector;
using std::string;

class Student {
public:
	Student();
	void info_set(const string& input_str);
	void info_print(std::ostream &os);
	void info_find(std::ostream &os);
	void score_print_each(std::ostream &os);
	void score_print_total(std::ostream &os);
	int grade_total;
	long student_ID;
	string student_name;
private:
	int	grade_math;
	int grade_english;
	int grade_physics;
};

Student::Student() {
	grade_total = grade_math = grade_english = grade_physics = 0;
	student_ID = 0;
}
void Student::info_set(const string& input_str) {
	std::istringstream input_buf(input_str);
	//Now input_buf behaves just like std::cin
	input_buf >> student_name >> student_ID >> grade_math >> grade_english >> grade_physics;
	grade_total = grade_math + grade_english + grade_physics;
}
void Student::info_print(std::ostream &os) {
	os << student_name << ' ' << student_ID << ' ' << grade_math << ' ' << grade_english << ' ' << grade_physics << std::endl;
}
void Student::info_find(std::ostream &os) {
	os << student_name << ' ' << grade_math << ' ' << grade_english << ' ' << grade_physics << std::endl;
}
void Student::score_print_each(std::ostream &os) {
	os << grade_math << ' ' << grade_english << ' ' << grade_physics << std::endl;
}
void Student::score_print_total(std::ostream &os) {
	os << grade_total << std::endl;
}

void string_split(const string& s, vector<string>& v, const string& c);
void find(long student_ID, vector<Student> &classroom, std::ostream &os);
void print_sort(vector<Student> &classroom, std::ostream &os);
void sort_quick(int left,int right, vector<vector<int>> &vec);

int main() {
	vector<Student> classroom;

	std::cout << "Section 1:" << std::endl
		<< "Please enter students' info like this:" << std::endl << std::endl
		<< "Name  Student_ID  Grade_math  Grade_English  Grade_physics" << std::endl << std::endl
		<< "Enter 'q' to indicate end of input." << std::endl
		<< "DO NOT USE LINE BREAKS AS END MARKERS FOR THIS SETCION!" << std::endl
		<< "输入字符q结束该部分的输入。" << std::endl
		<< "请勿将单独的换行符作为该部分结束的标志！" << std::endl;
	//Actrually, entering EOF will also end the input, but will have a slight impact on later parts.
	string input_str;
	while (std::getline(std::cin, input_str)) {
		//Read one line each time.
		if (input_str == "q") break;
		else {
			if (input_str.size() != 0) {
				vector<string> text_spilt;
				string_split(input_str, text_spilt, " ");
				//Actually the vector text_spilt does not participate in assignment.
				if (text_spilt.size() == 5) {
					Student student_temp;
					student_temp.info_set(input_str);
					classroom.push_back(student_temp);
					std::cout << "Input succeeded. Now there are " << classroom.size() << " student(s)." << std::endl;
				}
				else std::cout << "ERROR: Invalid input detected, please check your input." << std::endl;
			}
		}
	}
	std::cin.clear();
	std::cin.sync();

	std::cout << std::endl << "Section 2:" << std::endl
		<< "Please enter student's ID." << std::endl << std::endl
		<< "Enter 'q' to indicate end of input." << std::endl
		<< "DO NOT USE LINE BREAKS AS END MARKERS FOR THIS SETCION!" << std::endl
		<< "输入字符q结束该部分的输入。" << std::endl
		<< "请勿将单独的换行符作为该部分结束的标志！" << std::endl;
	//Actrually in this section, any non-numeric value entered will end the input.
	//Entering EOF will also end the input, but will have a slight impact on later parts.
	long check_ID = 0;
	while (std::cin >> check_ID) {
		find(check_ID, classroom, std::cout);
	}
	std::cin.clear(); 
	std::cin.sync();
	std::cin.ignore();

	std::cout << std::endl << "Section 3:" << std::endl
		<< "Now the info for element currently entered will be returned in descending order according to the total score." << std::endl
		<< "Entry anything to continue" << std::endl;
	std::cin.get();
	std::cin.get();
	print_sort(classroom, std::cout);
	return 0;
}

void string_split(const string& s, vector<string>& v, const string& c) {
	//Use string c to split string s into x parts, store them in vector v and return.
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2) {
		v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}
void find(long student_ID, vector<Student> &classroom, std::ostream &os) {
	for (unsigned int i = 0; i < classroom.size(); i++) {
		if (classroom[i].student_ID == student_ID) {
			classroom[i].info_find(os);
			return;
		}
	}
	os << "Student can't find, please check the student_ID entered" << std::endl;
	return;
}
void print_sort(vector<Student> &classroom, std::ostream &os) {
	if (classroom.size() == 0) {
		os << "There are not any student." << std::endl;
		return;
	}
	vector<vector<int>> vec(classroom.size());
	for (unsigned int i = 0; i < classroom.size(); i++) {
		vec[i].resize(2);
		vec[i][0] = classroom[i].grade_total;
		vec[i][1] = i;
	}
	sort_quick(0, vec.size() - 1, vec);
	for (unsigned int i = 0; i < classroom.size(); i++) {
		classroom[vec[i][1]].info_print(os);
	}
}
void sort_quick(int left, int right, vector<vector<int>> &vec) {
	int mid = (left + right) / 2;
	int i, j;
	int middle = vec[mid][0];
	i = left;
	j = right;
	while (j >= i) {
		while (middle < vec[i][0]) i++;
		while (middle > vec[j][0]) j--;
		if (i <= j) {
			vector<int> temp(2);
			temp[0] = vec[i][0];
			temp[1] = vec[i][1];
			vec[i][0] = vec[j][0];
			vec[i][1] = vec[j][1];
			vec[j][0] = temp[0];
			vec[j][1] = temp[1];
			i++;
			j--;
		}
	}
	if (i < right) sort_quick(i, right, vec);
	if (j > left) sort_quick(left, j, vec);
}