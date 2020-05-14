#include <iostream>
#include <vector>
#include <map>
using namespace std;

int curTime = 0;
class Orange {
private:
	bool _isRot = false;
	int _rotTime = -1;
public:
	Orange()
	{

	}
	Orange(bool isRot, int rotTime = -1) :
		_isRot(isRot), _rotTime(rotTime)
	{
		if (isRot && rotTime == -1)//如果default了的话，重置感染时间
			_rotTime = 0;

	}
	inline bool isRotOrange() { return _isRot; }
	inline int getRotTime() { return _rotTime; }
	inline void addRotTime() { _rotTime++; }
	inline void gotRot() { _isRot = true; }
};

class Plate {
private:
	vector<vector<Orange>> orangePlate;//存放橘子的盘
	map<pair<int, int>, bool> orangeOccupy;//橘子占用地图
	map<pair<int, int>, bool> rotOrange;//橘子腐烂地图
	vector<vector<int>> dirs = { {1,0},{0,1},{-1,0},{0,-1} };
public:
	Plate()
	{
		orangePlate.resize(3);
		for (int i = 0; i < 3; i++)
		{
			orangePlate[i].resize(3);
		}
	}
	bool isInRange(int x, int y)
	{
		if (x < 0 || y < 0)
			return 0;
		if (x >= 3 || y >= 3)
			return 0;
		return 1;
	}
	inline bool isEmpty(int x, int y)
	{
		if (orangeOccupy[{x, y}])
			return false;
		return true;
	}

	bool Put(Orange orangeToPut, int x, int y)
	{
		if (!isInRange(x, y))
			return false;
		if (!isEmpty(x, y))
			return false;
		orangePlate[x][y] = orangeToPut;
		orangeOccupy[{x, y}] = true;
		if (orangeToPut.isRotOrange())
			rotOrange[{x, y}] = true;
		return true;
	}
	void infect(int x, int y)
	{
		for (int i = 0; i < 4; i++)
		{
			int tmpX = x + dirs[i][0];
			int tmpY = y + dirs[i][1];
			if (isInRange(tmpX, tmpY) && orangeOccupy[{tmpX, tmpY}])
			{
				if (!rotOrange.count({ tmpX,tmpY }))
				{
					orangePlate[tmpX][tmpY].gotRot();
					//orangePlate[tmpX][tmpY].addRotTime();
					rotOrange[{tmpX, tmpY}]++;
				}
			}
		}
	}
	void timePlus()
	{
		for (auto& it : rotOrange)
		{
			if (orangePlate[it.first.first][it.first.second].getRotTime() >= 0)//只有摆放超过了1秒的橘子才拥有感染能力
				infect(it.first.first, it.first.second);
		}
		for (auto& it : rotOrange)
		{
			orangePlate[it.first.first][it.first.second].addRotTime();//所有橘子都时间++
		}
		
	}
	void printPlate()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (orangePlate[i][j].getRotTime() == -1)//如果未腐烂那就输出负一
					cout << -1 << " ";
				else
					cout << curTime - orangePlate[i][j].getRotTime() << " ";//如果已经腐烂了，则输出腐烂的时间
				//显然，腐烂的时间 == 当前时间 - 橘子感染上的时间
			}
			cout << endl;
		}
	}
	void Check(int i)
	{
		while (i--)
		{
			curTime++;
			timePlus();
			
			this->printPlate();//如果不想看到中间变化请删去此行，并且将其放在函数的最后一行。
			//cout << endl << endl;
		}
		int rotSum = 0, occupySum = 0;
		for (auto& it : rotOrange)
		{
			if (it.second == true)
				rotSum++;
		}
		for (auto& it : orangeOccupy)
		{
			if (it.second == true)
				occupySum++;
		}
		this->printPlate();
		if (rotSum == occupySum)
		{
			cout << "Sad" << endl;
		}
		else
		{
			cout << "Happy" << endl;
		}
		
	}
};

int main()
{
	vector<Orange> vOrange = { Orange(true,0),Orange(),Orange(),Orange(),Orange(),Orange(),Orange(),Orange(),Orange() };
	
	Plate plate;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 1 && j == 2) continue;
			if (i == 2 && j == 1) continue;
			plate.Put(vOrange[3 * i + j], i, j);
		}
	}
	for (int i = 0; i < 9; i++)
	{
		plate.Check(1);
	}
	return 0;
}