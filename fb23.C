// Pb:
// ---
//
// A museum was represented by a square matrix that was filled with O, G,
// and W where O represented open space G represented guards, and W 
// represented walls. Write a function that accepts the square matrix and 
// returns another square matrix where all of the O's in the matrix are 
// replaced with the number of how many spaces they are away from a guard, 
// without being able to go through any walls.
//
// Sol:
// ----
//
// BFS from guard

#include <vector>
#include <queue>
#include <iostream>

using std::vector;
using std::queue;

namespace
{
  using Matrix = vector<vector<char>>;
  using Distances = vector<vector<size_t>>;
  using Graph = vector<vector<size_t>>;

  void addEdge(Graph& g, size_t count, size_t x1, size_t y1, size_t x2, size_t y2)
  {
    size_t v1 = x1*count + y1,
           v2 = x2*count + y2;

    g[v1].push_back(v2);
    g[v2].push_back(v1);
  }

  void dfs(Graph& g, size_t v, vector<size_t>& d)
  {
    vector<bool> visited(g.size());
    queue<size_t> q;
    q.push(v);
    visited[v] = true;
    d[v] = 0;

    while(!q.empty())
    {
      size_t n = q.front();
      q.pop();

      for(auto c : g[n])
      {
        if(!visited[c])
        {
          q.push(c);
          visited[c] = true;
          d[c] = d[n] + 1;
        }
      }
    }
  }

  Distances computeDistances(const Matrix& m, size_t row, size_t col)
  {
    const size_t count = m.size();
    const size_t graphSize = count*count;

    Graph g(graphSize);

    for(size_t i = 0; i < count; ++i)
    {
      for(size_t j = 0; j < count; ++j)
      {
        if(m[i][j] != 'w')
        {
          if(j < count-1 && m[i][j+1] != 'w')
          {
            // connect (i,j) and (i,j+1)
            addEdge(g, count, i, j, i, j+1);
          }

          if(i < count-1 && m[i+1][j] != 'w')
          {
            // add edge (i,j) and (i+1,j)
            addEdge(g, count, i, j, i+1, j);
          }
        }
      }
    }

    vector<size_t> d(g.size());
    dfs(g, (row*count)+col, d);

    Distances dist(count);

    for(size_t i = 0; i < count; ++i)
    {
      for(size_t j = 0; j < count; ++j)
      {
        if(m[i][j] == 'o')
        {
          dist[i].push_back(d[i*count+j]);
        }
        else
        {
          dist[i].push_back(0);
        }
      }
    }

    return dist;
  }
}

int main(int argc, char* argv[])
{
  Matrix m = {
    { 'o', 'o', 'o', 'g', 'o' },
    { 'o', 'o', 'w', 'o', 'o' },
    { 'o', 'g', 'o', 'o', 'w' },
    { 'o', 'w', 'g', 'o', 'o' },
    { 'w', 'o', 'o', 'o', 'g' }
  };

  Distances d = computeDistances(m, 3, 2);

  for(auto i : d)
  {
    for(auto j : i)
    {
      std::cerr << j << " ";
    }

    std::cerr << std::endl;
  }
}
