#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(){
	vector<double> dvec;
	double tmp=0;
	while(cin>>tmp){
		dvec.push_back(tmp);
	}
	
	sort(dvec.begin(),dvec.end());
	double min_max=0;
	for(int i=0;i<dvec.size();i+=2){
		min_max+=dvec[i]; 
	}
	cout<<min_max;
	
	return 0;
}

