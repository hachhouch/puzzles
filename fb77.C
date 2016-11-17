// Pb:
// ---
// 
// There's a new language which uses the latin alphabet. However, you don't know
// the order among letters. 
// 
// It could be: 
// a b c d ... 
// 
// as it could also be: 
// 
// b e z a m i ... 
// 
// You receive a list of words lexicographically sorted by the rules of this new
// language. From this list, derive one valid particular ordering of letters in
// this language.
// 
// Sol:
// ----
// 
// A) from the words, figure out which letter precedes which. This gives you a DAC
//    where there is an edge from char 'a' to char 'b' only if 'a' supersedes 'b'
//    in the order. 
// 
// B) Run DFS to get (a) topological order. The topological order is the reverse
//    order of the items you mark as visited.

#include <vector>
#include <string>
#include <stack>
#include <iostream>

using std::vector;
using std::string;
using std::stack;

namespace
{
  using AdjMatrix = vector<vector<bool>>;
  using Words = vector<string>;

  void dfs(int i, const AdjMatrix& m, vector<bool>&v, stack<int>& s)
  {
    v[i] = true;

    for(int j = 0; j < 26; ++j)
    {
      if(m[i][j] == true && !v[j])
      {
        dfs(j, m, v, s);
      }
    }

    s.push(i);
  }

  string getAlphabet(const Words& w)
  {
    AdjMatrix m(26);

    for(size_t i = 0; i < 26; ++i)
    {
      m[i].resize(26);
    }

    const size_t count = w.size();

    for(size_t i = 0; i < count; ++i)
    {
      for(size_t j = i+1; j < count; ++j)
      {
        size_t len = std::min(w[i].size(), w[j].size());
        size_t k = 0;

        while(k < len && w[i][k] == w[j][k]) ++k;

        if(k < len)
        {
          m[w[i][k] - 'a'][w[j][k] - 'a'] = true;
        }
      }
    }

    vector<bool> visited(26);
    stack<int> s;

    for(int i = 0; i < 26; ++i)
    {
      if(!visited[i])
      {
        dfs(i, m, visited, s);
      }
    }

    string ret;

    while(!s.empty())
    {
      ret += ('a' + s.top());
      s.pop();
    }

    return ret;
  }

}

int main(int argc, char* argv[])
{
  Words w = {
    "aaa",
    "aba",
    "aca",
    "ada",
    "aea",
    "afa",
    "aga",
    "aha",
    "aia",
    "aja",
    "aka",
    "ala",
    "ama",
    "ana",
    "aoa",
    "apa",
    "aqa",
    "ara",
    "asa",
    "ata",
    "aua",
    "ava",
    "awa",
    "axa",
    "aya",
    "aza"
  };

  std::cerr << getAlphabet(w) << std::endl;
  return 0;
}

