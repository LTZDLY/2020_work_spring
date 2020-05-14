/**题干 
M个好人和 M个非好人在深海上遇险，必须将一半的人投入海中，其余的人才能幸免于难，于是想了一个办法：2M个人围成一圆圈，从第一个人开始依次报数，每数到第K个人就将他扔入大海，
如此循环进行直到仅余M个人为止。问怎样排法，才能使每次投入大海的都是非教徒。(0<M<1000,1<K<1000)
*/

/* 
最初是用数组模拟，在数据大时效率较低，理解约瑟夫环后用递归改进了程序。 
	 0 1 2 3 4 5 6 7 8 9	10人 游戏开始前 
1	 7 8 X 0 1 2 3 4 5 6	10人环杀人后新环 
2	 4 5   6 7 X 0 1 2 3	9人环杀人后新环 
3	 1 2   3 4   5 6 X 0    8人环杀人后新环 
……
将一个环按照序号一次次死人转换为一个个人数越来越少的环，每个环只找到第一个死的人，然后创造新环 
显然，设f[i-1]为第i-1圈的位置，上一圈人数是2*M-（i-1）+1，f[i-1]=(f[i]+K) mod （2*M-（i-1）+1）;
显然，第i圈（报数者：2*M-i+1）死的人，死亡时的在新环的序号为（K-1）% （2*M-i+1） 
*/
#include<iostream>
#include<cstring>
#define GOOD '+'
#define BAD '@'
using namespace std;

//根据存在的圈数，找到无人死亡（即最初）时的位置 
int find_initial_position(int roundlife,int nCurheadcount,int nDeadnumber)
{
	if(roundlife==1)
	{
		return (nDeadnumber-1)%nCurheadcount;
	}
	return (find_initial_position(roundlife-1,nCurheadcount-1,nDeadnumber)+nDeadnumber)%nCurheadcount;
}

int main()
{
	int M=0;
	int K=0;
	cin>>M;
	cin>>K;
	char line[2000]={'\0'};
	for(int i=1;i<=M;i++)
	{
		line[find_initial_position(i,2*M,K)]=BAD;
	}
	for(int i=0;i<(2*M);i++)
	{
		if(line[i]==BAD)
		{
			cout<<line[i];
		}
		else
		{
			cout<<GOOD;
		}
	}
	return 0;
} 
