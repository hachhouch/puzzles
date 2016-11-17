// Given an array of positive, unique, increasingly sorted numbers A, 
// e.g. A = [1, 2, 3, 5, 6, 8, 9, 11, 12, 13]. Given a positive value 
// K, e.g. K = 3. Output all pairs in A that differ exactly by K. 
// 
// e.g. 
// 
// 2, 5 
// 3, 6 
// 5, 8 
// 6, 9 
// 8, 11 
// 9, 12 
// 
// what is the runtime for your code?
//

#include <vector>
#include <utility>
#include <iostream>

using std::vector;
using std::pair;

namespace
{
  using Pair = pair<int, int>;

  void getPairs(const vector<int>& a, size_t k, vector<Pair>& ret)
  {
    if(a.size() < 2)
    {
      return;
    }

    const size_t count = a.size();
    size_t i = 0, j = 1;

    while(j < count)
    {
      while(j < count && a[j] < a[i]+k)
      {
        ++j;
      }

      if(a[i]+k == a[j])
      {
        ret.push_back(std::make_pair(a[i], a[j]));
      }

      ++i;
    }
  }
}

int main(int argc, char*[])
{
  vector<int> a{1, 2, 3, 5, 6, 8, 9, 11, 12, 13};

  vector<Pair> pairs;
  getPairs(a, 3, pairs);

  std::for_each(
    pairs.begin(),
    pairs.end(),
    [](const Pair& p){ std::cerr << p.first << "," << p.second << std::endl; }
  );

  return 0;
}

