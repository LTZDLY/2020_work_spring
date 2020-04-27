#include<iostream>
#include<vector>
#include<string>
#include<ctime> 
#include<sstream>
using std::vector;
using std::string;

class Orange {
	friend class Plate;
public:
	Orange();
	Orange(int, int, bool);
	void SetRotten(int);
	void operator= (const Orange);
private:
	bool rotten_;
	bool empty_;
	int rot_time_;
	int x_;
	int y_;
};

Orange::Orange() {
	empty_ = true;
	rotten_ = false;
	rot_time_ = -1;
	x_ = y_ = -1;
}
Orange::Orange(int x, int y, bool rot) {
	rotten_ = rot;
	if (rot) rot_time_ = 0;
	else rot_time_ = -1;
	x_ = x;
	y_ = y;
	empty_ = false;
}
void Orange::SetRotten(int time) {
	rotten_ = true;
	rot_time_ = time;
}
void Orange::operator=(const Orange obj) {
	rotten_ = obj.rotten_;
	empty_ = obj.empty_;
	rot_time_ = obj.rot_time_;
	x_ = obj.x_;
	y_ = obj.y_;
}

class Plate {
public:
	bool Put(Orange, int, int);
	void Run();
	void BfsSearch(vector<string>, int);
	bool Check(int, int[3][3]);
	string Print(int[3][3]);
private:
	Orange obj_[3][3];
};

bool Plate::Put(Orange obj, int x, int y) {
	if (!obj_[x][y].empty_) return false;
	obj_[x][y] = obj;
	return true;
}
void Plate::Run() {
	vector<string> dir;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (obj_[i][j].rotten_) {
				std::stringstream temp;
				temp << i << " " << j;
				dir.push_back(temp.str());
				//Record coordinates of rotted oranges for BFS.
			}
		}
	}
	this->BfsSearch(dir, 1);//Using BFS method to calculate the result in advance.
}
void Plate::BfsSearch(vector<string> before, int time) {
	int step[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
	vector<string> now;
	for (unsigned i = 0; i < before.size(); i++) {
		std::istringstream input_buf(before[i]);
		int x, y;
		input_buf >> x >> y;
		for (int j = 0; j < 4; j++) {
			int next_x = x + step[j][0];
			int next_y = y + step[j][1];
			if (next_x < 0 || next_y < 0 || next_x > 2 || next_y > 2 || obj_[next_x][next_y].empty_ || obj_[next_x][next_y].rotten_)
				continue;
			obj_[next_x][next_y].rotten_ = true;
			obj_[next_x][next_y].rot_time_ = time;
			std::stringstream temp;
			temp << next_x << " " << next_y;
			now.push_back(temp.str());
			//Record coordinates of rotted oranges for BFS again.
		}
	}
	if (now.size() != 0)
		BfsSearch(now, time + 1);
}
bool Plate::Check(int time, int map[3][3]) {
	auto flag = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (obj_[i][j].empty_) continue;
			if (!obj_[i][j].rotten_ || obj_[i][j].rot_time_ > time) {
				map[i][j] = 1;
				flag = true;
			}
			else map[i][j] = -1;
		}
	}
	std::cout << Print(map) << std::endl;
	return flag;
}
string Plate::Print(int map[3][3]) {
	string str;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (map[i][j]) {
			case 0:
				str += "　";
				break;
			case 1:
				str += "Ｏ";
				break;
			case -1:
				str += "Ｘ";
				break;
			default:
				break;
			}
		}
		if (i != 2)str += '\n';
	}
	return str;
}

void StringSplit(const string&, vector<string>&, const string&);

int main() {
	//According to the question, all check commands must be given after the put command.
	//So we use sequence structure here.
	Plate plate;
	std::cout << "Section 1:" << std::endl
		<< "Please enter the oranges' info like this:" << std::endl
		<< "x	y	[T/F]" << std::endl << std::endl
		<< "The third parameter which represents the rotten state of the orange is optional." << std::endl
		<< "If the third parameter is ignored, the rotten state will be given randomly." << std::endl
		<< "Enter 'q' to indicate end of input." << std::endl;
	int map[3][3] = { {0} };
	while (true) {
		string input_str;
		while (input_str.size() == 0) std::getline(std::cin, input_str);
		if (input_str == "q") break;
		vector<string> text_split;
		StringSplit(input_str, text_split, " ");
		//Using text split to confirm whether the input meets the requirements.
		if (text_split.size() < 2) {
			std::cout << "ERROR: Invalid input detected, please try again." << std::endl;
			continue;
		}
		std::istringstream input_buf(input_str);
		int x, y;
		if (!(input_buf >> x >> y)) {
			std::cout << "ERROR: Invalid input detected, please try again." << std::endl;
			continue;
		}
		if (x < 0 || x > 2 || y < 0 || y > 2) {
			std::cout << "ERROR: Invalid input detected, please try again." << std::endl;
			continue;
		}
		bool rot;
		if (text_split.size() == 2) {
			srand((unsigned)time(NULL));
			rot = rand() % 2;
		}
		else {
			if (text_split[2] == "T")rot = true;
			else rot = false;
		}
		Orange obj(x, y, rot);
		if (plate.Put(obj, x, y)) {
			std::cout << "Succeed! You add a ";
			if (rot) {
				map[x][y] = -1;
				std::cout << "bad ";
			}
			else {
				map[x][y] = 1;
				std::cout << "good ";
			}
			std::cout << "orange at position (" << x << ", " << y << ")!" << std::endl;
			std::cout << plate.Print(map) << std::endl;
		}
		else std::cout << "Failed! We already have an orange at position (" << x << ", " << y << ")!" << std::endl;
	}
	
	plate.Run();//Using BFS method to calculate the result in advance.
	std::cout << "Section 2:" << std::endl
		<< "Please enter the observation time." << std::endl
		<< "Enter 'q' to indicate end of input." << std::endl;
	//Actrually in this section, any non-numeric value entered will end the input.
	while (true) {
		int time;
		if (!(std::cin >> time)) break;
		int temp[3][3] = { {0} };
		if (plate.Check(time, temp)) std::cout << "Happy!" << std::endl;
		else std::cout << "Sad!" << std::endl;
	}
	return 0;
}

void StringSplit(const string& s, vector<string>& v, const string& c) {
	//Use string c to split string s into x parts, store them in vector v and return.
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2) {
		v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}