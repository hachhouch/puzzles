// You are given a set of unique characters and a string. 
// 
// Find the smallest substring of the string containing all the characters in the set. 
// 
// ex: 
// Set : [a, b, c] 
// String : "abbcbcba" 
// 
// Result: "cba"

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <limits>

using std::string;
using std::vector;
using std::array;

namespace
{
  using CharList = vector<char>;
  using Counter = array<size_t, 26>;

  bool isValid(const Counter& c)
  {
    for(auto i : c)
    {
      if(i == 0)
      {
        return false;
      }
    }

    return true;
  }

  string getSmallestSub(const string& str, CharList& a)
  {
    Counter counter = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    for(char c : a)
    {
      counter[c-'a'] = 0;
    }

    const size_t count = str.size();

    size_t start = 0,
           end = 0,
           optStart = 0,
           optEnd = std::numeric_limits<size_t>::max();

    bool foundOne{false};

    counter[str[start]-'a']++;

    while(end < count)
    {
      ++end;
      counter[str[end]-'a']++;

      while(isValid(counter) && start <= end)
      {
        if( (end - start) < (optEnd - optStart))
        {
          optStart = start;
          optEnd = end;
          foundOne = true;
        }

        counter[str[start]-'a']--;
        ++start;
      }
    }

    return foundOne ? str.substr(optStart, optEnd+1) : "";
  }
}

int main(int argc, char* argv[])
{
  CharList a = {'a', 'b', 'c'};
  string str{"abbcbcba"};
  std::cerr << "Smallest substr = " << getSmallestSub(str, a) << std::endl;
  return 0;
}
 
