#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <cmath>
#include <utility>

class Orange
{
private:
    int time_;
    bool rot_;

public:
    friend class Plate;
    Orange() = default;
    explicit Orange(bool rot) : time_(rot ? 0 : -1), rot_(rot) {}

    ~Orange() = default;
};

class Plate
{
private:
    std::vector<Orange> data_;
    std::array<std::array<int, 3>, 3> index_;

public:
    Plate()
    {
        std::array<int, 3> temp;
        temp.fill(-1);
        index_.fill(temp);
    }

    ~Plate() = default;

    bool Boundary(int x, int y)
    {
        return x >= 0 && x < 3 && y >= 0 && y < 3;
    }

    bool Put(const Orange &orange, int x, int y)
    {
        if ((!Boundary(x, y)) || (~index_[x][y]))
            return false;
        index_[x][y] = data_.size();
        data_.push_back(orange);
        return true;
    }

    void Solve()
    {
        std::queue<std::pair<int, int> /**/> que;
        for (auto i : {0, 1, 2})
            for (auto j : {0, 1, 2})
                if ((~index_[i][j]) && data_[index_[i][j]].rot_)
                    que.push(std::pair<int, int>(i, j));
        /* BFS */
        while (!que.empty())
        {
            auto x = que.front().first;
            auto y = que.front().second;
            auto time = data_[index_[x][y]].time_;
            que.pop();
            int delta[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
            for (auto i : delta)
            {
                auto tx = x + i[0];
                auto ty = y + i[1];
                if (Boundary(tx, ty) && (~index_[tx][ty]) && (!data_[index_[tx][ty]].rot_))
                {
                    data_[index_[tx][ty]].time_ = time + 1;
                    data_[index_[tx][ty]].rot_ = true;
                    que.push(std::pair<int, int>(tx, ty));
                }
            }
        }
    }

    void Check(int i)
    {
        for (auto j : data_)
        {
            if (!j.rot_ || i < j.time_)
            {
                std::cout << "Happy" << std::endl;
                return;
            }
        }
        std::cout << "Sad" << std::endl;
    }
};

int main()
{
    try
    {
        /* 
        You can follow this pattern to add some testing data.
        plate.Put(Orange(A),X,Y);
        A is a bool value, true means the orange has rotted,otherwise it is false.
        X is the horizontal cordinate ranges form 0 to 2.
        Y is the vertical  cordinate ranges form 0 to 2.*/
        Plate plate;
        plate.Put(Orange(true), 0, 0);
        plate.Put(Orange(false), 0, 1);
        plate.Put(Orange(false), 2, 2);

        plate.Solve();

        plate.Check(3);
    }
    catch (const std::string &error)
    {
        std::cerr << error << ",please start over again." << std::endl;
        return -1;
    }
    return 0;
}