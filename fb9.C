// Given a decimal number, write a function that returns its negabinary (i.e. negative 2-base)
// representation as a string.
// 
// #!/usr/bin/env python3
// assert solution(-15) ==	'110001'
// assert solution(2) == '110'
// assert solution(13) == '11101'

#include <string>
#include <iostream>

namespace
{
  std::string toNegaBinary(int n)
  {
    const int base = -2;
    std::string str;

    while(n != 0)
    {
      int div = n/base,
          remainder = (n - (base*div));

      if(remainder < 0)
      {
        remainder += base;
        div += 1;
      }

      str.insert(0, remainder == 0 ? "0" : "1");
      n = div;
    }

    return str;
  }
}

int main(int argc, char* argv[])
{
  int n = -15;
  std::string str = toNegaBinary(n);
  std::cerr << n << " ==> " << str << std::endl;

  n = 2;
  str = toNegaBinary(n);
  std::cerr << n << " ==> " << str << std::endl;

  n = 13;
  str = toNegaBinary(n);
  std::cerr << n << " ==> " << str << std::endl;
}

