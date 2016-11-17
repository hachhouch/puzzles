// Pb:
// ---
// 
// A robot has to move in a grid which is in the form of a matrix. It can go to 
// 1.) A(i,j)--> A(i+j,j) (Down) 
// 2.) A(i,j)--> A(i,i+j) (Right) 
// 
// Given it starts at (1,1) and it has to go to A(m,n), find the minimum number
// of STEPS it has to take to get to (m,n) and write public static int minSteps(int m,int n) 
// 
// For instance to go from (1,1) to m=3 and n=2 it has to take (1, 1) -> (1, 2) -> (3, 2) 
// i.e. 2 steps
// 
// Sol:
// ----
// 
// DP

#include <vector>
#include <string>
#include <utility>
#include <iostream>

using std::vector;
using std::string;
using std::pair;
using std::make_pair;

namespace
{
  using Cell = pair<bool, int>;
  using DP = vector<vector<Cell>>;

  void compute(DP& dp, size_t i, size_t j, int m, int n)
  {
    std::cerr << "Processing " << i << "," << j << std::endl;

    if(i == m && j == n)
    {
      std::cerr << "Found" << std::endl;
      dp[i][j].second = 0;
    }
    else
    {
      if(i+j <= m && dp[i+j][j].first == false)
      {
        compute(dp, i+j, j, m, n);

        if(dp[i+j][j].second > -1)
        {
          dp[i][j].second = dp[i+j][j].second + 1;
        }
      }

      if(i+j <= n && dp[i][i+j].first == false)
      {
        compute(dp, i, i+j, m, n);

        if(dp[i][i+j].second > -1)
        {
          if(dp[i][j].second == -1)
          {
            dp[i][j].second = dp[i][i+j].second+1;
          }
          else
          {
            dp[i][j].second = std::min(dp[i][j].second, dp[i][i+j].second+1);
          }
        }
      }
    }

    dp[i][j].first = true;
  }

  // Starts at (0, 0)
  int minSteps(int m, int n)
  {
    DP dp(m+1);

    for(auto& r : dp)
    {
      r.resize(n+1, make_pair(false, -1));
    }

    compute(dp, 1, 1, m, n);
    return dp[1][1].second;
  }
}

int main(int argc, char* argv[])
{
  std::cerr << "Min steps: " << minSteps(3, 2) << std::endl;
  return 0;
}

