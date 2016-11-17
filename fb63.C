// Pb:
// ---
// 
// Given a set of n people, find the celebrity. 
// Celebrity is a person who: 
// 1. Knows only himself and no one else 
// 2. Every one else knows this person 
// 
// You are given the following helper function: 
// bool knows(i, j); 
// Returns: 
// True: If i knows j 
// False: otherwise 
// 
// I proposed the O(n2) algorithm at first but he wanted me to improve on it.
// He wanted an O(n) algorithm
// 
// Sol:
// ----
// 
// Its almost like finding the max from a list, by assuming the first element as
// the max and as you are iterating updating the current max.
//

#include <iostream>

#define n 4

namespace
{
  bool knows(size_t i, size_t j)
  {
    return j == n-1;
  }

  size_t findCeleb()
  {
    size_t celeb = 0;

    for(size_t i = 1; i < n; ++i)
    {
      if(knows(celeb, i) && !knows(i, celeb))
      {
        celeb = i;
      }
    }

    return celeb;
  }
}

int main(int argc, char* argv[])
{
  std::cerr << "Celeb is " << findCeleb() << std::endl;
  return 0;
}

