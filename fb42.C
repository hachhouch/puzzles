// Pb:
// ---
// 
// We know a string is Palindrome if it is the same reading from both sides.
// Now we define the following string also Palindrome: 
// 
// A man, a plan, a canal, Panama! 
// 
// Write a code that returns if an string is palindrome and it should return
// true for above input. (Without directly saying, I should conclude that I
// have to only consider alphanumerical characters in a string). In addition, 
// we assume the string is very long and we can not keep a copy of this string
// or even a copy of preprocessed version of this string. Therefore the result
// should be returned with the first sweep of the string.
// 
// Sol:
// ----
// 
// Scan from both ends and ignore non alphabetical chars.
// 

#include <string>
#include <iostream>

using std::string;

namespace
{
  bool isAlphabetical(char c)
  {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  }

  bool areEqual(char c1, char c2)
  {
    return c1 == c2 ||
           c1 - 'a' == c2 - 'A' ||
           c1 - 'A' == c2 - 'a';
  }

  bool isPalindrom(const string& str)
  {
    const size_t count = str.size();
    size_t l = 0, r = count-1;

    while(l<r)
    {
      if(!isAlphabetical(str[l]))
      {
        ++l;
        continue;
      }
      
      if(!isAlphabetical(str[r]))
      {
        --r;
        continue;
      }

      if(!areEqual(str[l], str[r]))
      {
        return false;
      }
      else
      {
        ++l;
        --r;
      }
    }

    return true;
  }
}

int main(int argc, char* argv[])
{
  string str{"A man, a plan, a canal, Panama!"};
  std::cerr << "isPalindrome() returned " << std::boolalpha << isPalindrom(str)
            << std::endl;
  return 0;
}

