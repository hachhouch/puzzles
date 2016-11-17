// Pb:
// ---
// 
// You're given an array of integers(eg [3,4,7,1,2,9,8]) Find the 
// index of values that satisfy A+B = C + D, where A,B,C & D are
// integers values in the array. 
// 
// Eg: Given [3,4,7,1,2,9,8] array 
// The following 
// 3+7 = 1+ 9 satisfies A+B=C+D 
// so print (0,2,3,5)
// 
// Sol:
// ----
// 
// I use hash map to record the sum of two pair and find two pairs
// which has the same sum. Time is O(n^2)
// 

#include <vector>
#include <array>
#include <unordered_map>
#include <iostream>
#include <utility>

using std::vector;
using std::array;
using std::unordered_map;
using std::pair;
using std::make_pair;

namespace
{
  using Array = vector<int>;
  using Result = array<size_t, 4>;
  using Hash = unordered_map<int, pair<size_t, size_t>>;;

  Result findSolution(const Array&  a)
  {
    const size_t count = a.size();
 
    Hash h;

    for(size_t i = 0; i < count; ++i)
    {
      for(size_t j = i+1; j < count; ++j)
      {
        Hash::const_iterator pos = h.find(a[i]+a[j]);

        if(pos != h.end())
        {
          Result r{i, j, pos->second.first, pos->second.second};
          return r;
        }
        else
        {
          h[a[i]+a[j]] = make_pair(i, j);
        }
      }
    }

    return Result();
  }
}

int main(int argc, char* argv[])
{
  Array a = {3,4,7,1,2,9,8};
  Result r = findSolution(a);

  std::copy(r.begin(), r.end(), std::ostream_iterator<size_t>(std::cerr, " "));
  
  return 0;
}

