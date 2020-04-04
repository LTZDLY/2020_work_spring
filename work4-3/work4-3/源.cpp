#include<iostream>
#include<string>
#include<vector>
using namespace std;

template<typename typ_arb>
void sort_quick(const int left/*需排序的左端*/, const int right/*需排序的右端*/, typ_arb& arr/*需排序的数组*/) {
	//排序使用的快速排序算法，不考虑左端或右端的值超过int范围的情况
	int mid = (left + right) / 2;
	int i, j;//定义左端和右端
	typ_arb temp;//定义交换两数的中间变量
	typ_arb middle = arr[mid];//取中间值
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
	}//进行升序排序，不考虑降序需求
	if (i < right) sort_quick(i, right, arr);
	if (j > left) sort_quick(left, j, arr);
}
template<typename typ_arb>
void print_arr(const int length/*需输出的数组长度*/, const typ_arb arr/*需输出的数组*/) {
	for (int i = 0; i < length; i++) cout << arr[i] << " ";
	cout << endl;
}

int main() {
	long a[] = { 809691,916503,728926,200427,662765,332707,442516,706866,161898,540364,111569,608819,541489,998199 };
	double b[] = { 45.28477,9.42539,27.86058,33.72358,15.26590,23.61844,47.58611,38.93692,38.94538,19.32721 };
	string c[] = { "asdf","vsa","jhvr","gkhp","gbva","dosu","vbsdfaf","vaczzsa","chvasr","pdhgwf","cnidasd","hxisczxc" };
	cout << "以下为对整型的排序" << endl;
	int length_a = sizeof(a) / sizeof(a[0]);
	sort_quick(0, length_a - 1, a); 
	print_arr(length_a, a);
	cout << "以下为对浮点型的排序" << endl;
	int length_b = sizeof(b) / sizeof(b[0]);
	sort_quick(0, length_b - 1, b);
	print_arr(length_b, b);
	cout << "以下为对字符串型的排序" << endl;
	int length_c = sizeof(c) / sizeof(c[0]);
	sort_quick(0, length_c - 1, c);
	print_arr(length_c, c);
	//给string型数组排序中，优先考虑前面字母在ASCII码中的字典序，而不是各成员的长度
	vector<string> s_test_vec({ "Mike", "Alex", "Picasso", "Tom", "John" });
	int length_d = s_test_vec.size();
	sort_quick(0, length_d - 1, s_test_vec);
	return 0;
}