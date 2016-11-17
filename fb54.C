// Pb:
// ---
// 
// Implement stairs(N) that (collect the solutions in a list) prints all the ways
// to climb up a N-step-stairs where one can either take a single step or double step. 
// We'll use 1 to represent a single step, and 2 to represent a double step. 
// 
// stairs(3) 
// 111 
// 12 
// 21
// 
// Sol:
// ----
// 
// DP
//

#include <string>
#include <vector>
#include <iostream>

using std::vector;
using std::string;

namespace
{
  using DP = vector<vector<string>>;

  void computeSteps(DP& dp, size_t i)
  {
    if(!dp[i].empty())
    {
      return;
    }

    computeSteps(dp, i-1);

    for(const auto& v : dp[i-1])
    {
      dp[i].push_back("1" + v);
    }

    if(i > 1)
    {
      computeSteps(dp, i-2);

      for(const auto& v : dp[i-2])
      {
        dp[i].push_back("2" + v);
      }
    }
  }

  void printSteps(size_t n)
  {
    DP dp(n+1);
    dp[0].push_back("");

    computeSteps(dp, n);

    for(const auto& s : dp[n])
    {
      std::cerr << s << std::endl;
    }
  }
}

int main(int argc, char* argv[])
{
  const size_t N = 4;
  printSteps(N);

  return 0;
}

