#include <iostream>
#include <vector>
using namespace std;
class Matrix {
private:
	int row;
	int col;
	vector<double>data;

public:
	Matrix(int r, int c);
	Matrix transpose();
	void set(int l, int r, int elem);
	Matrix& operator+=(const Matrix&m);
	Matrix& operator*=(const Matrix&m);
	Matrix& operator=(const Matrix& m);
	Matrix& operator*(const Matrix& m);
	void set(int row,int col);
	void output();

};
Matrix::Matrix(int r, int c) {
	this->row = r;
	this->col = c;
	for (int i = 0; i < r * c; i++)
		this->data.push_back(0);
}
Matrix& Matrix::operator+=(const Matrix& m) {
	if (row == m.row && col == m.col) {
		for (int i = 0; i < data.size(); i++)
			data[i] += m.data[i];
		return *this;
	}
	else {
		cout << "不满足加法规则" << endl;
		return *this;
	}

}
Matrix& Matrix::operator=(const Matrix& m) {
	if (this == &m) {
		return *this;
	}
	while (data.size() < m.col * m.row)data.push_back(0);
	while (data.size() > m.col * m.row)data.pop_back();

	int countNum = 0;
	for (int i = 0; i < col * row; i++) {
		data[countNum] = m.data[countNum];
		countNum++;
	}
	return *this;
}
Matrix& Matrix::operator*=(const Matrix& m) {
	if (row == m.col) {
		Matrix temp(row, m.col);
		for(int i=0;i<temp.row;i++)
			for (int j = 0; j < temp.col; j++) {
				for (int k = 0; k < col; k++) {
					temp.data[i * temp.row + j] += data[i * row + k] * m.data[k * m.row + j];
				}
			}
		*this = temp;
		return *this;
	}
	else {
		cout << "不满足乘法运算" << endl;
		return *this;
	}
}
Matrix Matrix::transpose() {
	Matrix temp(row, col);
	for (int i = 0; i < temp.col; i++)
		for (int j = 0; j < temp.row; j++)
			temp.data[i * temp.row + j] = data[j * temp.col + i];
	return temp;
}
void Matrix::set(int row,int col) {
	this->row = row;
	this->col = col;
	double elem;
	int countNum = 0;
	for (int i = 0; i < row * col; i++) {
		cin >> elem;
		data[countNum] = elem;
		countNum++;
		
	}
}
void Matrix::output() {
	int countNum = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << data[countNum] << " ";
			countNum++;
		}
		cout << endl;
	}
		
}
int main() {
	cout << "输入矩阵A的行与列" << endl;
	int col,row;
	cin >> row >> col;
	Matrix A(row, col);
	A.set(row, col);
	cout << "输入矩阵B的行与列" << endl;
	cin >> row >> col;
	Matrix B(row, col);
	B.set(row, col);
	Matrix C(row, col);
	C = A;
	Matrix D(row, col);
	D = A;

	cout << "A+B为：" << endl;
	A += B;
	A.output();

	cout << "A的转置矩阵为：" << endl;
	D = D.transpose();
	D.output();

	cout << "A*B为" << endl;
	C *= B;
	C.output();

	return 0;



}