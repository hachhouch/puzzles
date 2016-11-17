/* -------------------------------------------------------------------------- */

// Problem:
// --------
//
// Given a dictionary containing a list of words, a starting word, and an ending word, return 
// the minimum number of steps to transform the starting word into the ending word. A step involves
// changing one letter at a time to a valid word that is present in the dictionary. Return null if it
// is impossible to transform the starting word into the ending word using the dictionary. 
// 
// Example: 
// 
// Starting word: cat 
// Ending word: dog 
// 
// cat -> cot -> cog -> dog ('cot' and 'cog' are in the dictionary) 
// 
// return 3
//
// Answer:
// -------
//
// This is a minimum edit distance problem. 
//
// http://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/
//

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <assert.h>

using std::vector;
using std::string;

namespace
{
  using Dict = vector<string>;
  using Graph = vector<vector<size_t>>;

  bool areConnected(const string& w1, const string& w2)
  {
    if(w1.size() != w2.size())
    {
      return false;
    }

    const size_t count{w1.size()};
    size_t diff{0};

    for(size_t i = 0; i < count; ++i)
    {
      if(w1[i] != w2[i])
      {
        ++diff;

        if(diff > 1)
        {
          return false;
        }
      }
    }

    return diff == 1;
  }

  int getMinEdits(string& str1, string& str2, const Dict& dict)
  {
    // S1: Build the graph

    const size_t count = dict.size();
    Graph g(count);

    size_t src = 0, dst = 0;

    for(size_t i = 0; i < count; ++i)
    {
      const string& w = dict[i];

      if(w == str1)
      {
        src = i;
      }
      else if(w == str2)
      {
        dst = i;
      }

      for(size_t j = i+1; j < count; ++j)
      {
        const string& w2 = dict[j];

        if(areConnected(w,w2))
        {
          g[i].push_back(j);
          g[j].push_back(i);
        }
      }
    }

    // S2: Use DFS to compute shortest path (if any)

    std::vector<bool> visited(count);
    std::vector<size_t> distance(count);

    for(size_t i = 0; i < count; ++i)
    {
      visited[i] = false;
      distance[i] = 0;
    }

    std::queue<size_t> q;
    q.push(src);
    visited[src] = true;
    distance[src] = 0;

    while(!q.empty())
    {
      size_t n = q.front();
      q.pop();

      for(const auto& c : g[n])
      {
        if(!visited[c])
        {
          visited[c] = true;
          distance[c] = distance[n] + 1;
          q.push(c);
          
          if(c == dst)
          {
            return distance[c];
          }
        }
      }
    }

    return -1;
  }
}

int main(int argc, char* argv[])
{
  Dict dict{"cat", "cot", "cog", "dog"};

  string str1{"cat"},
         str2{"dog"};

  std::cerr << "Solution for " << str1 << " and " << str2 <<  ": "
            << getMinEdits(str1, str2, dict) << std::endl;

  return 0;
}

/* -------------------------------------------------------------------------- */

// Dynamic Programming | Set 5 (Edit Distance)
//
// Given two strings str1 and str2 and below operations that can performed on 
// str1. Find minimum number of edits (operations) required to convert ‘str1′
// into ‘str2′.
// 
// Insert
// Remove
// Replace
// All of the above operations are of equal cost.
// 
// Examples:
// 
// Input:   str1 = "geek", str2 = "gesek"
// Output:  1
// We can convert str1 into str2 by inserting a 's'.
// 
// Input:   str1 = "cat", str2 = "cut"
// Output:  1
// We can convert str1 into str2 by replacing 'a' with 'u'.
// 
// Input:   str1 = "sunday", str2 = "saturday"
// Output:  3
// Last three and first characters are same.  We basically
// need to convert "un" to "atur".  This can be done using
// below three operations. 
// Replace 'n' with 'r', insert t, insert a

#if 0

#include <string>
#include <iostream>

using std::string;

namespace
{
  size_t min3(size_t n1, size_t n2, size_t n3)
  {
    return std::min( std::min(n1, n2), n3);
  }

  size_t getMinEdits(const string& str1, const string& str2)
  {
    if(str1.empty())
    {
      return str1.size();
    }

    if(str2.empty())
    {
      return str2.size();
    }

    const size_t m = str1.size(),
                 n = str2.size();

    size_t** dp = new size_t*[m+1];

    for(size_t i = 0; i <= m; ++i)
    {
      dp[i] = new size_t[n+1];
    }

    for(size_t i = 0; i <= m; ++i)
    {
      dp[i][0] = i;
    }

    for(size_t j = 0; j <= n; ++j)
    {
      dp[0][j] = j;
    }

    for(size_t i = 1; i <= m; ++i)
    {
      for(size_t j = 1; j <= n; ++j)
      {
        if(str1[i] == str2[j])
        {
          dp[i][j] = dp[i-1][j-1];
        }
        else
        {
          dp[i][j] = min3(dp[i-1][j], dp[i-1][j-1], dp[i][j-1]) +1;
        }
      }
    }

    size_t outcome = dp[m][n];

    for(size_t i = 0; i <= m; ++i)
    {
      delete [] dp[i];
    }

    delete [] dp;

    return outcome;
  }
}

int main(int argc, char* argv[])
{
  string str1{"sunday"},
         str2{"saturday"};

  std::cerr << "Min Edits for " << str1 << " and " << str2 <<  ": "
            << getMinEdits(str1, str2) << std::endl;

  str1 = "geek";
  str2 = "gesek";

  std::cerr << "Min Edits for " << str1 << " and " << str2 <<  ": "
            << getMinEdits(str1, str2) << std::endl;

  str1 = "cat";
  str2 = "cut";

  std::cerr << "Min Edits for " << str1 << " and " << str2 <<  ": "
            << getMinEdits(str1, str2) << std::endl;

  return 0;
}

#endif

