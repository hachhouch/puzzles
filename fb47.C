// Pb:
// ---
// 
// A 2D array filled with integer, define a flow from one point to its
// neighbor only if the value of current point is not less than its
// neighbor's value. Consider up edge and left edge as east coast, bottom
// edge and right edge as west coast, find all position that it can flow
// to east coast and west cost both.
// 
// Sol:
// ----
//

#include <vector>
#include <utility>
#include <queue>
#include <iostream>

using std::queue;
using std::vector;
using std::pair;
using std::make_pair;

namespace
{
  using Matrix = vector<vector<int>>;
  using Point = pair<int, int>;
  using Points = vector<Point>;
  using Queue = queue<Point>;

  class Base
  {

  };

  class FlowScanner : public Base
  {
    public:

      FlowScanner(const Matrix& m);
      void findAll(Points& pointList);

    private:

      size_t computeIndex(int i, int j);
      bool isValidMove(const Point& p1, const Point& p2) const;
      void bfs(int i, int j, vector<bool>& flow);

      const Matrix& m_;

      size_t rowCount_;
      size_t colCount_;

      vector<bool> visited_;
  };

  FlowScanner::FlowScanner(const Matrix& m) : m_(m)
  {
    if(m_.empty())
    {
      return;
    }

    rowCount_ = m.size();
    colCount_ = m[0].size();

    visited_.resize(rowCount_*colCount_);
  }

  size_t FlowScanner::computeIndex(int i, int j)
  {
    return (i*rowCount_) + j;
  }

  bool FlowScanner::isValidMove(const Point& p1, const Point& p2) const
  {
    return p1.first + p2.first >= 0 &&
           p1.first + p2.first < rowCount_ &&
           p1.second + p2.second >= 0 &&
           p1.second + p2.second < colCount_ &&
           m_[p1.first][p1.second] <= m_[p1.first+p2.first][p1.second + p2.second];
  }

  void FlowScanner::bfs(int i, int j, vector<bool>& flow)
  {
    std::cerr << "Scanning from " << i << "," << j << std::endl;

    static Point neighbours[] = {
      {-1, 0},
      {1, 0},
      {0, -1},
      {0, 1}
    };

    Queue q;
    size_t index = computeIndex(i, j);
    q.push(make_pair(i, j));
    visited_[index] = true;

    while(!q.empty())
    {
      Point p = q.front();
      q.pop();

      for(size_t i = 0; i < 4; ++i)
      {
        if(isValidMove(p, neighbours[i]))
        {
          Point child = make_pair(p.first + neighbours[i].first, p.second + neighbours[i].second);
          size_t index = computeIndex(child.first, child.second);

          if(!visited_[index])
          {
            visited_[index] = true;
            q.push(child);
            flow[index] = true;
            std::cerr << "Setting flow " << child.first << "," << child.second << " to true." << std::endl;
          }
        }
      }
    }
    std::cerr << "DONE Scanning from " << i << "," << j << std::endl;
  }

  void FlowScanner::findAll(Points& pointList)
  {
    if(m_.empty())
    {
      return;
    }

    vector<bool> eastFlow(rowCount_*colCount_);
    vector<bool> westFlow(rowCount_*colCount_);

    // Start reverse BFS from east (up && left)

    std::cerr << " scanning east" << std::endl;

    for(size_t i = 0; i < rowCount_; ++i)
    {
      size_t index = computeIndex(i, 0);

      if(!visited_[index])
      {
        bfs(i, 0, eastFlow); 
      }
    }

    for(size_t j = 0; j < colCount_; ++j)
    {
      size_t index = computeIndex(0, j);

      if(!visited_[index])
      {
        bfs(0, j, eastFlow); 
      }
    }

    std::cerr << " scanning west" << std::endl;
    visited_.assign(visited_.size(), false);

    // Same for west (down && right)
    for(size_t i = 0; i < rowCount_; ++i)
    {
      size_t index = computeIndex(i, colCount_-1);

      if(!visited_[index])
      {
        bfs(i, colCount_-1, westFlow); 
      }
    }

    for(size_t j = 0; j < colCount_; ++j)
    {
      size_t index = computeIndex(rowCount_-1, j);

      if(!visited_[index])
      {
        bfs(rowCount_-1, j, westFlow); 
      }
    }

    for(size_t i = 1; i < rowCount_-1; ++i)
    {
      for(size_t j = 1; j < colCount_-1; ++j)
      {
        size_t index = computeIndex(i, j);

        if(westFlow[index] && eastFlow[index])
        {
          pointList.push_back(make_pair(i, j));
        }
      }
    }
  }
}

int main(int argc, char* argv[])
{
  Matrix m = {
    {1, 2, 3, 4},
    {5, 6, 17, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };

  FlowScanner s(m);
  Points l;
  s.findAll(l);

  std::for_each(l.begin(), l.end(), [] (const Point& p) { std::cerr << p.first << "," << p.second << std::endl;});
  return 0;
}

