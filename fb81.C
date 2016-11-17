// Pb:
// ---
//
// You're given a dictionary of strings, and a key. Check if the key is composed
// of an arbitrary number of concatenations of strings from the dictionary.
// 
// For example: 
// 
// dictionary: "world", "hello", "super", "hell" 
// 
// key: "helloworld" --> return true 
// key: "superman" --> return false 
// key: "hellohello" --> return true
//
// Sol:
// ----
//
// Word split

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>

using std::string;
using std::vector;

namespace
{
  using Dict = std::unordered_set<string>;

  bool canSplit(const string& w, const Dict& d)
  {
    size_t count = w.size();
    vector<bool> dp(count);

    for(size_t i = 0; i < count; ++i)
    {
      //std::cerr << "Checking " << w.substr(0, i+1) << std::endl;

      if(dp[i] == false && d.find(w.substr(0, i+1)) != d.end())
      {
        dp[i] = true;
      }

      if(dp[i] == true)
      {
        if(i == count-1)
        {
          return true;
        }

        size_t j = i+1;

        for(; j < count; ++j)
        {
          //std::cerr << " " << w.substr(i+1, j-i) << std::endl;

          if(dp[j] == false && d.find(w.substr(i+1, j-i)) != d.end())
          {
            dp[j] = true;
        
            if(j == count-1)
            {
              return true;
            }
          }
        }
      }
    }

    return false;
  }
}

int main(int argc, char* argv[])
{
  Dict d = { "world", "hello", "super", "hell"};

  std::cerr << std::boolalpha << canSplit("helloworld", d) << std::endl;
  std::cerr << std::boolalpha << canSplit("superman", d) << std::endl;
  std::cerr << std::boolalpha << canSplit("hellohello", d) << std::endl;
  
  return 0;
} 

