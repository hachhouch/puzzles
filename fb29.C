// Given n, return 1 ^ 2 ^ 3 ^ ... ^ n 
// Where ^ is binary xor. 
// Note: n is a 64-bit number, and 1<<63 is a valid n for this problem. 
// 
// Examples:
// 
// 
// >>> reduce(lambda a,b:a^b, [1,2,3])
// 0
// >>> reduce(lambda a,b:a^b, [1,2,3,4])
// 4
// >>> reduce(lambda a,b:a^b, [1,2,3,4,5,6,7])
// 0
// >>> reduce(lambda a,b:a^b, [1,2,3,4,5,6,7,8,9])
// 1

#include <iostream>

namespace
{
  size_t getResult(size_t n)
  {
    switch(n % 4)
    {
      case 0:
        return n;

      case 1:
        return 1;

      case 2:
        return n+1;

      case 3:
        return 0;
    }

    return -1;
  }
}

int main(int argc, char* argv[])
{
  std::cerr << "Enter number: ";
  size_t n;
  std::cin >> n;
  std::cerr << "Result = " << getResult(n) << std::endl;
  return 0;
}

