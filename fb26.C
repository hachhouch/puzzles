// Pb:
// ---
//
// Convert a number to English representation. 
// Ex: Input : 100 
// Output : One Hundred.
//
// Sol:
// ---
//
// 

#include <iostream>
#include <limits>
#include <string>

using std::string;

namespace
{
  string toStr(int n)
  {
    const char* digits[] = {
      "",
      "one",
      "two",
      "three",
      "four",
      "five",
      "six",
      "seven",
      "eight",
      "nine"
    };

    const char* lessThan20[] = {
      "ten",
      "eleven",
      "twelve",
      "thirteen",
      "fourteen",
      "fifteen",
      "seventeen",
      "eighteen",
      "nineteen"
    };

    const char* tens[] = {
      "",
      "",
      "twenty",
      "thirty",
      "fourty",
      "fifty",
      "sixty",
      "seventy",
      "eighty",
      "ninety"
    };

    // n < 1000

    string str;
 
    int h = n /100;
    n = n%100;

    if(h > 0)
    {
      str += digits[h];
      str += " hundreds ";
    }

    int t = n/10;
    n = n%10;

    if(t >= 2)
    {
      str += tens[t];

      if(n > 0)
      {
        str += " ";
        str += digits[n];
      } 
    }
    else if(t == 1)
    {
      str += lessThan20[n];
    }
    else
    {
      str += digits[n];
    }

    return str;
  }


  string getStr(int n)
  {
    string str;

    int billions = n/1000000000;
    n = n % 1000000000;

    if(billions > 0)
    {
      str += toStr(billions);
      str += " billions ";
    }

    int millions = n/1000000;
    n = n % 1000000;

    if(millions > 0)
    {
      str += toStr(millions);
      str += " millions ";
    }

    int thousands = n/1000;
    n = n % 1000;

    if(thousands > 0)
    {
      str += toStr(thousands);
      str += " thousands ";
    }

    if(n > 0)
    {
      str += toStr(n);
    }

    return str;
  }
}

int main(int argc, char* argv[])
{
  std::cerr << std::numeric_limits<int>::max() << std::endl;
  std::cerr << getStr(std::numeric_limits<int>::max()) << std::endl;

  return 0;
}

