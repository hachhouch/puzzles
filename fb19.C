// Given an undirected graph and a node, modify the graph into a directed graph
// such that, any path leads to one particular node.
//
// This is simply creating a tree rooted at (and directed to) the given node and
// then completing it to a DAG, any search algorithm (e.g. BFS or DFS) can give you
// a solution: Starting with the given node, using the search algorithm - Whenever
// encountering a node, connect it to an already connected node (usually to the one
// from which you got to it), you can then set the direction for the remaining edges
// according to the order in which you encountered the nodes (from the latter to 
// the earlier)

#include <vector>
#include <stack>
#include <iostream>

using std::vector;
using std::stack;

namespace
{
  using Edges = vector<size_t>;
  using Graph = vector<Edges>;

  void doDFS(Graph& g, size_t n, vector<bool>& visited)
  {
    visited[n] = true;

    for(auto c : g[n])
    {
      if(visited[c] == false)
      {
        doDFS(g, c, visited);
        g[c].clear();
        g[c].push_back(n);
      }
    }
  }

  void transform(Graph& g, size_t s)
  {
    const size_t count = g.size();
    vector<bool> visited(count, false);
    doDFS(g, s, visited);
    g[s].clear();

    for(size_t i = 0; i < count; ++i)
    {
      if(!visited[i])
      {
        doDFS(g, i, visited);
        g[i].clear();
        g[i].push_back(s);
      }
    }
  }

  void addVertex(Graph& g, size_t i, size_t j)
  {
    g[i].push_back(j);
    g[j].push_back(i);
  }
}

int main(int argc, char* argv[])
{
  const size_t count = 8;
  Graph g(count);
  addVertex(g, 0, 1);
  addVertex(g, 0, 2);
  addVertex(g, 1, 3);
  addVertex(g, 2, 3);
  addVertex(g, 3, 4);
  addVertex(g, 5, 6);
  addVertex(g, 6, 7);

  transform(g, 2);

  for(size_t i = 0; i < count; ++i)
  {
    for(auto j : g[i])
    {
      std::cerr << i << "->" << j << std::endl;
    }
  }

  return 0;
}

