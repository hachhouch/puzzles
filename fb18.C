// Pb:
// ---
//
// Given integer k and a subset S of set {0, 1, 2, ..., 2^k - 1} 
// Return the count of pairs (a, b) where a and b are from S and (a < b) and (a & b == a) 
// & here is bit-wise and. 
// Do it faster than O((2^k)^2), assume k <= 16 
// 
// Example: 
// 0b111 
// 0b101 
// 0b010 
// Answer: 2 
// 
// 0b110 
// 0b011 
// 0b101 
// Answer: 0
//
// Solution:
// ---------
//
// 1) sort in desc order
// 2) For each number loop on k
//      Zero kth bit
//      Binary search for that new number in S
//

#include <vector>
#include <iostream>

using std::vector;

namespace
{
  using Values = vector<unsigned short>;
  
  const unsigned short k = 16;

  size_t getPairCount(Values& s)
  {
    size_t count = 0;

    // Sort the input
    std::sort(s.begin(), s.end());

    // Try each number from larger to smaller
    for(size_t i = s.size(); i > 0; --i)
    {
      unsigned short v = s[i-1];
 
      for(int i = k-1; i >= 0; --i)
      {
        
        unsigned short tmp = v & ~(1 << i);

        if(tmp != v)
        {
          if(std::binary_search(s.begin(), s.end(), v))
          {
            ++count;
          }
      
          v = tmp;
        }
      }
    }

    return count;
  }
}

int main(int argc, char* argv[])
{
  Values s{7, 5, 2};
  std::cout << "Count = " << getPairCount(s) << std::endl;
  return 0;
}

