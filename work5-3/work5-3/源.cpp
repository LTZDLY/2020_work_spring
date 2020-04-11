///To prevent misscoding, all comments are written in English.
#include<iostream>
#include<vector>

bool input_check(std::vector<int> &input_box);
void sort_quick(int left, int right, std::vector<int>& arr);
void print_output(const std::vector<int>& arr);

int main() {
	//Regardless of array length and array elements beyond the range of int or the array is float
	std::vector<int>input_box;
	std::cout << "Please enter values. Enter EOF or a non-numeric value to end input." << std::endl;
	while (input_check(input_box));
	sort_quick(0, input_box.size() - 1, input_box);
	print_output(input_box);
	return 0;
}

bool input_check(std::vector<int> &input_box){
	int input_temp = 0;
	if (std::cin >> input_temp) {
		//When the input is EOF or a non-numeric value value, it returns 0 and the loop exits.
		input_box.push_back(input_temp);
		return true;
	}
	else if (input_box.size() == 0 || input_box.size() % 2 != 0) {
		std::cout << "ERROR: Invalid input detected, the number of inputs must be even." << std::endl;
		exit(-1);
	}
	else return false;
}
void sort_quick(int left, int right, std::vector<int>& arr) {
	int mid = (left + right) / 2;
	int i, j;
	int temp;
	int middle = arr[mid];
	i = left;
	j = right;
	while (j >= i) {
		while (middle > arr[i]) i++;
		while (middle < arr[j]) j--;
		if (i <= j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}
	if (i < right) sort_quick(i, right, arr);
	if (j > left) sort_quick(left, j, arr);
}
void print_output(const std::vector<int>& arr) {
	int num = arr.size() / 2;
	long sum = 0;
	for (int i = 0; i < num; i++) sum += arr[2 * i];
	std::cout << sum << std::endl;
}

/*
According to the qusetion, after sorting all input data in ascending order, we divide every two data into a group.
At this point, the sum of the minimum values from each group must be the maximum.
*/