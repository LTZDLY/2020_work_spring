#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using std::vector;
using std::string;

template<typename T> class Matrix {
public:
	Matrix(int, int, vector<T>);
	Matrix(int, int);
	Matrix();
	Matrix Transpose();
	~Matrix();
	void Print(std::ostream& os);
	void operator= (const Matrix);
	Matrix operator+ (const Matrix);
	Matrix operator* (const Matrix);
	bool operator== (const Matrix);
private:
	int column_;
	int row_;
	vector<vector<T>> val_;
};

template<typename T> Matrix<T>::Matrix() { column_ = row_ = 0; }
template<typename T> Matrix<T>::Matrix(int lenth, int width) {
	row_ = lenth;
	column_ = width;
	val_.resize(row_);
	for (unsigned i = 0; i < val_.size(); i++)
		val_[i].resize(column_);
}
template<typename T> Matrix<T>::Matrix(int lenth, int width, vector<T> vec) {
	row_ = lenth;
	column_ = width;
	unsigned num = row_ * column_;
	val_.resize(row_);
	for (unsigned i = 0; i < val_.size(); i++)
		val_[i].resize(column_);
	for (unsigned i = 0; i < vec.size() && i < num; i++)
		val_[i / column_][i % column_] = vec[i];
}
template<typename T> Matrix<T>::~Matrix() {
}
template<typename T> void Matrix<T>::Print(std::ostream& os) {
	for (int i = 0; i < row_; i++) {
		for (int j = 0; j < column_; j++)
			os << val_[i][j] << " ";
		if (i != row_ - 1) os << std::endl;
	}
}
template<typename T> void Matrix<T>::operator=(const Matrix mat) {
	row_ = mat.row_;
	column_ = mat.column_;
	for (int i = 0; i < row_; i++) {
		for (int j = 0; j < column_; j++)
			val_[i][j] = mat.val_[i][j];
	}
}
template<typename T> Matrix<T> Matrix<T>::operator+(const Matrix mat) {
	if (mat.row_ != row_ || mat.column_ != column_) 
		throw "ERROR: Does not conform to the matrix addition rule, please try again.";
	Matrix<T> tmp = mat;
	for (int i = 0; i < row_; i++) {
		for (int j = 0; j < column_; j++)
			tmp.val_[i][j] = val_[i][j] + mat.val_[i][j];
	}
	return tmp;
}
template<typename T> Matrix<T> Matrix<T>::operator*(const Matrix mat) {
	if (row_ != mat.column_) 
		throw "ERROR: Does not conform to the matrix multiplication rule, please try again.";
	int num = row_;
	Matrix<T> tmp(column_, mat.row_);
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < column_ ; j++) {
			for (int k = 0; k < mat.row_ ; k++) {
				tmp.val_[j][k] += mat.val_[j][i] * val_[i][k];
			}
		}
	}
	return tmp;
}
template<typename T> bool Matrix<T>::operator==(const Matrix mat) {
	if (mat.row_ != row_ || mat.column_ != column_) 
		return false;
	for (int i = 0; i < row_; i++) {
		for (int j = 0; j < column_; j++)
			if (val_[i][j] != mat.val_[i][j])
				return false;
	}
	return true;
}
template<typename T> Matrix<T> Matrix<T>::Transpose() {
	Matrix<T> tmp;
	tmp.column_ = row_;
	tmp.row_ = column_;
	tmp.val_.resize(tmp.row_);
	for (unsigned i = 0; i < tmp.val_.size(); i++)
		tmp.val_[i].resize(tmp.column_);
	for (unsigned i = 0; i < tmp.val_.size(); i++) {
		for (unsigned j = 0; j < tmp.val_[i].size(); j++) {
			tmp.val_[i][j] = val_[j][i];
		}
	}
	return tmp;
}
template<typename T> std::ostream &operator<<(std::ostream& os, Matrix<T>& mat) {
	mat.Print(os);
	return os;
};

void loop();
void CommandInput(vector<Matrix<int>>&);
void CommandPrint(vector<Matrix<int>>&);
void CommandAdd(vector<Matrix<int>>&);
void CommandMultiply(vector<Matrix<int>>&);
void CommandTranspose(vector<Matrix<int>>&);

int main() {
	loop();
	return 0;
}

