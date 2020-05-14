#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
public:
	int row, col;
	vector <double>elements;

	Matrix(int r, int c, vector<double>&ele);
	void display();
	void transposition();

	Matrix operator+(Matrix rhs);
	Matrix operator*(Matrix rhs);
	bool operator==(Matrix rhs);
};

Matrix::Matrix(int r, int c, vector<double>&ele)
{
	row = r;
	col = c;
	elements.assign(ele.begin(), ele.end());
}

void Matrix::display()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			cout << elements[i*col + j] << ' ';
		}
		cout << '\n';
	}
}

void Matrix::transposition()
{
	int i, j;

	vector<double> tem;
	tem.swap(elements);

	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			elements.push_back(tem[j*col + i]);
		}
	}
	swap(row, col);
	cout << "转置成功！" << '\n';
}

Matrix Matrix::operator+(Matrix rhs)
{
	vector<double> Res;
	for (int i = 0; i < row*col; i++)
	{
		double result = elements[i] + rhs.elements[i];
		Res.push_back(result);
	}

	return Matrix(row, col, Res);
}

Matrix Matrix::operator*(Matrix rhs)
{
	vector<double> Res;
	double sum = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < rhs.col; j++)
		{

			for (int k = 0; k < col; k++)
			{
				sum = elements[i*col + k] * rhs.elements[j*rhs.col + k] + sum;
			}

			Res.push_back(sum);
			sum = 0;
		}
	}

	return Matrix(row, rhs.col, Res);
}

bool Matrix::operator==(Matrix rhs)
{
	if (row == rhs.row && col == rhs.col)
	{
		for (int i = 0; i < row*col; i++)
		{
			if (elements[i] != rhs.elements[i])
				return false;
		}
	}
	else return false;

	return true;
}

void loop()
{
	cout << "初始化：请按要求输入您想插入的一个矩阵行数和列数（空格隔开）：\n";
	int r, c;
	cin >> r >> c;
	cout << "请按书写习惯格式输入矩阵的各个元素：" << endl;

	vector<double>ele;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			double element;
			cin >> element;
			ele.push_back(element);
		}
	}

	Matrix mat(r,c, ele);
	
	while (1)
	{
		cout << "\n请输入你想要进行的操作序号：\n" << "1.输出当前矩形\n"
			<< "2.转置\n" << "3.对当前矩形做加法\n"
			<< "4.对当前矩形做乘法\n" << "5.判断矩阵相等问题\n"<<"6.退出程序\n\n";

		cout << "您要选择的操作序号为：";
		int i; cin >> i;

		switch (i)
		{

		case 1:
		{
			mat.display();
			break;
		}

		case 2:
		{
			mat.transposition();
			break;
		}

		case 3:
		{	cout << "请输入矩阵的各个元素：(多输入无效）" << endl;

			vector<double>rhs;
			for (int i = 0; i < mat.row * mat.col; i++)
			{
				double result;
				cin >> result;
				rhs.push_back(result);
			}

			Matrix Rhs(mat.row, mat.col, rhs);
			mat = mat + Rhs;

			cout << "结果为\n";
			mat.display();
			break;
		}

		case 4:
		{	
			cout << "请输入矩阵的列数：" << endl;
			int rhs_col;
			cin >> rhs_col;

			cout << "请输入矩阵的各个元素：(多输入无效）" << endl;

			vector<double>rhs;
			for (int i = 0; i < mat.col * rhs_col; i++)
			{
				double result;
				cin >> result;
				rhs.push_back(result);
			}

			Matrix Rhs(mat.col, rhs_col, rhs);
			mat = mat * Rhs;

			cout << "结果为\n";
			mat.display();
			break;
		}

		case 5:
		{	
			cout << "请输入矩阵的行数和列数" << endl;
			int rhs_row, rhs_col;
			cin >> rhs_row >> rhs_col;

			cout << "请输入矩阵的各个元素：(多输入无效）" << endl;

			vector<double>rhs;
			for (int i = 0; i < rhs_row * rhs_col; i++)
			{
				double result;
				cin >> result;
				rhs.push_back(result);
			}

			Matrix Rhs(rhs_row, rhs_col, rhs);
			if (mat == Rhs)
				cout << "该矩阵与已知矩阵相等。" << endl;
			else
				cout << "该矩阵与已知矩阵不相等。" << endl;

			break;
		}

		case 6:
		{
			std::cout << "\n再见~\n";
			exit(0);
		}

		default:
			std::cout << "输入有误,请重新输入:\n";
			break;
		}
	}
}

int main()
{
	loop();
	return 0;
}