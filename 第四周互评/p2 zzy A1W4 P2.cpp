#include<iostream>
#include<stdlib.h>
using namespace std;

bool IsLeapYear(int year) 
{
	if(year%400==0 || (year%100!=0 && year%4==0))
	{
		return true;
	}else{
		return false;
	}
}


int DaysofMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int DaysofEachMonth(int month, int year)
{
	int CountforMonth=0;
	CountforMonth=DaysofMonth[month-1];
	
	if(month==2 && IsLeapYear(year)){
		CountforMonth++;
	}
	
	return CountforMonth;
}


int DaysofEachYear(int year)
{
	int CountforYear=0;
	if(IsLeapYear(year)){
		CountforYear=366;
	}else{
		CountforYear=365;
	}
	
	return CountforYear;
 } 
 
 
 
int ForDifferentYear(int year1, int month1, int day1, int year2, int month2, int day2)
{
	int result;
	//计算完整年之间的天数差 
	while(year1!=(year2-1)){
		result+=DaysofEachYear(year1);
		year1++;
	}

	//计算年份小的到年末的天数
	while(month1!=12){
		result+=DaysofEachMonth(month1, year1);
		month1++;
	}
	
	result+=31-day1+1;
	
	//计算年份大的到年初的天数 
	while(month2!=1){
		result+=DaysofEachMonth(month2-1, year2);
		month2--;
	}
	
	result+=day2-1;


	return result;
}

int ForDifferentMonth(int year, int month1, int month2, int day1, int day2)
{
	int result=0;
	
	while(month1!=(month2-1)){
		result+=DaysofEachMonth(month1, year);
		month1++;
	}
	
	result+=DaysofEachMonth(month1, year)-day1+1;
	result+=day2-1;
	return result;
}

int main()
{
   int yearS, monthS, dayS;
   int yearE, monthE, dayE;
   char t1, t2;
   
   cin>>yearS>>t1>>monthS>>t2>>dayS;
   cin>>yearE>>t1>>monthE>>t2>>dayE;
   
   int result;
   //同年同月 
   if(yearS==yearE && monthS==monthE){
   	  result=abs(dayS-dayE);
   }else{
   	 //同年不同月
     if(yearS==yearE){
     	if(monthE>monthS){
     		result=ForDifferentMonth(yearS, monthS, monthE, dayS,dayE);
		 }else{
		 	result=ForDifferentMonth(yearS, monthE, monthS, dayE, dayS);
		 }
    }else{
    	if(yearE>yearS){
    		result=ForDifferentYear(yearS, monthS, dayS, yearE, monthE, dayE);
		}else{
			result=ForDifferentYear(yearE, monthE, dayE, yearS, monthS, dayS);
		}
	} 
   }
   
  cout<<result;
  return 0;

}
