//本程序在 3x3 的盘子上由用户输入放置新鲜或腐烂的橘子
//放置完毕后模拟相邻腐烂的过程并记录每个橘子腐烂的时间
//最后获取用户输入的时间以查看此时是否仍有新鲜橘子
//部分初始化操作在 -std=c++11 或 -std=gnu++11 编译选项下正常
#include <iostream>
#include <utility>
#include <queue>

class Orange
{
private:
	bool _decayed;
	int _decay_time;

public:
	Orange()
	{
		_decayed = false;
		_decay_time = -1;
	}

	bool Decay(const int minute = 0) 
	{
		if (!_decayed)	//防止重复腐烂
		{
			_decayed = true;
			_decay_time = minute;
			return true;
		}
		return false;
	}

	 bool IsDecayed() const  { return _decayed; }
};

class Plate
{
private:
	typedef std::pair<int, int> Location;
	struct Position
	{
		bool _is_exist = false;
		Orange _inner;
	};

	const int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} }, _length = 3;
	int _all_decayed_time;
	Position _plate[3][3];
	
	inline bool InPlate(const int i, const int j) const;
	bool Put(const Orange& rhs, const int i, const int j);
	int Classify(std::queue<Location>& decayed_location);

public:
	Plate() { _all_decayed_time = -1; }
	void Set();
	void BFS();
	void Check(const int i) const;
};

inline bool Plate::InPlate(const int i, const int j) const
{
	return i >= 0 && i < _length&& j >= 0 && j < _length;
}

bool Plate::Put(const Orange& rhs, const int i, const int j)
{
	if (InPlate(i, j) && !_plate[i][j]._is_exist)
	{
		_plate[i][j]._is_exist = true;
		_plate[i][j]._inner = rhs;
		return true;
	}
	std::cerr << "Unable to put orange to "
		<< i << ',' << j << " !\n";
	return false;
}

//对新鲜橘子计数，让腐烂橘子入队
int Plate::Classify(std::queue<Location>& decayed_location)
{
	int fresh_orange = 0;
	for (int i = 0; i < _length; i++)
		for (int j = 0; j < _length; j++)
			if (_plate[i][j]._is_exist)
			{
				if (_plate[i][j]._inner.IsDecayed())
					decayed_location.push({ i,j });
				else
					fresh_orange++;
			}
	return fresh_orange;
}

//在盘子内放置橘子
void Plate::Set()
{
	int x, y;
	Orange fresh, decayed;
	decayed.Decay();

	std::cout << "Attention : The size of plate is 3 x 3 from 0 to 2.\n"
		<< "Please type in the location of FRESH oranges like this :\n"
		<< "x1 y1\n" << "x2 y2\n" << "...\n"
		<< "And use Ctrl + Z to end typing in.\n";
	while (std::cin >> x >> y)
		(*this).Put(fresh, x, y);
	std::cin.clear();

	std::cout << "Now you can type in DECAYED oranges!\n";
	while (std::cin >> x >> y)
		(*this).Put(decayed, x, y);
	std::cin.clear();
}

//宽度优先搜索模拟腐坏过程
void Plate::BFS()
{
	int num = 0, time = 0;
	std::queue<Location> orange;
	int fresh_orange = Classify(orange);

	while (!orange.empty())	//队列中仍有有感染能力的橘子时继续
	{
		if (fresh_orange == 0)	//原有橘子全腐烂，跳出
			break;

		time++;
		num = orange.size();
		while (num--)	//每1分钟内多处同时感染
		{
			Location focus = orange.front();
			orange.pop();

			for (int i = 0; i < 4; i++)
			{
				//四方向搜索并模拟感染
				int x = focus.first + dir[i][0], y = focus.second + dir[i][1];
				if (InPlate(x, y) && _plate[x][y]._is_exist &&
					!_plate[x][y]._inner.IsDecayed())
				{
					fresh_orange--;
					orange.push({ x,y });
					_plate[x][y]._inner.Decay(time);
				}
			}
		}
	}
	if (fresh_orange == 0)	//排除存在不可能被感染到的橘子的情况
		_all_decayed_time = time;
}

void Plate::Check(const int i) const
{
	if (i < 0)
		std::cerr << "Invalid time!\n";
	else if (_all_decayed_time == -1 || i < _all_decayed_time)
		std::cout << "Happy\n";
	else
		std::cout << "Sad\n";
}


int main()
{
	Plate plate;
	plate.Set();
	plate.BFS();

	int time;
	std::cout << "Please type in time to see if there still are fresh oranges:\n";
	while (std::cin >> time)
		plate.Check(time);
	std::cin.clear();

	std::cout << "See you next time!";
	return 0;
}
