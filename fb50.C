// Pb:
// ---
//
// N queen problem.o 
// In NXN chess board, you have to arrange N queens such that they do not interfere each other.
// Following is how you define interference of queens. 
// 1. Two queens cannot be on the same diagonal 
// 2. Two queens cannot be in same horizontal or vertical line 
// 3. Queen can jump like a knight. So, two queens cannot be at a position where they can jump
//    two and half steps like a knight and reach the other queen. 
// 
// You should return the possible ways to arrange N queens on a chess board. 
// 
// This was a tech screen, but since I was local, they called me in their office rather than phone interview. 
// 
// Hint: Don't try too hard, the best solution is n!
// 
// Sol:
// ----
//
// backtracking

#include <cstdlib>
#include <iostream>
#include <vector>

using std::vector;

namespace
{
  using Solution = vector<int>;

  bool sameCol(int k, int i, const Solution& s)
  {
    return s[k] == s[i];
  }

  bool sameDiag(int k, int i, const Solution& s)
  {
    return std::abs(k - i) == std::abs(s[k] - s[i]);
  }

  bool knightReachable(int k, int i, const Solution& s)
  {
    return ((i-k == 2) && std::abs(s[k] - s[i]) == 1) ||
           ((i-k == 1) && std::abs(s[k] - s[i]) == 2);
  }

  void resolve(const size_t i, Solution& s)
  {
    const size_t n = s.size();

    for(size_t j = 0; j < n; ++j)
    {
      s[i] = j;

      bool illegal{false};

      for(size_t k = 0; k < i; ++k)
      {
        if(sameCol(k, i, s) || sameDiag(k, i, s) || knightReachable(k, i, s))
        {
          illegal = true;
          break;
        }
      }

      if(illegal)
      {
        continue;
      }

      if(i < n - 1)
      {
        resolve(i+1, s);
      }
      else
      {
        std::cerr << "Found solution: " << std::endl;

        for(size_t k = 0; k < n; ++k)
        {
          std::cerr << k << "," << s[k] << std::endl;
        }
      }
    }
  }
}

int main(int argc, char* argv[])
{
  const size_t N = 12;
  Solution s(N);
  resolve(0, s);
  return 0;
}

