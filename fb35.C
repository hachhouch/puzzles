// Pb:
// ---
// 
// On a given array with N numbers, find subset of size M (exactly M elements) that
// equal to SUM.
// 
// Sol:
// ----
// 
// DP: dp[i][j][k] : found subset of a[0]...a[i] with j elements that sums to k.
//                   0 < i < n-1
//                   1 < j < i+1
//                   N < k < P ( N: sum neg *** P: pos sum)
//
// Dp: dp[0][1][a[0]] -> true
//     dp[0][1][....] -> false
//     ...
//     dp[i][j][k]    -> dp[i-1][j][k] or dp[i-1][j-1][k-a[i]]

#include <vector>
#include <unordered_map>
#include <iostream>

using std::vector;
using std::unordered_map;

namespace
{
  using DP = vector<vector<unordered_map<int, bool>>>;

  DP dp;

  void findSub(const vector<int>& a, size_t i, size_t size, int sum)
  {
    if(size == 1)
    {
      for(size_t j = 0; j <= i; ++j)
      {
        if(a[j] == sum)
        {
          for(size_t k = j; k <= i; ++k)
          {
            dp[k][size][sum] = true;
          }

          return;
        }
      }

      dp[i][size][sum] = false;
      return;
    }
    else if(size > i+1) 
    {
      dp[i][size][sum] = false;
      return;
    }

    findSub(a, i-1, size, sum);
    findSub(a, i-1, size-1, sum-a[i]);

    dp[i][size][sum] = dp[i-1][size][sum] || dp[i-1][size-1][sum-a[i]];
  }
}

int main(int argc, char* argv[])
{
  vector<int> a = {-3, 5, 0, 23, 9};

  const size_t size = 3;
  const int sum = 6;

  dp.resize(a.size());

  for(auto& r : dp)
  {
    r.resize(sum);
  }

  findSub(a, a.size()-1, size, sum);
 
  if(dp[a.size()-1][size][sum])
  {
    std::cerr << "Found subset: ";

    size_t k = size;
    size_t i = a.size()-1;
    int j = sum;

    while( k > 0)
    {
      if(i == 0 && dp[i][k][j])
      {
        std::cerr << a[i] << " ";
        --k;
        break;
      }

      if(dp[i][k][j] != dp[i-1][k][j])
      {
        std::cerr << a[i] << " ";
        --k;
        j-= a[i];
      }

      --i;
    }

    std::cerr << std::endl;
  }
  else
  {
    std::cerr << "No subset" << std::endl;
    //std::copy(sub.begin(), sub.end(), std::ostream_iterator<int>(std::cerr, ","));
  }

  return 0;
}

