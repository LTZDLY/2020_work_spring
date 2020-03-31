/**��� 
M�����˺� M���Ǻ�����������գ����뽫һ�����Ͷ�뺣�У�������˲����������ѣ���������һ���취��2M����Χ��һԲȦ���ӵ�һ���˿�ʼ���α�����ÿ������K���˾ͽ�������󺣣�
���ѭ������ֱ������M����Ϊֹ���������ŷ�������ʹÿ��Ͷ��󺣵Ķ��Ƿǽ�ͽ��(0<M<1000,1<K<1000)
*/

/* 
�����������ģ�⣬�����ݴ�ʱЧ�ʽϵͣ����Լɪ�򻷺��õݹ�Ľ��˳��� 
	 0 1 2 3 4 5 6 7 8 9	10�� ��Ϸ��ʼǰ 
1	 7 8 X 0 1 2 3 4 5 6	10�˻�ɱ�˺��»� 
2	 4 5   6 7 X 0 1 2 3	9�˻�ɱ�˺��»� 
3	 1 2   3 4   5 6 X 0    8�˻�ɱ�˺��»� 
����
��һ�����������һ�δ�����ת��Ϊһ��������Խ��Խ�ٵĻ���ÿ����ֻ�ҵ���һ�������ˣ�Ȼ�����»� 
��Ȼ����f[i-1]Ϊ��i-1Ȧ��λ�ã���һȦ������2*M-��i-1��+1��f[i-1]=(f[i]+K) mod ��2*M-��i-1��+1��;
��Ȼ����iȦ�������ߣ�2*M-i+1�������ˣ�����ʱ�����»������Ϊ��K-1��% ��2*M-i+1�� 
*/
#include<iostream>
#include<cstring>
#define GOOD '+'
#define BAD '@'
using namespace std;

//���ݴ��ڵ�Ȧ�����ҵ������������������ʱ��λ�� 
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
