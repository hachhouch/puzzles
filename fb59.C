// Input: A string equation that contains numbers, '+' and '*' 
// Output: Result as int. 
// 
// For example: 
// Input: 3*5+8 (as String) 
// Output: 23 (as int)

#include <string>
#include <stack>
#include <iostream>

using std::string;
using std::stack;

namespace
{
  int evaluate(const string& str)
  {
    const size_t count = str.size();

    stack<int> s;

    string number;
    int tmp = -1;

    size_t i = 0;

    while(i < count)
    {
      while(i < count && str[i] >= '0' && str[i] <= '9')
      {
        number += str[i];
        ++i;
      }

      if(tmp != -1)
      {
        tmp *= atoi(number.c_str());
        s.push(tmp);
        tmp = -1;
      }
      else
      {
        s.push(atoi(number.c_str()));
      }

      number.clear();

      if(i < count)
      {
        char op = str[i];
        ++i;

        if(op == '*')
        {
          tmp = s.top();
          s.pop();
        }
      }
    }

    int sum = 0;

    while(!s.empty())
    {
      int n = s.top();
      s.pop();
      sum += n;
    }

    return sum;
  }
}

int main(int argc, char* argv[])
{
  string str("3+5*8+7*7+8");
  std::cerr << evaluate(str) << std::endl;
  return 0;
}

