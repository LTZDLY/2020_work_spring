#include<cstdio>
#include<iostream>
using namespace std;

int FindLeftNode(int temp, int index[], int M)
{
	for(int i=1; i<=2*M; i++){
		if(index[i]==temp){
			return i;
		}
	}
	return -1;
}

int main()
{
	int M,K;
	cin>>M>>K;
	
	int *data=new int[2*M];
	int *index=new int[2*M];
	
	//�����ʼ��
	int i,j;
	for(i=0; i<=2*M; i++){
		data[i]=i;
		index[i]=i+1;
	}
	index[2*M]=1;
	
	//���Լɪ������
	int turn=1; int temp=1; int count=1;
	for(i=1; turn<M+1; i=index[i]){
		if(count==K-1){
			temp=index[temp];
			
		   //ɾ�������� 
		    int left=FindLeftNode(temp, index, M);//�ҵ������ߵ�ǰһ���� 
		   //�ó�����ǰһ���˵�����ָ������ߵ����� 
		    index[left]=index[temp];
		    data[temp]=-1;
		
		  //ɾ�������ߵ�����
		    int kill=temp;
		    temp=index[temp];
		    index[kill]=-1;
		
		    turn++; 
		    count=1;
		}else{
			count++;
			temp=index[temp];
		}
		
	}
	
	for(i=1; i<=2*M; i++){
		if(data[i]==-1){
			cout<<'@';
		}else{
			cout<<'+';
		}
	}
	
	delete [] data;
	delete [] index;
	return 0;
 } 

