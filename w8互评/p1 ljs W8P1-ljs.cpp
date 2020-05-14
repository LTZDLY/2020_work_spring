#include<iostream>
#include<vector>
using namespace std;

class Matrix {
public:
	Matrix();
	Matrix(int, int, vector<double>);
	void transpose();
	Matrix operator+(const Matrix&);
	Matrix operator*(const Matrix&);
	bool operator==(const Matrix&);
	friend ostream& operator<<(ostream& os, const Matrix& mat);
private:
	int row, col;
	vector<vector<double>> matVec;
};

//默认构造函数
Matrix::Matrix() {
	row = 0;
	col = 0;
	vector<vector<double>> tmpVec(1, vector<double>(1, 0));
	matVec = tmpVec;
}

//以行数，列数，一维vector为参数的构造函数
Matrix::Matrix(int _row, int _col, vector<double> tmpVec)
	:row(_row), col(_col) {
	vector<double> rowVec;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			rowVec.push_back(tmpVec[i * col + j]);
		}
		matVec.push_back(rowVec);
		rowVec.clear();
	}
}

//矩阵的转置
void Matrix::transpose() {
	vector<vector<double>> tmpVec = matVec;
	vector<double> rowVec;
	matVec.clear();
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			rowVec.push_back(tmpVec[j][i]);
		}
		matVec.push_back(rowVec);
		rowVec.clear();
	}
	int tmp = row;
	row = col;
	col = tmp;
}

//矩阵的加法
Matrix Matrix::operator+(const Matrix& mat2) {
	Matrix ansMat;
	if (row != mat2.row || col != mat2.col) {
		cout << "不是合法的加法" << endl;
		return ansMat;
	}
	ansMat = *this;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			ansMat.matVec[i][j] = matVec[i][j] + mat2.matVec[i][j];
		}
	}
	return ansMat;
}

//矩阵的乘法
Matrix Matrix::operator*(const Matrix& mat2) {
	Matrix ansMat;
	if (col != mat2.row) {
		cout << "不是合法的乘法" << endl;
		return ansMat;
	}
	ansMat.row = row;
	ansMat.col = mat2.col;
	ansMat.matVec.clear();
	vector<double> rowVec;
	double tmp;
	for (int i = 0; i < ansMat.row; i++) {
		for (int j = 0; j < mat2.col; j++) {
			tmp = 0;
			for (int k = 0; k < mat2.row; k++) {
				tmp += matVec[i][k] * mat2.matVec[k][j];
			}
			rowVec.push_back(tmp);
		}
		ansMat.matVec.push_back(rowVec);
		rowVec.clear();
	}
	return ansMat;
}

//判断矩阵是否相等
bool Matrix::operator==(const Matrix& mat2) {
	if (row != mat2.row || col != mat2.col) {
		return false;
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (matVec[i][j] != mat2.matVec[i][j]) {
				return false;
			}
		}
	}
	return true;
}

//重载矩阵的ostream
ostream& operator<<(ostream& os, const Matrix& mat) {
	for (int i = 0; i < mat.row; i++) {
		for (int j = 0; j < mat.col; j++) {
			cout << mat.matVec[i][j] << " ";
		}
		cout << endl;
	}
	return os;
}

int main() {
	int row, col;
	vector<double> tmpVec;
	double tmpNum;
	cout << "请输入第一个矩阵的行数和列数，用空格隔开" << endl;
	cin >> row >> col;
	cout << "请输入第一个矩阵:" << endl;
	for (int i = 0; i < row * col; i++) {
		cin >> tmpNum;
		tmpVec.push_back(tmpNum);
	}
	Matrix mat1(row, col, tmpVec);
	tmpVec.clear();
	cout << "请输入第二个矩阵的行数和列数，用空格隔开" << endl;
	cin >> row >> col;
	cout << "请输入第二个矩阵:" << endl;
	for (int i = 0; i < row * col; i++) {
		cin >> tmpNum;
		tmpVec.push_back(tmpNum);
	}
	Matrix mat2(row, col, tmpVec);
	cout << "请输入你想进行的操作，1代表输出两个矩阵的转置，2代表输出两个矩阵的和，3代表输出两个矩阵的积，4代表判断两个矩阵是否相等" << endl;
	cin >> tmpNum;
	if (tmpNum == 1) {
		mat1.transpose();
		mat2.transpose();
		cout << mat1 << endl << mat2;
	}
	else if (tmpNum == 2) {
		cout << mat1 + mat2;
	}
	else if (tmpNum == 3) {
		cout << mat1 * mat2;
	}
	else if (tmpNum == 4) {
		if (mat1 == mat2) {
			cout << "两个矩阵相等";
		}
		else
		{
			cout << "两个矩阵不相等";
		}
	}
	return 0;
}