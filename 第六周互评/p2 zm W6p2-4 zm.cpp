#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

/* P2,P4 */ 
class Student
{
	public:
		string name;
		string id;
		int scoreMath;
		int scoreEnglish;
		int scorePhysics;
		
		//两个成员函数 P4
		int getSingleScore(char subject);
		int getTotalScore(void);
};
vector<Student> studentList;


/* P4 返回各科成绩 */
int Student::getSingleScore(char subject)
{
	switch(subject)
	{
		case 'M':return scoreMath;
		case 'E':return scoreEnglish; 
		case 'P':return scorePhysics;
	}
}

/* P4 返回总成绩 */
int Student::getTotalScore()
{
	return scoreMath+scoreEnglish+scorePhysics;
}

/* P2 */ 
bool find(vector<Student> &list,string targetId)
{
	for(int i=0;i<list.size();++i)
	{
		if(list[i].id==targetId)
		{
			
			cout<<list[i].name<<' '
				<<list[i].scoreMath<<' '
				<<list[i].scoreEnglish<<' '
				<<list[i].scorePhysics<<endl;
				 
			/* 想要用到成员函数  */
			/*
			cout<<list[i].name<<' '
				<<list[i].getSingleScore('M')<<' '
				<<list[i].getSingleScore('E')<<' '
				<<list[i].getSingleScore('P')<<endl;
			*/
			return 0;
		}
	}
	return 1;
}

/* P4 */ 
bool descending(Student a,Student b)
{ 
	return (a.getTotalScore()>=b.getTotalScore()); 
} 
void orderedOutput(vector<Student> list)
{	
	//依据总成绩降序对vector排序 
	sort(list.begin(),list.end(),descending);
	
	for(int i=0;i<list.size();++i)
	{
		cout<<list[i].name<<' '
			<<list[i].id<<' '
			<<list[i].scoreMath<<' '
			<<list[i].scoreEnglish<<' '
			<<list[i].scorePhysics<<endl;
	}
	return;
}


/* 写入数据到学生名单 */ 
void writeStudentList(int numStudent)
{
	Student someStudent;
	for(int i=0;i<numStudent;i++)
	{
		cin>>someStudent.name>>someStudent.id>>someStudent.scoreMath>>someStudent.scoreEnglish>>someStudent.scorePhysics;
		studentList.push_back(someStudent);
	}
	return;
}

int main()
{
	/* 检验自补部分 */ 
	int num=0;
	cin>>num;
	writeStudentList(num);//写入数据
	cout<<endl;
	/* 题目要求部分 */ 
	cout<<"Please enter the student id to search:"<<endl;
	string targetId;//P2
	cin>>targetId;//P2
	if(find(studentList,targetId))//P2 名单中没有该学号 
	{
		cout<<"There is no such student."<<endl;
	}
	cout<<endl;
	cout<<"The list ordered by total scores"<<endl;
	orderedOutput(studentList);//P3  
	return 0;
}
