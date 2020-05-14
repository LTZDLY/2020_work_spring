#include<iostream>
#include<vector>

template<class elemtype>//矩阵的元素类型没有确定，因此建立类模板
class Matrix
{
private:
	int row_;
	int col_;
public:
	std::vector<elemtype> data_;
	Matrix() = default;//默认构造函数
	Matrix(int row, int col, std::vector<elemtype> data)//三参数构造函数
	{
		row_ = row;
		col_ = col;
		data_ = data;
	}
	Matrix(Matrix& data1)//copy constructor
	{
		col_ = data1.col_;
		row_ = data1.row_;
		data_ = data1.data_;
	}
	Matrix(int row,int col):row_(row),col_(col){}//双参数构造函数
	elemtype get_col() { return col_; }//获取列指标
	elemtype get_row() { return row_; }//获取行指标
	elemtype get_data(int row, int col) {
		return data_[(row - 1)*(col_)+col - 1];
	}//该函数通过矩阵的行列下标获取对应元素
	void rotate();//转置函数
	void copy(Matrix& data1);
	bool operator==(Matrix& data1)//重载==运算符
	{
		return (col_ == data1.col_&&row_ == data1.row_&&data_ == data1);
	}
	Matrix operator*(Matrix& data1);//重载*运算符

};

template<typename elemtype>
void Matrix<elemtype>::rotate()
{
	std::vector<elemtype> evec;
	for (int i = 0; i < col_; i++)
	{
		for (int j = 0; j < row_; j++)
		{
			evec.push_back(get_data(j + 1, i + 1));//直接将对应元素插入全新的vector中
		}
	}
	data_ = evec;//赋值
}


template<typename elemtype>
void Matrix<elemtype>::copy(Matrix<elemtype>& data1)
{
	col_ = data1.col_;
	row_ = data1.row_;
	data_ = data1.data_;
}



template<typename elemtype>
Matrix<elemtype> Matrix<elemtype>::operator*(Matrix& data1)//类中声明，所以为单参数
{
	Matrix<elemtype> cal_data(row_,data1.get_col());
	elemtype temp;
	if (col_ == data1.get_row())
	{
		for (int i = 0; i < row_; i++)
		{
			for (int j = 0; j < data1.get_col(); j++)
			{
				temp = 0;
				for (int k = 0; k < col_;k++)
				{
					temp += (get_data(i + 1, k + 1)*data1.get_data(k+1, j+1));
				}
				cal_data.data_.push_back(temp);//将计算的值放入新的vector中
			}
		}
		return cal_data;
	}

}


template<typename elemtype>
std::ostream& operator<<(std::ostream& os,Matrix<elemtype>& data)//重载输出运算符来输出数据
{
	for (int i = 0;i < data.get_row(); i++)
	{
		for (int j = 0; j < data.get_col(); j++)
			os << data.get_data(i + 1, j + 1)<<" ";
		os << std::endl;
	}
	return os;
}


template<typename elemtype>
Matrix<elemtype> operator+(Matrix<elemtype>& data1, Matrix<elemtype>& data2)//重载+运算符
{
	Matrix<elemtype> mat(data1.get_row(),data1.get_col());
	if (data2.get_col() == data1.get_col() && data2.get_row() == data1.get_row())
	{
		for (int i = 0; i < mat.get_row(); i++)
		{
			for (int j = 0; j < mat.get_col(); j++)
			{
				mat.data_.push_back(data1.get_data(i + 1, j + 1) + data2.get_data(i + 1, j + 1));
			}
		}
		return mat;
	}
	else
		std::cerr << "wrong data!";
}
int main()//测试主函数
{
	int data1[] = { 1,2,3,4,1,2,3,4,1,2,3,4 };
	int data2[] = { 2,3,4,5,3,4,5,6,2,3,4,5 };
	int data3[] = { 1,2,3,4,5,6,1,2,3,4,5,6 };
	std::vector<int> ivec1(data1, data1 + 12);
	std::vector<int> ivec2(data2, data2 + 12);
	std::vector<int> ivec3(data3, data3 + 12);
	Matrix<int> mat1(3, 4, ivec1);
	Matrix<int> mat2(3, 4, ivec2);
	Matrix<int> mat4(4, 3, ivec3);
    std::cout << "mat1" << std::endl;
	std::cout << mat1;
	std::cout << "mat2" << std::endl;
	std::cout << mat2;
	std::cout << "mat4:" << std::endl;
	std::cout << mat4;
	Matrix<int> mat3;
	mat3 = mat1 + mat2;
	std::cout << "mat3=mat1+mat2:" << std::endl;
	std::cout << mat3;
	Matrix<int> mat5;
	std::cout << "mat5=mat1*mat4:" << std::endl;
	mat5 = mat1 * mat4;
	std::cout << mat5;
	std::cout << "rotate mat5" << std::endl;
	mat5.rotate();
	std::cout << mat5;
	return 0;
}