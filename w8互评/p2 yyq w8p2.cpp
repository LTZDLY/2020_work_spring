#include <iostream>
#include <vector>
using namespace std;
class Orange {
private:
    int time;/*新鲜橘子为-1 腐烂橘子为0*/
    int state;/*新鲜橘子为0 腐烂橘子为1*/
public:
    Orange() {};
    Orange(int t, int s)
    {
        time = t;
        state = s;
    }
    int getState() { return state; }
    int getTime() { return time; }
    void changeState() { this->state = 1; }
    void changeTime() {  this->time++; }
};

void setOrange(vector<Orange>& orange)
{
    int num, time, state;
    cout << "请输入橘子数量：" << endl;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cout << "请输入腐烂时间、是否腐烂：" << endl;
        cin >> time >> state;
        Orange o(time, state);

        orange.push_back(o);
    }
}

class Plate {
private:
    int number;
    vector<Orange>orange;
    int array[3][3] = { 0 };
    Orange oarray[3][3];
public:
    Plate() {};
    bool Put(Orange o, int i, int j);
    void setPlate(vector<Orange>orange);
    bool inPlate(int i, int j);
    void Infect(int t);
    void Check(int i);
};

bool Plate::Put(Orange o, int i, int j)
{
    if (array[i][j] == 1)
        return false;
    else
        return true;
}

void Plate::setPlate(vector<Orange>orange)
{
    int num = orange.size();
    Orange o(-5, -5);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            oarray[i][j] = o;
        }
    }
    int x, y;
    for (int k = 0; k < num; k++)
    {
        while (1)
        {
            cout << "请输入要放置的横纵坐标：" << endl;
            cin >> x >> y;
            if (Put(orange[k], x, y))
            {
                array[x][y] = 1;
                oarray[x][y] = orange[k];
                break;
            }
        }
    }
}

/*判断是否在盘子中并且有橘子*/
bool Plate::inPlate(int i, int j)
{
    if (i >= 0 && i < 3 && j >= 0 && j < 3)
    {
        if (array[i][j] == 1)
            return true;
        else
           return false;
    }
    else
        return false;
}

void Plate::Infect(int t)
{
    //t分钟内橘子感染
    for (int tmp = 0; tmp < t; tmp++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (array[i][j] == 1 && oarray[i][j].getState()==1)
                {
                    if (inPlate(i - 1, j))
                    {
                        oarray[i - 1][j].changeState();
                        oarray[i - 1][j].changeTime();
                    }
                    if (inPlate(i, j - 1))
                    {
                        oarray[i][j - 1].changeState();
                        oarray[i][j - 1].changeTime();
                    }
                    if (inPlate(i + 1, j))
                    {
                        oarray[i + 1][j].changeState();
                        oarray[i + 1][j].changeTime();
                    }
                    if (inPlate(i, j + 1))
                    {
                        oarray[i][j + 1].changeState();
                        oarray[i][j + 1].changeTime();
                    }

                    oarray[i][j].changeTime();
                }
            }
        }
    }
}



void Plate::Check(int i)
{
    Infect(i);
    int che = 0;
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (oarray[x][y].getState() == 0)
            {
                cout << "Happy" << endl;
                che = 1;
                break;
            }
        }
        break;
    }

    if (che == 0)
        cout << "Sad" << endl;
}



int main()
{
    vector<Orange>orange;
    Plate plate;

    setOrange(orange);
    plate.setPlate(orange);


    int i;
    cout << "请输入要查询的时间：" << endl;
    cin >> i;
    plate.Check(i);

    system("pause");
    return 0;
}