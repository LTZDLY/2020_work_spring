#include<iostream>
#include<string>

using namespace std;
int check_input(int &num_last, int &num_through) {
	cin >> num_last >> num_through;
	if (num_last <= 0 || num_last >= 1000) {
		cout << "输入错误！M的值应大于0小于1000！请重新输入K和M！" << endl;
		return 1;
	}
	else if () {

	}
	else if (num_through <= 0 || num_through >= 1000) {
		cout << "输入错误！K的值应大于0小于1000！请重新输入K和M！" << endl;
		return 1;
	}
	else return 0;
}

void print_line(int *line, int num_all) {
	for (int i = 0; i < num_all; i++) {
		if (line[i] == 0)printf("+");
		else printf("@");
	}
}
int main() {
	int num_all;//总人数
	int num_last;//剩余人数
	int num_through;//第几个人会被扔下去
	cout << "请输入0到1000（不含）内的整数M，K（用空格隔开）" << endl;
	cout << "M代表剩余总人数，K代表第几个人会被扔下去" << endl;
	while (check_input(num_last, num_through)); //检查输入是否合理
	num_all = 2 * num_last;
	int *line = (int *)malloc(sizeof(int) * num_all);
	for (int i = 0; i < 2 * num_last; i++)line[i] = 0;//数组赋初值
	int num_now = num_all;//当前剩余人数
	int num_temp = 0;//当前报数
	int num_pointer = 0;//当前指向第几个人
	do {
		if (line[num_pointer % num_all] == 0) num_temp++;
		else {
			num_pointer++;
			continue;
		}
		if (num_temp % num_through == 0) {
			line[num_pointer % num_all] = 1;
			num_now--;
		}
		num_pointer++;
	} while (num_now != num_last);
	print_line(line, num_all);
	free(line);
	line = NULL;
	return 0;
}