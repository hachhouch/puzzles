// Pb:
// ---
//
// paint a list of N houses and M colors, each combination has cost, minimize the
// total cost without color in row.
//
// Sol:
// ----
//
// Dynamic programming
//
// DP[i][j] : best cost for coloring up to house i, and last color is j;

#include <vector>
#include <iostream>
#include <utility>

using std::vector;
using std::make_pair;
using std::pair;

namespace
{
  using Cost = vector<vector<int>>;
  using DP = vector<vector<pair<size_t, size_t>>>;

  void computeOpt(const Cost& c, size_t house, size_t color, DP& dp)
  {
    const size_t colCount = c[0].size();
    size_t min = std::numeric_limits<size_t>::max();
    size_t colMin = 0;

    if(house > 0)
    {
      for(size_t i = 0; i < colCount; ++i)
      {
        if(i != color && (c[house][i]+dp[house-1][i].first < min))
        {
          computeOpt(c, house-1, i, dp);
          min = c[house][i]+dp[house-1][i].first;
          colMin = i;
        }
      }
    }
    else
    {
      for(size_t i = 0; i < colCount; ++i)
      {
        if(i != color && c[house][i] < min)
        {
          min = c[house][i];
          colMin = i;
        }
      }
    }

    dp[house][color] = make_pair(min, colMin);
  }

  size_t getOptimalSolution(const Cost& c)
  {
    const size_t houseCount = c.size();
    const size_t colCount = c[0].size();

    DP dp{houseCount};

    for(auto& r : dp)
    {
      r.resize(colCount+1);
    }

    computeOpt(c, houseCount-1, colCount+1, dp);
    size_t min = dp[houseCount-1][colCount+1].first;
    size_t colMin = dp[houseCount-1][colCount+1].second;

    std::cerr << houseCount-1 << " => " << colMin << std::endl;

    for(size_t j = houseCount-1; j > 0; --j)
    {
      std::cerr << j-1 << " => " << dp[j-1][colMin].second << std::endl;
      colMin = dp[j-1][colMin].second;
    }

    return min;
  }
}

int main(int argc, char* argv[])
{
  Cost cost = {
    { 7, 5, 10 },
    { 3, 6, 1 },
    { 8, 7, 4 },
    { 6, 2, 9 },
    { 1, 4, 7 },
    { 2, 3, 6 }
  };

  std::cerr << "Opt cost is: " << std::endl << getOptimalSolution(cost) << std::endl;
}

