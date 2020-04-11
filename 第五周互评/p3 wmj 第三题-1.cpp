#include<iostream>
#include<vector>
#include<algorithm>

//使用英文是怕乱码，用中文是因为翻译都是瞎写的
//Use English because I'm afraid of situations like "uhcdiuah2983y9ew"
//Use Chinese because I translate xj8ly

//any problem, contact with me:1209497940

int main()
{
	//后来，我终于学会了如何vector
	//Later,I finally learn how to vector
	std::vector<double> numberPair;

	//后来，群里大哥说可能有小数
	//Later,big bro tell me that double may exists

	//可惜你却告诉我用一个临时变量
	//but you tell me use a temporary varible
	int tempNumber;

	//循环接受数据，Ctrl+Z结束数据输入
	//read data looply, use Ctrl+Z to stop the input of the data
	//linus:Ctrl+D
	while (std::cin >> tempNumber)
	{
		//快乐的加入vector之中
		//make it into the vector
		numberPair.push_back(tempNumber);
	}

	//如果空空如也，或非成双成对
	//if empty or not pairs
	if (numberPair.size() == 0 || numberPair.size() % 2 != 0)
	{
		//请您离开
		//please go away
		std::cout << "The number you input is not pairs";

		return 0;
	}

	//思路很显然，最后的结果需要最大
	//it is obvious of the silu because we need the max result
	//第一步必须做的事情，就是排序
	//what needs to be done first is to sort
	//最小的数字无论和谁组合，必然会出现在最后的结果中
	//no matter what it pairs with , the min number will appear in the last
	//因此要用最小的数字和次小的数字搭配，让次小数字别再出现
	//so we need to pari the min with the 2nd min to make it disapeear
	//之后，问题就转换成了(n-2)个数字最小值的最大值问题
	//then the proble becomes the max of the min in (n-2)
	//所以我们只要依次取序列号为偶数的数字即可(从0开始)
	//so we just need to calculate the double number(from 0)
	std::sort(numberPair.begin(), numberPair.end());

	//定义一个计算和的变量
	//define a varible which is used to calculate the sum
	int sumVector = 0;

	//开始计算
	//start to calculate

	for (std::vector<double>::iterator iter = numberPair.begin(); iter < numberPair.end(); iter += 2)
	{
		sumVector += *iter;
	}

	//输出结果
	//input the result
	std::cout << sumVector;

	return 0;
}
