///To prevent misscoding, all comments are written in English.
#include<iostream>
#include<vector>

template<typename T>
long sum(int num, const T&p);
double avg(int num, long sum);
bool input_check(int &input_num);

int main() {
	//Regardless of array length and array elements beyond the range of int
	int input_num = 0;
	long sum_arr = 0;
	long sum_vec = 0;
	double avg_arr = 0;
	double avg_vec = 0;
	std::cout << "Please enter the length of the array." << std::endl;
	while (!input_check(input_num));
	std::vector<int> input_vec;
	int *input_arr = new (std::nothrow)int[input_num]();
	if (input_arr == NULL) {
		std::cout << "ERROR: Memory request error.";
		return -1;
	}
	std::cout << "Please enter array elements." << std::endl;;
	for (int i = 0; i < input_num; i++) {
		int input_temp;
		if (std::cin >> input_temp) {
			input_vec.push_back(input_temp);
			input_arr[i] = input_temp;
		}
		else {
			std::cout << "ERROR: Input is not numeric. Please check your inputs." << std::endl;
			return -1;
		}
	}
	sum_arr = sum(input_num, input_arr);
	sum_vec = sum(input_num, input_vec);
	avg_arr = avg(input_num, sum_arr);
	avg_vec = avg(input_num, sum_vec);
	if (sum_arr != sum_vec || abs(avg_arr - avg_vec) > 1e-6) {
		std::cout << "ERROR: There are some unknown errors.";
		delete[] input_arr;
		return -1;
	}
	else std::cout << sum_arr << " " << avg_arr << std::endl;
	delete[] input_arr;
	return 0;
}

template<typename T>
long sum(int num, const T&p) {
	long temp = 0;
	for (int i = 0; i < num; i++)temp += p[i];
	return temp;
}

inline double avg(int num, long sum) {
	return (double)sum / (double)num;
}

bool input_check(int &input_num) {
	if (!(std::cin >> input_num)) {
		std::cout << "ERROR: Input is not numeric. Please check your inputs." << std::endl;
		exit(-1);
	}
	else if (input_num <= 0) {
		std::cout << "ERROR: Invalid input detected. Please try again." << std::endl;
		return false;
	}
	return true;
}

/*
When the dynamic array and the maximum size allocated are in different functions,
the compiler detects warnings, and I don't know how to avoid them.
I am so vegetable.
*/