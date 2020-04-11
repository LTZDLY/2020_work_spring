
#include <iostream>
using namespace std;
long long ans=0;

long long count=1;


int main(){
	long long num;
	cin>>num;
	ans+=num;
	while(cin.get()!='\n'){
		cin>>num;
		ans+=num;
		count++;
	}

	if(count%2==0)cout<<((count/2)*(count+1)-ans);
	else cout<<(((count+1)/2)*(count)-ans);
	return 0;
}
