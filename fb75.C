// Pb:
// ---
// 
// You are given an array of non-negative integers (0, 1, 2 etc). The value in
// each element represents the number of hops you may take to the next
// destination. Write a function that determines when you start from the
// first element whether you will be able to reach the last element of the array. 
// 
// if a value is 3, you can take either 0, 1, 2 or 3 hops. 
// 
// For eg: for the array with elements 1, 2, 0, 1, 0, 1, any route you take
// from the first element, you will not be able to reach the last element.
// 
// Sol:
// ----
// 
//

#include <vector>
#include <iostream>

using std::vector;

namespace
{
  using Hops = vector<size_t>;

  bool isReachable(const Hops& h)
  {
    const size_t count = h.size();
    size_t last = count;

    for(size_t i = count-1; i > 0; --i)
    {
      if(i+h[i-1] >= last)
      {
        last = i;
      }
    }

    return last == 1;
  }
}

int main(int argc, char* argv[])
{
  Hops h = {1, 2, 0, 1, 0, 1};
  std::cerr << std::boolalpha << isReachable(h) << std::endl;
  return 0;
}

