// Given a random string S and another string T with unique elements, find the
// minimum consecutive sub-string of S such that it contains all the elements in T. 
// 
// example: 
//
// S='adobecodebanc' 
// T='abc' 
// answer='banc'

#include <string>
#include <limits>
#include <iostream>

namespace
{
  bool isMatch(size_t* curHist, size_t* targetHist)
  {
    for(size_t i = 0; i < 256; ++i)
    {
      if(targetHist[i] > 0 && curHist[i] == 0)
      {
        return false;
      }
    }

    return true;
  }

  std::string getSubstr(const std::string& str, const std::string& chars)
  {
    std::string sub;

    if(str.size() < chars.size())
    {
      return sub;
    }

    // Build histograms.

    size_t targetHist[256];
    memset(targetHist, 0, 256*sizeof(size_t));

    for(auto c : chars)
    {
      ++targetHist[c];
    }

    size_t curHist[256];
    memset(curHist, 0, 256*sizeof(size_t));

    const size_t targetSize = chars.size();

    size_t i = 0;

    for(; i < targetSize; ++i)
    {
      ++curHist[str[i]];
    }

   // Scan the rest of the string using the sliding window.

    const size_t count = str.size();

    size_t start = 0,
           end = i-1,
           minStart = 0,
           minEnd = 0,
           minLen = std::numeric_limits<size_t>::max();

    do
    {
      while(isMatch(curHist, targetHist))
      {
        size_t curLen = end - start + 1;
   
        if(curLen < minLen)
        {
          minLen = curLen;
          minStart = start;
          minEnd = end;
        }

        --curHist[str[start]];
        ++start;
      }

      ++end;
      ++curHist[str[end]];
    }
    while(end < count);

    if(minLen < std::numeric_limits<size_t>::max())
    {
      // Build the substr
      sub = str.substr(minStart, minLen);
    }

    return sub;    
  }
}

int main(int argc, char* argv[])
{
  std::cerr << "Enter string: ";
  std::string str;
  std::cin >> str;

  std::cerr << "Enter chars: ";
  std::string chars;
  std::cin >> chars;

  std::cerr << "Substring is: " << getSubstr(str, chars) << std::endl;
  return 0;
}

