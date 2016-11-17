// Pb1:
// ----
// 
// write a function that detects conflicts in given meeting schedules 
// input: a list of intervals, [(s1, e1), (s2, e2), ] 
// output: return True if there's any conflict, False otherwise
// 
// Pb2:
// ----
// 
// write a function that calculates the minimum number of meeting rooms 
// that can accommodate given schedules 
// input: same 
// output: # of rooms 
// Also back to back events are allowed e.g. {2,5} {5,9} correct o/p:1
// 
// Sol1:
// -----
//
// Sort on start time and scan the sorted list.
//
// Sol2:
// -----
//
// Put all numbers in a simple array but the end time with a negative sign
// - Sort the array by the absolute value of elements
// - Do a simple for loop, keeping a current value of number of currently scheduled meetings;
//   if the current number is positive - increase it by 1, otherwise - decrease by 1
// - Keep track of its maximum value - that's the answer

#include <vector>
#include <utility>
#include <iostream>

using std::vector;
using std::pair;
using std::make_pair;

namespace
{
  using Interval = pair<int, int>;
  using Schedule = vector<Interval>;

  bool hasConflict(Schedule& s)
  {
    if(s.empty())
    {
      return false;
    }

    std::sort(
      s.begin(),
      s.end(),
      [] (const Interval& lhs, const Interval& rhs) -> bool {return lhs.first < rhs.first;}
    );

    const size_t count = s.size();

    int endTime = s[0].second;

    for(size_t i = 1; i < count; ++i)
    {
      if(s[i].first < endTime)
      {
        return true;
      }

      if(s[i].second > endTime)
      {
        endTime = s[i].second;
      }
    }

    return false;
  }

  size_t getRequiredRooms(const Schedule& s)
  {
    vector<int> a;

    for(const auto& m : s)
    {
      a.push_back(m.first);
      a.push_back(m.second * (-1));
    }

    struct Compare
    {
      bool operator()(int a, int b)
      {
        if(std::abs(a) == std::abs(b))
        {
          return a < b;
        }

        return std::abs(a) < std::abs(b);
      }
    };

    std::sort(
      a.begin(),
      a.end(),
      Compare()
    );

    size_t max = 0;
    size_t counter = 0;

    for(int i : a )
    {
      if(i >= 0)
      {
        ++counter;
      }
      else
      {
        --counter;
      }

      if(counter > max)
      {
        max = counter;
      }
    }

    return max;
  }
}

int main(int argc, char* argv[])
{
  Schedule s = {
    {2, 5},
    {3, 8},
    {7, 10},
    {9,11}
  };

  std::cerr << "Conflict: " << std::boolalpha << hasConflict(s) << std::endl;
  std::cerr << "Room #: " << getRequiredRooms(s) << std::endl;

  return 0;
}

