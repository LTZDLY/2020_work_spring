#include<iostream>
#include<vector>
#include<algorithm>

//ʹ��Ӣ���������룬����������Ϊ���붼��Ϲд��
//Use English because I'm afraid of situations like "uhcdiuah2983y9ew"
//Use Chinese because I translate xj8ly

//any problem, contact with me:1209497940

int main()
{
	//������������ѧ�������vector
	//Later,I finally learn how to vector
	std::vector<double> numberPair;

	//������Ⱥ����˵������С��
	//Later,big bro tell me that double may exists

	//��ϧ��ȴ��������һ����ʱ����
	//but you tell me use a temporary varible
	int tempNumber;

	//ѭ���������ݣ�Ctrl+Z������������
	//read data looply, use Ctrl+Z to stop the input of the data
	//linus:Ctrl+D
	while (std::cin >> tempNumber)
	{
		//���ֵļ���vector֮��
		//make it into the vector
		numberPair.push_back(tempNumber);
	}

	//����տ���Ҳ����ǳ�˫�ɶ�
	//if empty or not pairs
	if (numberPair.size() == 0 || numberPair.size() % 2 != 0)
	{
		//�����뿪
		//please go away
		std::cout << "The number you input is not pairs";

		return 0;
	}

	//˼·����Ȼ�����Ľ����Ҫ���
	//it is obvious of the silu because we need the max result
	//��һ�������������飬��������
	//what needs to be done first is to sort
	//��С���������ۺ�˭��ϣ���Ȼ����������Ľ����
	//no matter what it pairs with , the min number will appear in the last
	//���Ҫ����С�����ֺʹ�С�����ִ��䣬�ô�С���ֱ��ٳ���
	//so we need to pari the min with the 2nd min to make it disapeear
	//֮�������ת������(n-2)��������Сֵ�����ֵ����
	//then the proble becomes the max of the min in (n-2)
	//��������ֻҪ����ȡ���к�Ϊż�������ּ���(��0��ʼ)
	//so we just need to calculate the double number(from 0)
	std::sort(numberPair.begin(), numberPair.end());

	//����һ������͵ı���
	//define a varible which is used to calculate the sum
	int sumVector = 0;

	//��ʼ����
	//start to calculate

	for (std::vector<double>::iterator iter = numberPair.begin(); iter < numberPair.end(); iter += 2)
	{
		sumVector += *iter;
	}

	//������
	//input the result
	std::cout << sumVector;

	return 0;
}
