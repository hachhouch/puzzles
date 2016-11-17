// Pb:
// ---
//
// You are given a 2d rectangular array of positive integers representing the height
// map of a continent. The "Pacific ocean" touches the left and top edges of the array
// and the "Atlantic ocean" touches the right and bottom edges. 
// - Find the "continental divide". That is, the list of grid points where water can
// flow either to the Pacific or the Atlantic. 
// Water can only flow from a cell to another one with height equal or lower. 
// 
// Example: 
// 
// Pacific ~ ~ ~ ~ ~ |__ 
// ~ 1 2 2 3 (5) ~ 
// ~ 3 2 3 (4)(4) ~ 
// ~ 2 4 (5) 3 1 ~ 
// ~ (6)(7) 1 4 5 ~ 
// __ (5) 1 1 2 4 ~ 
// |~ ~ ~ ~ ~ Atlantic 
// 
// The answer would be the list containing the coordinates of all circled cells: 
// [(4,0), (3,1), (4,1), (2,2), (0,3), (1,3), (0,4)]
//
// Sol:
// ----
//
// DFS
//

#include <vector>
#include <utility>
#include <iostream>

using std::vector;
using std::pair;
using std::make_pair;

namespace
{
  using Map = vector<vector<size_t>>;
  using Position = pair<size_t, size_t>;
  using Solution = vector<Position>;

  struct Cell
  {
    bool visited_;
    bool flowToPacific_;
    bool flowToAtlantic_;

    Cell() : visited_{false}, flowToPacific_{false}, flowToAtlantic_{false} {}
  };

  void visit(const Map& m, vector<vector<Cell>>& cells, size_t i, size_t j)
  {
    std::cerr << "Visiting " << i << "," << j << std::endl;

    const size_t rowCount = m.size();
    const size_t colCount = m[0].size();

    cells[i][j].visited_ = true;

    // Up
    if(i > 0 && m[i-1][j] <= m[i][j])
    {
      if(!cells[i-1][j].visited_)
      {
        visit(m, cells, i-1, j);
      }

      cells[i][j].flowToPacific_ |= cells[i-1][j].flowToPacific_;
      cells[i][j].flowToAtlantic_ |= cells[i-1][j].flowToAtlantic_;
    }

    // Down
    if(i < rowCount-1 && m[i+1][j] <= m[i][j])
    {
      if(!cells[i+1][j].visited_)
      {
        visit(m, cells, i+1, j);
      }

      cells[i][j].flowToPacific_ |= cells[i+1][j].flowToPacific_;
      cells[i][j].flowToAtlantic_ |= cells[i+1][j].flowToAtlantic_;
    }

    // Left
    if(j > 0 && m[i][j-1] <= m[i][j])
    {
      if(!cells[i][j-1].visited_)
      {
        visit(m, cells, i, j-1);
      }

      cells[i][j].flowToPacific_ |= cells[i][j-1].flowToPacific_;
      cells[i][j].flowToAtlantic_ |= cells[i][j-1].flowToAtlantic_;
    }

    // Right
    if(j < colCount-1 && m[i][j+1] <= m[i][j])
    {
      if(!cells[i][j+1].visited_)
      {
        visit(m, cells, i, j+1);
      }

      cells[i][j].flowToPacific_ |= cells[i][j+1].flowToPacific_;
      cells[i][j].flowToAtlantic_ |= cells[i][j+1].flowToAtlantic_;
    }
  }

  Solution getContDevide(const Map& m)
  {
    const size_t rowCount = m.size();
    const size_t colCount = m[0].size();

    vector<vector<Cell>> cells(rowCount);

    for(auto& c : cells)
    {
      c.resize(colCount);
    }

    // Mark the edges.

    for(size_t i = 0; i < rowCount; ++i)
    {
      cells[i][0].flowToPacific_ = true;
      cells[i][colCount-1].flowToAtlantic_ = true;
    }

    for(size_t j = 0; j < colCount; ++j)
    {
      cells[0][j].flowToPacific_ = true;
      cells[rowCount-1][j].flowToAtlantic_ = true;
    }
    
    // Visit each unvisited cell.

    for(size_t i = 0; i < rowCount; ++i)
    {
      for(size_t j = 0; j < colCount; ++j)
      {
        if(!cells[i][j].visited_)
        {
          visit(m, cells, i, j);
        }
      }
    }

    Solution s;

    for(size_t i = 0; i < rowCount; ++i)
    {
      for(size_t j = 0; j < colCount; ++j)
      {
        if(cells[i][j].flowToPacific_ && cells[i][j].flowToAtlantic_)
        {
          s.push_back(make_pair(i, j));
        }
      }
    }

    return s;
  }
}

int main(int argc, char* argv[])
{
  Map m = {
    {1, 2, 2, 3, 5},
    {3, 2, 3, 4, 4},
    {2, 4, 5, 3, 1},
    {6, 7, 1, 4, 5},
    {5, 1, 1, 2, 4}
  };

  Solution sol = getContDevide(m);

  std::for_each(
    sol.begin(),
    sol.end(),
    [] (const Position& p) {std::cerr << p.first << "," << p.second << std::endl;}
  );

  return 0;
}

