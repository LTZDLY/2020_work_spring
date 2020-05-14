#include <iostream>

using namespace std;

class Orange
{
private:
public:
	int state, time;
	void setOrange(int s, int t)
	{
		state = s;
		time = t;
	}
};

class Plate
{
	Orange plate[3][3];
	int count[3][3] = { 0 };
	bool Put(int x, int y)
	{
		if (count[x][y] == 0)
		{
			int s, t;
			cin >> s >> t;
			plate[x][y].setOrange(s, t);
			return true;
		}
		else
		{
			return false;
		}
	}

	int Check(int t)
	{
		int a;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				while (t--)
				{
					if (plate[i][j].time == 0)
					{
						plate[i - 1][j].time = 0;
						plate[i][j - 1].time = 0;
						plate[i + 1][j].time = 0;
						plate[i][j + 1].time = 0;
					}
					else
					{
						plate[i][j].time--;
					}
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (plate[i][j].time >= 0)
					cout << "Happy";
				return 0;
			}
		}
		cout << "Sad";
		return 0;
	}
};

int main() {
	return 0;
}