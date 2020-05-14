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

//Ĭ�Ϲ��캯��
Matrix::Matrix() {
	row = 0;
	col = 0;
	vector<vector<double>> tmpVec(1, vector<double>(1, 0));
	matVec = tmpVec;
}

//��������������һάvectorΪ�����Ĺ��캯��
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

//�����ת��
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

//����ļӷ�
Matrix Matrix::operator+(const Matrix& mat2) {
	Matrix ansMat;
	if (row != mat2.row || col != mat2.col) {
		cout << "���ǺϷ��ļӷ�" << endl;
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

//����ĳ˷�
Matrix Matrix::operator*(const Matrix& mat2) {
	Matrix ansMat;
	if (col != mat2.row) {
		cout << "���ǺϷ��ĳ˷�" << endl;
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

//�жϾ����Ƿ����
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

//���ؾ����ostream
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
	cout << "�������һ��������������������ÿո����" << endl;
	cin >> row >> col;
	cout << "�������һ������:" << endl;
	for (int i = 0; i < row * col; i++) {
		cin >> tmpNum;
		tmpVec.push_back(tmpNum);
	}
	Matrix mat1(row, col, tmpVec);
	tmpVec.clear();
	cout << "������ڶ���������������������ÿո����" << endl;
	cin >> row >> col;
	cout << "������ڶ�������:" << endl;
	for (int i = 0; i < row * col; i++) {
		cin >> tmpNum;
		tmpVec.push_back(tmpNum);
	}
	Matrix mat2(row, col, tmpVec);
	cout << "������������еĲ�����1����������������ת�ã�2���������������ĺͣ�3���������������Ļ���4�����ж����������Ƿ����" << endl;
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
			cout << "�����������";
		}
		else
		{
			cout << "�����������";
		}
	}
	return 0;
}