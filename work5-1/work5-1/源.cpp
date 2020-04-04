///To prevent misscoding, all comments are written in English.
#include<iostream>
#include<vector>

bool input_check(std::vector<int> &input_box, int &input_max, int &input_num);
void value_search(const std::vector<int> &input_box, int input_max);

int main() {
	int input_max = 0;
	int input_num = 0;
	std::vector<int> input_box;
	std::cout << "Please enter values. Enter EOF or a non-numeric value to end input." << std::endl;
	//When the input is EOF or a non-numeric value value, it returns 0 and the loop exits
	while (input_check(input_box, input_max, input_num));
	value_search(input_box, input_max);
	return 0;
}

bool input_check(std::vector<int> &input_box, int &input_max, int &input_num) {
	int input_temp = 0;
	if (std::cin >> input_temp) {
		if (input_temp > input_max)input_max = input_temp;
		input_box.push_back(input_temp);
		input_num++;
		return true;
	}
	else if (input_max == 0) {
		std::cout << "ERROR: At least one input is required. Please try again." << std::endl;
		exit(-1);
	}
	else if (input_num - input_max < -1) {
		std::cout << "ERROR: Invaild input detected. Please try again." << std::endl;
		exit(-1);
	}
	else return false;
}

void value_search(const std::vector<int> &input_box, int input_max) {
	int *num = new (std::nothrow)int[input_max + 1]();
	if (num == NULL) {
		std::cout << "ERROR: Memory request error.";
		exit(-1);
	}
	for (int i = 0; i < input_max; i++) num[i] = 0;
	for (int i = 0; i < input_max; i++) num[input_box[i]] = -1;
	for (int i = 0; i < input_max; i++) {
		if (num[i] == 0) {
			std::cout << i << std::endl;
			delete[] num;
			return;
		}
	}
	std::cout << input_max + 1 << std::endl;
	delete[] num;
	return;
}

/*
When the dynamic array and the maximum size allocated are in different functions,
the compiler detects warnings, and I don't know how to avoid them.
I am so vegetable.
*/