void loop() {
	using std::cout;
	using std::cin;
	using std::endl;
	cout << "W8P1" << endl
		<< "Use number to choose what you want to do." << endl
		<< "1: Input a matrix." << endl
		<< "2: Print a matrix." << endl
		<< "3: Add the two matrices." << endl
		<< "4: Multiply two matrices." << endl
		<< "5: Transpose the matrix." << endl
		<< "Enter any other to exit the program." << endl << endl
		<< "To input a matrix, you will need to enter the rows, columns and elements like this:" << std::endl
		<< "rows  columns" << endl << "element1  element2  ..." << endl << endl
		<< "To print a matrix, you need to enter the number of the matrix." << endl
		<< "To add up two matrices, you need to enter the number of the two matrices, and it will be saved as a new matrix." << endl
		<< "To multiply two matrices, you need to enter the number of the two matrices, and it will be saved as a new matrix." << endl
		<< "To transpose a matrix, you need to enter the number of the matrix, and it will be saved as a new matrix." << endl
		<< "Have your time!" << endl;
	int temp = 0;
	vector<Matrix<int>> mat;
	cout << "Now enter your command." << endl;
	while (cin>>temp) {
		try {
			switch (temp) {
			case 1:
				CommandInput(mat);
				break;
			case 2:
				CommandPrint(mat);
				break;
			case 3:
				CommandAdd(mat);
				break;
			case 4:
				CommandMultiply(mat);
				break;
			case 5:
				CommandTranspose(mat);
				break;
			default:
				return;
			}
		}
		catch(const char* msg){
			std::cerr << msg << std::endl;
			cout << "Now enter your command." << endl;
			continue;
		}
		cout << "Now enter your command." << endl;
	}
}

void CommandInput(vector<Matrix<int>>& mats) {
	std::cout << "command 1: Input a matrix." << std::endl;
	int lenth, width;
	vector<int> vec;
	while (std::cin >> lenth >> width) {
		if (lenth <= 0 || width <= 0)
			throw "ERROR: Invalid input detected, please try again.";
		string input_str;
		std::getchar();
		std::getline(std::cin, input_str);
		std::istringstream input_buf(input_str);
		int temp;
		while (input_buf >> temp) 
			vec.push_back(temp);
		Matrix<int> mat(lenth, width, vec);
		mats.push_back(mat);
		std::cout << mat << std::endl 
			<< "Add success! The number of the matrix is " << mats.size() << "." << std::endl;
		return;
	}
}
void CommandPrint(vector<Matrix<int>>& mats) {
	std::cout << "command 2: Print a matrix." << std::endl;
	int temp;
	while (std::cin >> temp) {
		if (temp <= 0)
			throw "ERROR: Invalid input detected, please try again.";
		if (temp > mats.size())
			throw "ERROR: There are not enough matricse here, please try again.";
		temp--;
		std::cout << mats[temp] << std::endl;
		return;
	}
}
void CommandAdd(vector<Matrix<int>>& mats) {
	std::cout << "command 3: Add up two matricse." << std::endl;
	int a, b;
	while (std::cin >> a >> b) {
		if (a <= 0 || b <= 0)
			throw "ERROR: Invalid input detected, please try again.";
		if (a > mats.size() || b > mats.size())
			throw "ERROR: There are not enough matricse here, please try again.";
		a--;
		b--;
		try {
			auto c = mats[a] + mats[b];
			mats.push_back(c);
			std::cout << c << std::endl
				<<"Add success! The number of the new matrix is " << mats.size() << "." << std::endl;
		}
		catch (const char* msg) {
			std::cerr << msg << std::endl;
		}
		return;
	}
}
void CommandMultiply(vector<Matrix<int>>& mats) {
	std::cout << "command 4: Multiply two matrices." << std::endl;
	int a, b;
	while (std::cin >> a >> b) {
		if (a <= 0 || b <= 0)
			throw "ERROR: Invalid input detected, please try again.";
		if (a > mats.size() || b > mats.size())
			throw "ERROR: There are not enough matricse here, please try again.";
		a--;
		b--;
		try {
			auto c = mats[a] * mats[b];
			mats.push_back(c);
			std::cout << c << std::endl
				<< "Multiply success! The number of the new matrix is " << mats.size() << "." << std::endl;
		}
		catch (const char* msg) {
			std::cerr << msg << std::endl;
		}
		return;
	}
}
void CommandTranspose(vector<Matrix<int>>& mats) {
	std::cout << "command 5: Transpose a matrix." << std::endl;
	int temp;
	while (std::cin >> temp) {
		if (temp <= 0)
			throw "ERROR: Invalid input detected, please try again.";
		if (temp > mats.size())
			throw "ERROR: There are not enough matricse here, please try again.";
		temp--;
		auto c = mats[temp].Transpose();
		mats.push_back(c);
		std::cout << c << std::endl
			<< "Transpose success! The number of the new matrix is " << mats.size() << "." << std::endl;
		return;
	}
}