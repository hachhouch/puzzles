// Pb:
// ---
// 
// Find the maximum number of non-intersecting events in a calendar.
// 
// Sol:
// ----
// 

#include <utility>
#include <vector>
#include <iostream>

using std::pair;
using std::vector;

namespace
{
  using Interval = pair<size_t, size_t>;
  using Calendar = vector<Interval>;

  // Wrong solution
  size_t getMaxNonIntersecting(Calendar& cal)
  {
    if(cal.empty())
    {
      return 0;
    }

    std::sort(
      cal.begin(),
      cal.end(),
      [] (const Interval& lhs, const Interval& rhs) -> bool {return lhs.first < rhs.first;} 
    );

    const size_t count = cal.size();
    size_t counter = 1;

    Interval current = cal[0];

    for(size_t i = 1; i < count; ++i)
    {
      if(cal[i].first <= current.second)
      {
        current.second = std::max(current.second, cal[i].second);
      }
      else
      {
        ++counter;
        current = cal[i];
      }
    }

    return counter;
  }

  size_t getMaxNonIntersecting2(Calendar& cal)
  {
    if(cal.empty())
    {
      return 0;
    }

    std::sort(
      cal.begin(),
      cal.end(),
      [] (const Interval& lhs, const Interval& rhs) -> bool {return lhs.second < rhs.second;} 
    );

    const size_t count = cal.size();

    size_t counter = 0;

    while(!cal.empty())
    {
      Interval i = cal[0];

      for(size_t j = 1; j < cal.size();)
      {
        if(cal[j].first <= i.second)
        {
          cal.erase(cal.begin() + j);
        }
        else
        {
          ++j;
        }
      }

      cal.erase(cal.begin());
      ++counter;
    }

    return counter;
  }
}

int main(int argc, char* argv[])
{
  Calendar cal = {
    {0, 3},
    {2, 10},
    {9, 11},
    {20, 30},
    {15, 17},
    {29, 30},
    {100, 101}
  };

  std::cerr << "Max = " << getMaxNonIntersecting2(cal) << std::endl;
  return 0;
}

