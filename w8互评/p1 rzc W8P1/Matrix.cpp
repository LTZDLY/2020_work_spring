#include "Matrix.h"

Matrix::Matrix()
	:row_(0), column_(0), data_() {}

Matrix::Matrix(size_t row, size_t column, const std::vector<int>& elem)
	: row_(row), column_(column)
{
	data_ = new int*[row_];
	for (size_t i = 0; i < row_; i++)
	{
		data_[i] = new int[column_];
		for (size_t j = 0; j < column_; j++)
		{
			data_[i][j] = elem[i*column_ + j];
		}
	}
}

Matrix::Matrix(const Matrix& rhs_mat)
	:row_(rhs_mat.row_),column_(rhs_mat.column_)
{
	std::cout << "Copy constructor is called.\n";
	data_ = new int*[row_];
	for (size_t i = 0; i < row_; i++)
	{
		data_[i] = new int[column_];
		for (size_t j = 0; j < column_; j++)
		{
			data_[i][j] = rhs_mat.data_[i][j];
		}
	}
}

Matrix::Matrix(Matrix&& rhs_mat)
	:row_(rhs_mat.row_),column_(rhs_mat.column_)
{
	std::cout << "Move constructor is called.\n";
	data_ = rhs_mat.data_;
	rhs_mat.data_ = nullptr;
}

Matrix& Matrix::Transpose()
{
	//分配新的矩阵
	int **temp_mat;
	size_t temp_row = column_;
	size_t temp_column = row_;
	temp_mat = new int*[temp_row];
	for (size_t i = 0; i < temp_row; i++)
	{
		temp_mat[i] = new int[temp_column];
		for (size_t j = 0; j < temp_column; j++)
		{
			temp_mat[i][j] = data_[j][i];
		}
	}
	//释放原矩阵内存
	for (size_t i = 0; i < row_; i++)
	{
		delete[]data_[i];
	}
	delete[]data_;
	//将data_指向新矩阵
	data_ = temp_mat;
	row_ = temp_row;
	column_ = temp_column;
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs_mat)
{
	try
	{
		if (row_ != rhs_mat.row_ || column_ != rhs_mat.column_)
		{
			throw std::invalid_argument("This two matrix cannot be added.\n");
		}
		for (size_t i = 0; i < row_; i++)
		{
			for (size_t j = 0; j < column_; j++)
			{
				data_[i][j] += rhs_mat.data_[i][j];
			}
		}
	}
	catch (std::invalid_argument err)
	{
		std::cerr << err.what();
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& rhs_mat)
{
	Matrix temp(*this);
	temp += rhs_mat;
	return temp;
}

Matrix& Matrix::operator*=(const Matrix& rhs_mat)
{
	try
	{
		if (column_ != rhs_mat.row_)
		{
			throw std::invalid_argument("This two matrix cannot be multiplied.\n");
		}
		int **temp_mat;
		size_t temp_row = row_;
		size_t temp_column = rhs_mat.column_;
		temp_mat = new int*[temp_row];
		for (size_t i = 0; i < temp_row; i++)
		{
			temp_mat[i] = new int[temp_column];
			for (size_t j = 0; j < temp_column; j++)
			{
				int sum = 0;
				for (size_t k = 0; k < column_; k++)
				{
					sum += data_[i][k] * rhs_mat.data_[k][j];
				}
				temp_mat[i][j] = sum;
			}
		}
		for (size_t i = 0; i < row_; i++)
		{
			delete[]data_[i];
		}
		delete[]data_;
		//将data_指向新矩阵
		data_ = temp_mat;
		row_ = temp_row;
		column_ = temp_column;
	}
	catch (std::invalid_argument err)
	{
		std::cerr << err.what();
	}
	return *this;
}

Matrix Matrix::operator*(const Matrix& rhs_mat)
{
	Matrix temp_mat(*this);
	temp_mat *= rhs_mat;
	return temp_mat;
}

Matrix& Matrix::operator=(const Matrix& rhs_mat)
{
	std::cout << "Copy assignment operator is called.\n";
	Matrix temp_mat(rhs_mat);
	for (size_t i = 0; i < row_; i++)
	{
		delete[]data_[i];
	}
	delete[]data_;
	*this = std::move(temp_mat);
	temp_mat.data_ = nullptr;
	return *this;
}

Matrix& Matrix::operator=(Matrix&& rhs_mat)
{
	std::cout << "Move assignment operator is called.\n";
	if (this != &rhs_mat)
	{
		row_ = rhs_mat.row_;
		column_ = rhs_mat.column_;
		data_ = rhs_mat.data_;
		rhs_mat.data_ = nullptr;
	}
	return *this;
}

bool Matrix::operator==(const Matrix& rhs_mat)
{
	if (row_ != rhs_mat.row_ || column_ != rhs_mat.column_)
	{
		return false;
	}
	for (size_t i = 0; i < row_; i++)
	{
		for (size_t j = 0; j < column_; j++)
		{
			if (data_[i][j] != rhs_mat.data_[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

void Matrix::Print()const
{
	for (size_t i = 0; i < row_; i++)
	{
		for (size_t j = 0; j < column_; j++)
		{
			std::cout << data_[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}
Matrix::~Matrix()
{
	if (data_ != nullptr)
	{
		for (size_t i = 0; i < row_; i++)
		{
			delete[]data_[i];
		}
		delete[]data_;
	}
}