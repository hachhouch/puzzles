// Pb:
// ---
// 
// Let's say there is a double square number X, which can be expressed as
// the sum of two perfect squares, for example, 10 is double square 
// because 10 = 3^2 + 1^2 
// 
// Determine the number of ways which it can be written as the sum of two squares
// 
// Sol:
// ----
//
// This solution is similar to the 2-sum algorithm, used to see whether any two
// values of a sorted array sum to a specific number. 
//
// In this case, however, the lower bound is zero, while the upper bound is the
// square root of N. We set a cursor on the lower bound, and it only moves in
// +1 steps. Also, we set another cursor on the upper bound, and it only moves
// in -1 steps. 
//
// Whenever the sum of squares is greater than N, we need to decrease the sum.
// In order to do so, we move the upper cursor down (j = j-1). Whenever the sum
// is lower than N, we move the lower cursor up (i = i+1). Else, when we find
// a match, we move both.
//

#include <cmath>
#include <iostream>

namespace
{
  void findSums(size_t n)
  {
    size_t k = std::sqrt(n);

    size_t i = 0, j = k;

    while(i <= j)
    {
      size_t a = i*i, b = j*j;
      size_t s = a + b;

      if(s == n)
      {
        std::cerr << "Found one: " << n << " = "  << a << " + " << b << std::endl;
        --j;
        ++i;
      }
      else if(s < n)
      {
        ++i;
      }
      else
      {
        --j;
      }
    }
  }
}

int main(int argc, char* argv[])
{
  findSums(10);
  return 0;
}

