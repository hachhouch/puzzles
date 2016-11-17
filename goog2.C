// Given a string return the longest palindrome that can be constructed by removing or shuffling characters. 
// 
// Example: 
// 'aha' -> 'aha' 
// 'ttaatta' -> ' ttaaatt' 
// 'abc' -> 'a' or 'b' or 'c' 
// 'gggaaa' -> 'gaaag' or 'aggga' 
// 
// Note if there are multiple correct answers you only need to return 1 palindrome.

#include <string>
#include <array>
#include <iostream>

namespace mhl
{
  void getPalindrome(std::string& input)
  {
    std::array<size_t, 127> counter = {0};

    for(auto c : input)
    {
      counter[c]++;
    }

    size_t k = 0;
    char middle = 0;

    for(unsigned short i = 0; i < 127; ++i)
    {
      if(counter[i] >= 2)
      {
        size_t count = counter[i]/2;
        
        for(size_t j = 0; j < count; ++j)
        {
          input[k++] = i;
        }

        if(counter[i]%2 > 0 )
        {
          middle = i;
        }
      }
      else if (counter[i] == 1)
      {
        middle = i;
      }
    }
    
    if(middle != 0)
    {
      input[k++] = middle;
    }

    for(int i = k-2; i >= 0; --i)
    {
      input[k++] = input[i];
    }

    input.erase(k);
    return;
  }
}

int main(int argc, char* argv[])
{
  std::string input = argv[1];
  mhl::getPalindrome(input);
  std::cerr << input << std::endl;
}


