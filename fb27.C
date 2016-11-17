// Pb:
// 
// Given: sorted array of integers 
// Return: sorted array of squares of those integers 
// Ex: [1,3,5] -> [1,9,25] 
// 
// Integers can be negative.
// 
// Sol:
// 
// It can be done in O(n) time. Split your array into two logical parts.
// Positive and negative. Then apply square to each element in both arrays.
// Then merge the arrays( merging can be done in O(n) ), but merge the 
// array with previously negative integers in reverse order, since its 
// values will be reversed.
//

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using std::vector;

namespace
{
  vector<int> squareIt(const vector<int>& a)
  {
    const size_t count = a.size();
    size_t p = 0;

    while(p < count && a[p] < 0)
    {
      ++p;
    }

    // 0 -> p-1 : < 0
    // p -> count-1 >= 0

    vector<int> r(count);
    size_t n = p;

    for(size_t i = 0; i < count; ++i)
    {
      if((p >= count) || (n > 0 && std::abs(a[n-1]) < a[p]))
      {
        r[i] = a[n-1]*a[n-1];
        --n;
      }
      else
      {
        r[i] = a[p]*a[p];
        ++p;
      }
    }

    return r;
  }
}

int main(int argc, char* argv[])
{
  vector<int> a = { -10, -6, -4, -2, 1, 3, 5, 8 };
  vector<int> sq = squareIt(a);

  std::copy(sq.begin(), sq.end(), std::ostream_iterator<int>(std::cout, ","));
  std::cerr << std::endl;

  return 0;
}

