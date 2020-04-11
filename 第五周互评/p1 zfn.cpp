/*
数组nums大小为n且包含从0到n的所有整数，但其中有可能会存在一个缺失的整数。
你需要在O(n)的时间内找出那个缺失的整数，如果找到，则输出该数字，如果找不到，则输出-1
输入
9 6 4 2 3 5 7 0 1
输出
8

Compiler:
g++ -std=c++11
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <exception>

using std::vector;
using std::string;
using std::cout;

// Only with exceptions can the automatic variables be freed properly
class format_error : std::exception
{
  const char *error_str;
public:
  format_error(const char *str) : error_str(str) {}
  const char *what() const noexcept { return error_str; }
};

// Convert to an array
vector<int> read_nums(const string &);

// Find the missing number
int find_missing(const vector<int> &);

int main()
{
  // Read one line
  try {
    string nums_str;
    std::getline(std::cin, nums_str);

    vector<int> nums = read_nums(nums_str);

    cout << find_missing(nums);
  }
  catch (const format_error &e)
  {
    std::cerr << "Format error: " << e.what() << ".\n";
  }

  return 0;
}

vector<int> read_nums(const string &nums_str)
{
  std::vector<int> nums;
  std::istringstream nums_buf(nums_str);
  // Now nums_buf behaves just like cin
  while (true)
  {
    int tmp;
    nums_buf >> tmp;
    if (nums_buf.eof())
    {
      nums.push_back(tmp);
      break;
    }
    else if (nums_buf.fail())
    {
      throw format_error("not a number");
    }
    nums.push_back(tmp);
  }
  return nums;
}

int find_missing(const vector<int> &nums)
{
  // One more space for the biggest elememt
  vector<bool> found(nums.size() + 1, false);

  for (const auto &i : nums) // Range-based for
  {
    if (i <= nums.size())
    {
      found[i] = true;
    }
    else
    {
      throw format_error("number too big");
    }
  }

  // Only examine the first n elements
  for (size_t i = 0; i < nums.size(); i++)
  {
    if (!found[i])
    {
      return i;
    }
  }
  return -1;
}
