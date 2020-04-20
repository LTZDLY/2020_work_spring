#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm> 
using namespace std;
class student {
private:
	char name[20];
	char id[20];
	int mathPoint;
	int englishPoint;
	int physicsPoint;
	int pointSum;
public:
	void find(vector<student>vec);
	int totalPoint();
	void pointSort(vector<student>vec);
	void creat();
	void outPut();
	void outputAll();
};
int student::totalPoint() {
	return mathPoint + englishPoint + physicsPoint;
}
void student::creat() {
	cin >> name >> id >> mathPoint >> englishPoint >> physicsPoint;
	pointSum = totalPoint();
}
void student::outPut() {
	cout << name << ' ' << mathPoint << ' ' << englishPoint << ' ' << physicsPoint << endl;
}
void student::outputAll() {
	cout << name << ' ' << id << ' ' << mathPoint << ' ' << englishPoint << ' ' << physicsPoint << endl;
}
void student::find(vector<student>vec) {
	char tempId[20];
	cin >> tempId;
	int flag=0;
	for (int i = 0; i < vec.size(); i++) {
		if (!strcmp(vec[i].id, tempId)) {
			vec[i].outPut();
			flag=1;
			break;
		}
	}
	if (flag == 0)cout << "not find" << endl;
}
void student::pointSort(vector<student>vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec.size() - 1 - i; j++) {
			if (vec[i].pointSum > vec[j].pointSum) {
				swap(vec[i], vec[j]);
			}
		}
	}
	for (int i = 0; i < vec.size(); i++) {
		vec[i].outputAll();
	}
}

int main() {
	vector<student>vec;
	for (int i = 1; i <= 3; i++) {
		student temp;
		temp.creat();
		vec.push_back(temp);
	}
	student pupil;
	pupil.find(vec);
	pupil.pointSort(vec);
	return 0;
}