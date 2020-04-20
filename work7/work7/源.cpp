#include<iostream>
#include<sstream>
#include<vector>
using std::string;
using std::vector;

class Point {
public:
	Point();
	Point(int, int);
	void Set(std::istream&);
	string Get();
	int GetX();
	int GetY();
	double GetMed(Point);
	void InfoPrint(Point, std::ostream&);
	void operator= (const Point);
private:
	int x_;
	int y_;
};	

Point::Point() { x_ = y_ = 0; }
Point::Point(int i, int j) { this->x_ = i, this->y_ = j; }//Use the "this" pointer to assign a value. I don't know what that means.
int Point::GetX() { return x_; }
int Point::GetY() { return y_; }
void Point::Set(std::istream &is) { is >> x_ >> y_; }
void Point::operator=(Point p) { x_ = p.GetX(), y_ = p.GetY(); }
string Point::Get() {
	std::stringstream ss;
	ss << "(" << x_ << ", " << y_ << ")";
	return ss.str();
}
double Point::GetMed(Point p) {
	double d = ((x_ - p.GetX()) ^ 2 + (y_ - p.GetY()) ^ 2) ^ (1 / 2);
	return d;
}
void Point::InfoPrint(Point p, std::ostream &os) {
	os << '(' << x_ << ", " << y_ << ") * (" << p.GetX() << ", " << p.GetY() << ") = " << GetMed(p) << std::endl;
}

class Rectangle {
public:
	Rectangle();
	void Set(const string&);
	long CalPeri();
	long CalArea();
	void InfoPrint(std::ostream &os);
	Point getUpperLeft();
	Point getLowerRight();
	void operator= (const Rectangle);
	bool operator> (const Rectangle);
	bool operator< (const Rectangle);
	friend std::ostream &operator<<(std::ostream &os, Rectangle &D);
private:
	Point upper_left_;
	Point lower_right_;
	long area_;
	long peri_;
};

Rectangle::Rectangle() { area_ = peri_ = 0; };
void Rectangle::Set(const string& input_str) {
	std::istringstream input_buf(input_str);
	upper_left_.Set(input_buf);
	lower_right_.Set(input_buf);
	area_ = CalArea();
	peri_ = CalPeri();
}
long Rectangle::CalArea() {
	long lenth = abs(upper_left_.GetX() - lower_right_.GetX());
	long width = abs(upper_left_.GetY() - lower_right_.GetY());
	long area = lenth * width;
	return area;
}
long Rectangle::CalPeri() {
	long lenth = abs(upper_left_.GetX() - lower_right_.GetX());
	long width = abs(upper_left_.GetY() - lower_right_.GetY());
	long peri = lenth * 2 + width * 2;
	return peri;
}
void Rectangle::InfoPrint(std::ostream &os) {
	os << "vertices: " << upper_left_.Get() << " (" << lower_right_.GetX() << ", " << upper_left_.GetY() << ") "
		<< lower_right_.Get() << " (" << upper_left_.GetX() << ", " << lower_right_.GetY() << ") " << std::endl
		<< "perimeter: " << peri_ << std::endl
		<< "area:" << area_;
}
Point Rectangle::getUpperLeft() { return upper_left_; }
Point Rectangle::getLowerRight() { return lower_right_; }
void Rectangle::operator=(Rectangle rec) {
	upper_left_ = rec.getUpperLeft();
	lower_right_ = rec.getLowerRight();
	area_ = rec.area_; 
	peri_ = rec.peri_;
}
bool Rectangle::operator>(Rectangle rec) {
	if (area_ > rec.area_)return true;
	if (area_ == rec.area_ && peri_ > rec.peri_)return true;
	return false;
}
bool Rectangle::operator<(Rectangle rec) {
	if (area_ < rec.area_)return true;
	if (area_ == rec.area_ && peri_ < rec.peri_)return true;
	return false;
}
std::ostream &operator<<(std::ostream &os, Rectangle &D) {
	D.InfoPrint(os);
	return os;
}

template <typename T> struct Node {
	T val_;
	Node* next_;
};
template <typename T> class List {
private:
	Node<T>* head;
public:
	List();
	~List();
	void HeadSet(T);
	void pop(int, std::ostream&, bool&);
	void append(T, int&);
	void print(int, std::ostream&);
};

