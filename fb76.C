// Pb:
// ---
// 
// Given an array of integers. 
// 
// Move all non-zero elements to the left of all zero elements.
// 

#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;

namespace
{
  using Numbers = vector<int>;

  void shuffle(Numbers& a)
  {
    const size_t count = a.size();

    if(count <= 1)
    {
      return;
    }

    size_t i = 0, j = count-1;

    while(true)
    {
      while(i < count && a[i] != 0) ++i;

      while(j > 0 && a[j] == 0) --j;

      if(i < j)
      {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
      }
      else
      {
        break;
      }
    }
  }
}

int main(int argc, char* argv[])
{
  Numbers a = {-1, 0, 0, 20, 14, -10, 0};
  shuffle(a);

  std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, ","));

  return 0;
}

