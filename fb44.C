// Pb:
// ---
// 
// calculate minimum h-index for a sorted integer array
// (see http://en.wikipedia.org/wiki/H-index)
// 
// Sol:
// ---
// 
// Using Binary search you should look for the first V[i] that is lower than i+1.
// Assume the array with indices 0..n is sorted with the greatest number on the left.
// Then look in the middle and if V[i] < i+1 then memoize this as a minimum found and
// look in the left side of the rest of array, otherwise don't memoize and look in
// the right side until you will get to array of length 1. Then the result is memoized-1.
//

#include <vector>
#include <iostream>

using std::vector;

namespace
{
  size_t getHIndex(const vector<size_t>& v)
  {
    size_t l = 0, r = v.size()-1;

    while(l < r)
    {
      size_t mid = l + (r-l)/2;

      if(v[mid] >= mid+1)
      {
        l = mid+1;
      }
      else
      {
        r = mid-1;
      }
    }

    return l;
  }
}

int main(int argc, char* argv[])
{
  //vector<size_t> v = {10, 8, 5, 4, 3};  
  vector<size_t> v = {25, 8, 5, 3, 3};

  std::cerr << "H-index = " << getHIndex(v) << std::endl;
  return 0;
}

