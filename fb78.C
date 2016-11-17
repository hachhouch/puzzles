// Pb:
// ---
//
// Write a program to find pattern. 
//
// 0: 1 
// 1: 11 
// 2: 21 
// 3: 1211 
// 4: 111221 
// 5: 312211 
//
// Iterate over the previous number, and find count for same number number.
// Append that count before number. 
//
// e.g., 
//
// public String pattern(int input){} 
//
// If input = 4, function should return 111221.
//
// Explanation:
// ------------
//
// You're given number n and your task is to return nth look-and-say sequence.
// 
// Wiki:
// 
// In mathematics, the look-and-say sequence is the sequence of integers
// beginning as follows:
// 
// 1, 11, 21, 1211, 111221, 312211, 13112221, 1113213211, ... (sequence A005150 in OEIS).
// To generate a member of the sequence from the previous member, read off the digits of
// the previous member, counting the number of digits in groups of the same digit.
// For example:
// 
// 1 is read off as "one 1" or 11.
// 11 is read off as "two 1s" or 21.
// 21 is read off as "one 2, then one 1" or 1211.
// 1211 is read off as "one 1, then one 2, then two 1s" or 111221.
// 111221 is read off as "three 1s, then two 2s, then one 1" or 312211.
// 

#include <string>
#include <sstream>
#include <iostream>

using std::string;

namespace
{
  string getPattern(size_t n)
  {
    if(n == 0)
    {
      return "1";
    }

    string str = getPattern(n-1);
    const size_t size = str.size();

    char current = str[0];
    size_t count = 1;
    std::ostringstream oss;

    for(size_t i = 1; i < size; ++i)
    {
      if(str[i] == current)
      {
        ++count;
      }
      else
      {
        oss << count << current;
        current = str[i];
        count = 1;
      }
    }

    oss << count << current;
    return oss.str();
  }
}

int main(int argc, char* argv[])
{
  std::cerr << getPattern(7) << std::endl;
  return 0;
}

