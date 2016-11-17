// Pb:
// ---
// 
// Given an MxN matrix, with a few hurdles arbitrarily placed, calculate the cost of longest
// possible route from point A to point B within the matrix.
// 
// Sol:
// ----
// 
// The idea is to use Backtracking. We start from the source cell of the matrix, move
// forward in all four allowed directions and recursively checks if they leads to the
// solution or not. If destination is found, we update the value of longest path else
// if none of the above solutions work we return false from our function.
// 

#include <vector>
#include <utility>
#include <iostream>

using std::vector;
using std::pair;
using std::make_pair;

namespace
{
  using Matrix = vector<vector<bool>>;
  using Outcome = pair<bool, size_t>;

  Outcome getLongest(
    const Matrix& m,
    size_t sx,
    size_t sy,
    size_t dx,
    size_t dy,
    vector<vector<bool>>& v
  )
  {
    if(sx == dx && sy == dy)
    {
      return make_pair(true, 0);
    }
 
    const size_t M = m.size();
    const size_t N = m[0].size();

    vector<pair<int, int>> tmp = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    size_t max = 0;

    for(const auto& p : tmp)
    {
      int x = sx + p.first;
      int y = sy + p.second;

      if(x >= 0 && x < N &&
         y >= 0 && y < M &&
         m[y][x] != 0 && !v[y][x])
      {
        v[y][x] = true;
        Outcome o = getLongest(m, x, y, dx, dy, v);

        if(o.first && o.second+1 > max)
        {
          max = o.second + 1;
        }

        v[y][x] = false;
      }
    }

    return max > 0 ? make_pair(true, max) : make_pair(false, (size_t)0);
  } 
}

int main(int argc, char* [])
{
  Matrix m = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  };

  vector<vector<bool>> v(m.size());

  for(size_t i = 0; i < m.size(); ++i)
  {
    v[i].resize(m[i].size());
  }

  size_t sx = 0, sy = 0, dx = 7, dy = 1;

  v[0][0] = true;
  Outcome o = getLongest(m, sx, sy, dx, dy, v);

  if(o.first)
  {
    std::cerr << "Longest path from " << sx << "," << sy << " to "
              << dx << "," << dy <<   " is equal to " << o.second << std::endl;
  }
  else
  {
    std::cerr << "No route from " << sx << "," << sy << " to " << dx << "," << dy << std::endl;
  }

  return 0;
}