template <typename T> List<T>::List() {
	head = new Node<T>();
}
template <typename T> List<T>::~List() {
	Node<T>* cur = head;
	if (cur == NULL) return;
	while (cur->next_ != NULL) {
		Node<T>* temp = cur;
		cur = cur->next_;
		delete temp;
	}
	delete cur;
}
template <typename T> void List<T>::pop(int n, std::ostream &os, bool &flag) {
	flag = true;
	Node<T>* cur = head;
	Node<T>* cur_bef = cur;
	for (int i = 1; i < n; i++) {
		cur_bef = cur;
		if (cur->next_ != NULL)cur = cur->next_;
		else {
			os << "ERROR: There are not enough rectangles here, please try again." << std::endl;
			flag = false;
			return;
		}
	}
	os << cur->val_ << std::endl;
	if (cur == head) {
		cur = head->next_;
		auto temp = head;
		head = cur;
		cur = temp;
		delete cur;
		return;
	}
	else {
		cur_bef->next_ = cur->next_;
		delete cur;
		return;
	}
}
template <typename T> void List<T>::append(T val, int &dir) {
	Node<T>* cur = head;
	dir = 1;
	if (val < cur->val_) {
		Node<T>* temp = new Node<T>();
		temp->next_ = head;
		temp->val_ = val;
		head = temp;
		return;
	}
	dir++;
	while (cur->next_ != NULL) {
		if (cur->next_->val_ < val) {
			cur = cur->next_;
			dir++;
		}
		else {
			Node<T>* temp = new Node<T>();
			temp->next_ = cur->next_;
			cur->next_ = temp;
			temp->val_ = val;
			return;
		}
	}
	if (cur->next_ == NULL) {
		cur->next_ = new Node<T>();
		cur = cur->next_;
		cur->val_ = val;
		return;
	}
	return;
}
template <typename T> void List<T>::HeadSet(T val){ head->val_ = val; }
template <typename T> void List<T>::print(int num, std::ostream& os) {
	Node<T>* cur = head;
	for (int i = 0; i < num && i < 3; i++) {
		cur = head;
		for (int j = 1; j < num - i; j++) {
			cur = cur->next_;
		}
		os << cur->val_ << std::endl;
	}
	/*
		os << val_ << std::endl;
		for (int i = 1; i < num; i++) {
			cur = cur->next_;
			os << val_ << std::endl;
		}
		return;
	}
	for (int i = 3; i < num; i++) cur = cur->next_;
	os << val_ << std::endl;
	for (int i = 0; i < 1; i++) {
		cur = cur->next_;
		os << val_ << std::endl;
	}*/
	return;
}

void loop();
void string_split(const string&, vector<string>&, const string&);
void command_input(List<Rectangle>*&, int&);
void command_pop(List<Rectangle>*&, int&);
void command_print(List<Rectangle>*&, int&);

int main() {
	loop();
	return 0;
}

void loop() {
	List<Rectangle> *list = nullptr;
	using std::cout;
	using std::cin;
	using std::endl;
	cout << "W7P1-3" << endl
		<< "Use number to choose what you want to do." << endl
		<< "1: Input a rectangle." << endl
		<< "2: Pop a rectangle." << endl
		<< "3: Print the list." << endl
		<< "Enter any other to exit the program." << endl << endl
		<< "To input a rectangle, you will need to enter the coordinates of the upper left and lower right points of the rectangle like this:" << std::endl
		<< "upper_left.x  upper_left.y  lower_right.x  lower_right.y" << endl << endl
		<< "And to pop a rectangle, you only need to enter a number." << endl
		<< "Have your time!" << endl;
	int temp = 0;
	int num = 0;
	cout << "Now enter your command." << endl;
	while (cin >> temp) {
		switch (temp) {
		case 1:
			command_input(list, num);
			break;
		case 2:
			command_pop(list, num);
			break;
		case 3:
			command_print(list, num);
			break;
		default:
			delete list;
			return;
		}
		cout << "Now enter your command." << endl;
	}
}
void string_split(const string& s, vector<string>& v, const string& c) {
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
void command_input(List<Rectangle>* &list, int &num) {
	std::cout << "command 1: enter a rectangle." << std::endl;
	string temp_str;
	auto cur = list;
	while (true) {
		while (temp_str.size() == 0)std::getline(std::cin, temp_str);
		int dir = 0;
		vector<string> text_spilt;
		Rectangle temp_rec;
		string_split(temp_str, text_spilt, " ");
		if (text_spilt.size() == 4) {
			temp_rec.Set(temp_str);
			if (list == NULL) {
				list = new List<Rectangle>();
				list->HeadSet(temp_rec);
				dir = 1;
			}
			else list->append(temp_rec, dir);
			num++;
			std::cout << "Insert rectangle successful! The rectangle is inserted at position " << dir
				<< ".There are currently " << num << " rectangle(s) in the list." << std::endl;
			return;
		}
		std::cout << "ERROR: Invalid input detected, please try again." << std::endl;
		temp_str = "";
	}
}
void command_pop(List<Rectangle>* &list, int &num) {
	std::cout << "command 2: enter a number." << std::endl;
	int temp;
	while (true) {
		if (std::cin >> temp) {
			if (temp <= 0) {
				std::cout << "Error: Invalid input detected, please try again." << std::endl;
				continue;
			}
			bool flag = true;
			list->pop(temp, std::cout, flag);
			if (flag) {
				num--;
				std::cout << "delete rectangle successful! The rectangle is deleted at position " << temp
					<< ".There are currently " << num << " rectangle(s) in the list." << std::endl;
				return;
			}
		}
		std::cout << "ERROR: Invalid input detected, please try again." << std::endl;
		std::cin.clear();
		std::cin.sync();
		std::cin.ignore();
	}
}
void command_print(List<Rectangle>* &list, int &num) {
	list->print(num, std::cout);
	if (num < 3) {
		std::cout << "There are only " << num << " rectangle(s) in the list." << std::endl;
	}
}