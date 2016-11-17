// Sol:
// ----
// 
// Given a 4 X 4 game slot that has random alphabets in all the slots 
// Write a function that takes the keyboard and the word as input and returns
// true if the word can be formed 
// False otherwise. 
// 
// A word can be formed on the board by connecting alphabets adjacent to each
// other (horizontal, vertical and diagonally) 
// 
// Same alphabet should not be reused.
// 
// Sol:
// ----
// 
// Recursive DFS with memoisation
// 

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <array>

#include <iostream>

using std::string;
using std::unordered_map;
using std::vector;
using std::pair;
using std::array;

namespace
{
  //using Game = char [4][4];
  using Game = array<array<char, 4>, 4>;

  struct Cell
  {
    bool                        visited_;
    unordered_map<string, bool> suffixes_;

    Cell() : visited_{false} {}
  };

  using Move = pair<int, int>;

  using Cache = vector<vector<Cell>>;

  bool isValidMove(
    const Game&  game,
    size_t       row,
    size_t       col,
    const Move&  m,
    char         c,
    const Cache& cache
  )
  {
    int x = (int)row + m.first;
    int y = (int)col + m.second;

    return x >= 0 && x < game.size() &&
           y >= 0 && y < game[0].size() &&
           !cache[x][y].visited_ &&
           game[x][y] == c;
  }

  bool dfs(
    const Game&   game,
    size_t        row,
    size_t        col,
    const string& str,
    size_t        start,
    Cache&        cache
  )
  {
    if(start == str.size()-1)
    {
      return true;
    }

    static Move moves[] = {
      {-1, 0},  // Left
      {1,  0},  // Right
      {0,  1},  // Up
      {0, -1},  // Down
      {-1, 1},  // Top-Left
      {1,  1},  // Top-Right
      {-1, -1}, // Bottom-Left
      {1,  -1}  // Bottom-Rght
    };

    bool outcome = false;
    cache[row][col].visited_ = true;

    for(const auto& m : moves)
    {
      if(isValidMove(game, row, col, m, str[start+1], cache))
      {
        unordered_map<string, bool>::const_iterator pos = 
          cache[row+m.first][col+m.second].suffixes_.find(str.substr(start+1));

        if(pos == cache[row+m.first][col+m.second].suffixes_.end())
        {
           outcome = dfs(game, row + m.first, col + m.second, str, start+1, cache);
        }
        else
        {
          outcome = pos->second;
        }

        if(outcome)
        {
          break;
        }
      }
    }

    cache[row][col].suffixes_[str.substr(start)] = outcome;
    cache[row][col].visited_ = false;
    return outcome;
  }

  bool canBeFormed(const Game& game, const string& str)
  {
    if(str.empty())
    {
      return true;
    }

    const size_t m = game.size();
    const size_t n = game[0].size();

    Cache cache(m);

    for(auto& r : cache)
    {
      r.resize(n);
    }

    for(size_t i = 0; i < m; ++i)
    {
      for(size_t j = 0; j < n; ++j)
      {
        if(game[i][j] == str[0] && dfs(game, i, j, str, 0, cache))
        {
          return true;
        }
      }
    }

    return false;
  }
}

int main(int argc, char* argv[])
{
  Game g = {{
    {{'A', 'B', 'Y', 'W'}},
    {{'E', 'F', 'G', 'T'}},
    {{'I', 'J', 'K', 'I'}},
    {{'M', 'N', 'O', 'R'}} 
  }};

  string str{"MINORITY"};

  std::cerr << str << " -> " << std::boolalpha << canBeFormed(g, str) << std::endl;
  return 0;
}

