// Write Program for String Permutations using most efficient algorithm.
// 
// Can you solve problem in O(n) time ?
// 
//

#include <string>
#include <iostream>

using std::string;

namespace
{
  void swap(string& str, size_t i, size_t j)
  {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
  }

  void printPermutations(string& str, size_t start)
  {
    const size_t count = str.size();

    if(start == count-1)
    {
      std::cerr << str << std::endl;
      return;
    }

    printPermutations(str, start+1);

    for(size_t i = start+1; i < count; ++i)
    {
      swap(str, start, i);
      printPermutations(str, start+1);
      swap(str, start, i);
    }
  }
}

int main(int argc, char* argv[])
{
  string str{"abc"};
  printPermutations(str, 0);
  return 0;
}

