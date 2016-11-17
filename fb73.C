// Pb:
// ---
// 
// Given a list of strings, return a list of lists of strings that groups all anagrams. 
// 
// Ex. given {trees, bike, cars, steer, arcs} 
// return { {cars, arcs}, {bike}, {trees, steer} } 
// 
// m = # of words 
// n = length of longest word 
// 
// I solved this in O(m * n * log n) time.
// 
// Sol:
// ----
// 

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

using std::unordered_map;
using std::vector;
using std::string;

namespace
{
  using Words = vector<string>;
  using Solution = vector<Words>;
  using Hash = unordered_map<string, Words>;

  Solution getAnagrams(const Words& strs)
  {
    Hash h;

    for(const auto& w : strs)
    {
      string tmp{w};
      std::sort(tmp.begin(), tmp.end());
      h[tmp].push_back(w);
    }

    Solution s;
    s.resize(h.size());
    size_t i = 0;

    for(const auto& p : h)
    {
      std::copy(p.second.begin(), p.second.end(), std::back_inserter(s[i]));
      ++i;
    }

    return s;
  }
}

int main(int argc, char* argv[])
{
  Words strs = {
    "trees",
    "bike",
    "cars",
    "steer",
    "arcs"
  }; 

  Solution sol = getAnagrams(strs);

  for(const auto& s : sol)
  {
    for(const auto& w : s)
    {
      std::cerr << w << " ";
    }

    std::cerr << std::endl;
  }

  return 0;
}

