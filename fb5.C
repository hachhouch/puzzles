// Problem:
// --------
// 
// Given a string "str" and pair of "N" swapping indices, generate a lexicographically largest
// string. Swapping indices can be reused any number times. 
// 
// Ex.
// 
// String: "abdc" 
// Indices: (1,4) (3,4) 
// Answer: cdba, cbad, dbac,dbca 
// 
// you should print only "dbca" which is lexicographically largest
// 
// Response:
// ---------
// 
// Consider indices as vertices.
// Connect two vertices with an edge if swapping is allowed between them
// 
// Now for each connected component in graph sort the characters represented by the indices
// (vertex) and place them from highest value to lowest value in those indices.
// 
// Result would be a lexicographically largest string.
// 

#include <vector>
#include <unordered_set>
#include <queue>
#include <utility>
#include <iostream>

namespace
{
  using Swap = std::pair<size_t, size_t>;
  using SwapList = std::vector<Swap>;

  using Edges = std::vector<size_t>;
  using Graph = std::vector<Edges>;

  using Component = std::vector<size_t>;
  using ComponentList = std::vector<Component>;

  bool buildGraph(const SwapList& swaps, Graph& g)
  {
    for(const auto& s : swaps)
    {
      // Swaps are 1-based (not 0-based)
      const size_t v1 = s.first - 1,
                   v2 = s.second - 1;

      // Assume no duplicates

      g[v1].push_back(v2);
      g[v2].push_back(v1);
    }

    return true;
  }

  ComponentList findConnectedComponents(Graph& g)
  {
    ComponentList components;
    std::unordered_set<size_t> visited;

    const size_t vertexCount = g.size();

    for(size_t i = 0; i < vertexCount; ++i)
    {
      if(visited.find(i) == visited.end())
      {
        Component comp;

        //std::cerr << "processing node " << i << std::endl;

        std::queue<size_t> toVisit;
        toVisit.push(i);
        
        while(!toVisit.empty())
        {
          size_t current = toVisit.front();
          toVisit.pop();
          visited.insert(current);
          comp.push_back(current);

          for(const auto& child : g[current])
          {
            //std::cerr << "Exploring child " << child << std::endl;

            if(visited.find(child) == visited.end())
            {
              toVisit.push(child);
            }
          }
        }

        components.push_back(comp);
      }
    }

    return components;
  }

  std::string getLargest(const std::string& str, const SwapList& swaps)
  {
    Graph g;
    g.resize(str.size());
    buildGraph(swaps, g);

    ComponentList cl = findConnectedComponents(g);

    std::string largest;
    largest.resize(str.size());

    for(auto c : cl)
    {
      std::cerr << std::endl << "Component: ";
      std::string compStr;

      for(const auto& i : c)
      {
        std::cerr << i << " ";
        compStr.push_back(str[i]);
      }

      //std::cerr << std::endl;

      std::sort(compStr.begin(), compStr.end(), std::greater<char>());
      std::sort(c.begin(), c.end());

      const size_t count = compStr.size();

      for(size_t i = 0; i < count; ++i)
      {
        largest[c[i]] = compStr[i];
      }
    }

    return largest;
  }
}

int main(int argc, char* argv[])
{
  std::string str = "abdc";
  SwapList swp = {{1,4}, {3,4}};

  std::cerr << "Largest string is: " << getLargest(str, swp) << std::endl;
  return 0;
}

