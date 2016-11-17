// Pb:
// ---
// 
// Array of size (n-m) with numbers from 1..n with m of them missing. Find
// one all of the missing numbers in O(log). Array is sorted. 
// 
// Example: 
// n = 8 
// arr = [1,2,4,5,6,8] 
// m=2 
// Result has to be a set {3, 7}.
// 
// Sol:
// ----
// 
// We divide the array into 2 equals parts and foreach subarray - we check
// if the number of elements that are actually in there (meaning the highest
// value minus the lowest value) matches the number of element of that sub
// array. If so (meaning the difference is zero) the function weill return
// from this subarray and do nothing. otherwise, we check if we got array
// that is actually a pair arr[i],arr[i+1] that has a difference bigger than 1.
// if so we add all the numbers from arr[i] to arr[i+1]. 
// the complexity is m*log(n). I'm assuming that m is a constant.

#include <vector>
#include <iostream>

using std::vector;

namespace
{
  using Numbers = vector<size_t>;

  void getMissing(const Numbers& a, size_t i, size_t j, Numbers& m)
  {
    //std::cerr << "getMissing: " << i << " -> " << j << std::endl;

    if(j==i)
    {
      return;
    }

    if(j == i+1)
    {
      if(a[j] > a[i] + 1)
      {
        for(size_t k = a[i]+1; k < a[j]; ++k)
        {
          m.push_back(k);
        }
      }

      return;
    }

    size_t mid = i+((j-i)/2);

    if(a[mid] - a[i] > mid-i)
    {
      getMissing(a, i, mid, m);
    }

    if(a[j] - a[mid] > j-mid)
    {
      getMissing(a, mid, j, m);
    }
  }

  Numbers getMissing(const Numbers& a)
  {
    Numbers m;
    getMissing(a, 0, a.size()-1, m);

    return m;
  }
}

int main(int argc, char* argv[])
{
  Numbers a = {1,2,4,5,6,8};
  Numbers m = getMissing(a);

  for(auto i : m)
  {
    std::cerr << i << " ";
  }

  std::cerr << std::endl;
  return 0;
}

