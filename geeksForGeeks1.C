// Pb:
// ---
// 
// Find the longest path in a matrix with given constraints
// 
// Given a n*n matrix where numbers all numbers are distinct and are
// distributed from range 1 to n2, find the maximum length path 
// (starting from any cell) such that all cells along the path are
// increasing order with a difference of 1.
// 
// We can move in 4 directions from a given cell (i, j), i.e., we can
// move to (i+1, j) or (i, j+1) or (i-1, j) or (i, j-1) with the 
// condition that the adjacen
// 
// Example:
// 
// Input:  mat[][] = {{1, 2, 9}
//                    {5, 3, 8}
//                    {4, 6, 7}}
// Output: 4
// The longest path is 6-7-8-9. 
// 
// Sol:
// ----
// 
// DP with memoisation
// 

#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;
using std::pair;

namespace
{
  using Matrix = vector<vector<int>>;

  struct Solution
  {
    bool                 valid_;
    size_t               len_;
    pair<size_t, size_t> pos_;

    Solution() : valid_(false), len_(0) {}
  };

  using DP = vector<vector<Solution>>;

  using Sequence = vector<pair<size_t, size_t>>;

  void computeLongestSeqFrom(const Matrix& m, size_t n, size_t i, size_t j, DP& dp)
  {
    vector<pair<int,int>> direction = {
      {-1, 0},
      {1, 0},
      {0, 1},
      {0, -1}
    };

    size_t max = 0;
    std::pair<size_t, size_t> p;

    for(const auto& p : direction)
    {
      int x = i + p.first;
      int y = j + p.second;

      if(x >= 0 && x < n && y >= 0 && y < n && m[i][j] < m[x][y])
      {
        if(!dp[x][y].valid_)
        {
          computeLongestSeqFrom(m, n, x, y, dp);
        }

        if(dp[x][y].len_ + 1 > max)
        {
          max = dp[x][y].len_ + 1;
          p.x = x;
          p.y = y;
        }
      }
    }

    Solution sol{true, max, p};
    dp[i][j] = sol;
  }

  Solution getLongestSeq(const Matrix& m)
  {
    const size_t n = m.size();
    DP dp(n);

    for(auto& i : dp)
    {
      i.resize(n);
    }

    Solution max;

    for(size_t i = 0; i < n; ++i)
    {
      for(size_t j = 0; j < n; ++j)
      {
        computeLongestSeqFrom(m, n, i, j, dp);

        if(dp[i][j].len_ > max.len_)
        {
          max = dp[i][j];
        }
      }
    }

    Sequence seq;
    seq.push_back(max.pos_);
    bool done = false;

    while(!done)
    {
      if(dp[max.pos_.first][max.pos_.second].len_ > 0)
      {
        seq.push_back(dp[max.pos_.first][max.pos_.second].pos_);
        max = max.pos_;
      }
      else
      {
        done = true;
      }
    }

    return seq;
  }
}

int main(int argc, char* argv)
{
  Matrix m = {
    {1, 2, 9},
    {5, 3, 8},
    {4, 6, 7}
  };

  Sequence seq = getLongestSeq(m);

  std::cerr << "Longest sequence = ";
  std::copy(seq.begin(), seq.end(), std::ostream_iterator<int>(std::cout, ","));
  std::cerr << std::endl;

  return 0;
}

