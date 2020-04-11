#include<iostream>
#include<string>
#include <sstream>
#include <vector>

class Student
{
public:
	void info_set(const std::string& input_str);
	void info_print(std::ostream &os);
	void score_print_each(std::ostream &os);
	void score_print_total(std::ostream &os);
	long student_ID = 0;
	std::string student_name;
private:
	int grade_sum = 0;
	int	grade_math = 0;
	int grade_english = 0;
	int grade_physics = 0;
};

void Student::info_set(const std::string& input_str) {
	std::istringstream input_buf(input_str);
	input_buf >> student_name >> student_ID >> grade_math >> grade_english >> grade_physics;
	grade_sum = grade_math + grade_english + grade_physics;
}
void Student::info_print(std::ostream &os) {
	os << student_name << ' ' << grade_math << ' ' << grade_english << ' ' << grade_physics << std::endl;
}
void Student::score_print_each(std::ostream &os) {
	os << grade_math << ' ' << grade_english << ' ' << grade_physics << std::endl;
}
void Student::score_print_total(std::ostream &os) {
	os << grade_sum << std::endl;
}

void find(std::vector<Student> classroom, long student_ID, std::ostream &os);

int main() {
	std::vector<Student> classroom;
	std::string input_str;
	std::cout << "Part 1:" << std::endl;
	std::cout << "Please enter students' info like this:" << std::endl << std::endl;
	std::cout << "Name  Student_ID  Grade_math  Grade_English  Grade_physics" << std::endl << std::endl;
	std::cout << "Enter EOF or 'q' to indicate end of input." << std::endl;
	while (std::getline(std::cin, input_str)) {
		if (input_str == "q")break;
		else {
			Student student_temp;
			student_temp.info_set(input_str);
			classroom.push_back(student_temp);
		}
	}
	std::cin.clear();
	std::cin.sync();
	std::cout << std::endl << "Part 2:" << std::endl;
	std::cout << "Please enter student's ID." << std::endl;
	std::cout << "Enter EOF or 'q' to indicate end of input." << std::endl;
	long check_ID = 0;
	while (std::cin >> check_ID) {
		find(classroom, check_ID, std::cout);
	}
	std::cin.clear();
	std::cin.sync();
	std::cout << std::endl << "Part 3:" << std::endl;

	return 0;
}

void find(std::vector<Student> classroom, long student_ID, std::ostream &os) {
	for (unsigned int i = 0; i < classroom.size(); i++) {
		if (classroom[i].student_ID == student_ID) {
			std::cout << classroom[i].student_name << ' ';
			classroom[i].score_print_each(std::cout);
			return;
		}
	}
	os << "Student can't find, please check the student_ID entered" << std::endl;
	return;
}