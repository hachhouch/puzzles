// Pb:
// ---
// 
// Given two strings, return boolean True/False, if they are only one
// edit apart.Edit can be insert/delete/update of only one character
// in the string. Eg: 
// 
// -True 
// xyz,xz 
// xyz, xyk 
// xy, xyz 
// 
// 
// -False 
// xyz, xyz 
// xyz,xzy 
// x, xyz
// 
// Sol:
// ----
//

#include <string>
#include <iostream>

using std::string;

namespace
{
  bool areOneEditAway(const string& lhs, size_t i, const string& rhs, size_t j)
  {
    if(i == lhs.size())
    {
      return rhs.size() - j == 1;
    }


    if(j == rhs.size())
    {
      return lhs.size() - i == 1;
    }

    if(lhs[i] == rhs[i])
    {
      return areOneEditAway(lhs, i+1, rhs, j+1);
    }
    else
    {
      return lhs.compare(i+1, lhs.size()-(i+1), rhs, j+1, rhs.size() - (j+1)) == 0 ||
             lhs.compare(i, lhs.size()-i, rhs, j+1, rhs.size()-(j+1)) == 0 ||
             lhs.compare(i+1, lhs.size()-(i+1), rhs, j, rhs.size() - j) == 0;
    }
  }

  bool areOneEdit(const string& lhs, const string& rhs)
  {
    return areOneEditAway(lhs, 0, rhs, 0);
  }
}

int main(int argc, char* argv[])
{
  std::cerr << std::boolalpha << areOneEdit("xyz", "xz") << std::endl;
  std::cerr << std::boolalpha << areOneEdit("xyz", "xyk") << std::endl;
  std::cerr << std::boolalpha << areOneEdit("xy", "xyz") << std::endl;
  std::cerr << std::boolalpha << areOneEdit("xyz", "xyz") << std::endl;
  std::cerr << std::boolalpha << areOneEdit("xyz", "xzy") << std::endl;
  std::cerr << std::boolalpha << areOneEdit("x", "xyz") << std::endl;

  return 0;
}

