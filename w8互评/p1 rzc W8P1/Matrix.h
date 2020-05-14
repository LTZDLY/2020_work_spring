#pragma once
#include <iostream>
#include <vector>

class Matrix
{
private:
	int** data_;
	size_t row_;
	size_t column_;
public:
	Matrix();
	Matrix(size_t row, size_t column, const std::vector<int>& elem);
	Matrix(const Matrix& rhs_mat);
	Matrix(Matrix&& rhs_mat);
	Matrix& Transpose();
	Matrix operator+(const Matrix& rhs_mat);
	Matrix& operator+=(const Matrix& rhs_mat);
	Matrix operator*(const Matrix& rhs_mat);
	Matrix& operator*=(const Matrix& rhs_mat);
	Matrix& operator=(const Matrix& rhs_mat);
	Matrix& operator=(Matrix&& rhs_mat);
	bool operator==(const Matrix& rhs_mat);
	void Print()const;
	~Matrix();
};

