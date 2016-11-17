// Pb (3-SUM):
// -----------
// 
// Given an array of integers, return true if there're 3 numbers adding up to zero 
// (repetitions are allowed) 
// {10, -2, -1, 3} -> true 
// {10, -2, 1} -> true -2 + 1 +1 =0
// 
// Sol 1:
// ------
// 
// 3SUM can be solved in O(n^2) time on average by inserting each number into a
// hash table, and then for each index i and j, checking whether the hash table
// contains the integer − (S[i] + S[j]).
// 
// Sol 2:
// ------
// 
// Alternatively, the algorithm below first sorts the input array and then tests
// all possible pairs in a careful order that avoids the need to binary search
// for the pairs in the sorted list, achieving worst-case O(n^2) time

#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using std::vector;
using std::unordered_set;

namespace
{
  using Numbers = vector<int>;

  bool sum3(const Numbers& a)
  {
    const size_t count = a.size();

    unordered_set<int> h;

    for(size_t i = 0; i < count; ++i)
    {
      h.insert(-a[i]);
    }

    for(size_t i = 0; i < count; ++i)
    {
      for(size_t j = 0; j < count; ++j)
      {
        if(h.find(a[i] + a[j]) != h.end())
        {
          return true;
        }
      }
    }

    return false;
  }

  bool sum3_2(Numbers a)
  {
    std::sort(a.begin(), a.end());
    const size_t count = a.size();

    for(size_t i = 0; i < count; ++i)
    {
      size_t start = 0;
      size_t end = count-1;

      while(start <= end)
      {
        int sum = a[i] + a[start] + a[end];

        if(sum == 0)
        {
          return true;
        }
        else if(sum > 0)
        {
          --end;
        }
        else
        {
          ++start;
        }
      }
    }

    return false;
  }
}

int main(int argc, char* argv[])
{
  //Numbers a = { 10, -2, -1, 3};
  Numbers a = {10, -2, 1};
  std::cerr << std::boolalpha << sum3_2(a) << std::endl;
  return 0;
}

