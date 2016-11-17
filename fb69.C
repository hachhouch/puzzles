// Pb:
// ---
// 
// Given an array of ages (integers) sorted lowest to highest, output the
// number of occurrences for each age. 
// 
// For instance: 
// [8,8,8,9,9,11,15,16,16,16] 
// 
// should output something like: 
// 8: 3 
// 9: 2 
// 11: 1 
// 15: 1 
// 16: 3 
// 
// This should be done in less than O(n).
// 
// Sol:
// ----
// 
// m log n, where m is number of unique ages and n is number of elements.
// Since m is practically a constant (unfortunately our age is bound), the
// time complexity is log n. If you look at this very simple and very short
// code, this is nothing else than binary search for the border point between
// two consecutive ages.
// 

#include <vector>
#include <utility>
#include <iostream>

using std::vector;
using std::pair;
using std::make_pair;

namespace
{
  using Ages = vector<int>;
  using Result = vector<pair<int, size_t>>;

  size_t findFirst(const Ages& a, int v)
  {
    std::cerr << "FindFirst: " << v << std::endl;

    size_t i = 1;
    size_t j = a.size();

    while(i <= j)
    {
      size_t mid = i + (j-i)/2;

      std::cerr << "mid = " << mid << std::endl;
      std::cerr << "a[mid] = " << a[mid-1] << std::endl;

      if(a[mid-1] >= v)
      {
        j = mid-1;
        std::cerr << "j = " << j << std::endl;
      }
      else
      {
        i = mid+1;
        std::cerr << "i = " << i << std::endl;
      }
    }

    std::cerr << "Returned " << j << std::endl;

    return i;
  }

  size_t findLast(const Ages& a, int v)
  {
    std::cerr << "FindLast: " << v << std::endl;

    size_t i = 1;
    size_t j = a.size();

    while(i <= j)
    {
      size_t mid = i + (j-i)/2;

      if(a[mid-1] <= v)
      {
        i = mid+1;
      }
      else
      {
        j = mid-1;
      }
    }

    std::cerr << "Returned " << j << std::endl;
    return j;
  }

  Result getCount(const Ages& a)
  {
    Result r;

    int min = a[0];
    int max = a[a.size()-1];

    for(int i = min; i <= max; ++i)
    {
      size_t first = findFirst(a, i);
      size_t last = findLast(a, i);

      r.push_back(make_pair(i, last-first+1));
    }

    return r;
  }
}

int main(int argc, char* argv[])
{
  std::cerr << "\033[31m" << "{8,8,8,9,9,11,15,16,16,16}" << "\033[0m" << std::endl;
  Ages a = {8,8,8,9,9,11,15,16,16,16};
  Result r = getCount(a);


  for(const auto& p : r)
  {
    if(p.second > 0)
    {
      std::cerr << p.first << ": " << p.second << std::endl;
    }
  }

  return 0;
}


