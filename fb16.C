// Pb:
//
// Given a set of ranges: 
// (e.g. S = {(1, 4), (30, 40), (20, 91) ,(8, 10), (6, 7), (3, 9), (9, 12), (11, 14)}. 
// And given a target range R (e.g. R = (3, 13) - meaning the range going from 3 to 13).
// Write an algorithm to find the smallest set of ranges that covers your target range.
// All of the ranges in the set must overlap in order to be considered as spanning the entire
// target range. (In this example, the answer would be {(3, 9), (9, 12), (11, 14)}.
//
// Sol:
//
//
//

#include <vector>
#include <iostream>
#include <sstream>

using std::vector;

namespace
{
  using Range = std::pair<int, int>;
  using RangeSet = vector<Range>;

  RangeSet getSubset(RangeSet& ranges, const Range& target)
  {
    RangeSet outcome;

    if(ranges.empty())
    {
      return outcome;
    }

    std::sort(
      ranges.begin(),
      ranges.end(),
      [] (const Range& lhs, const Range& rhs) -> bool {return lhs.first < rhs.first;}
    ); 

    Range cur = ranges[0];

    std::cerr << " Processing " << cur.first << " - " << cur.second << std::endl;

    std::cerr << " Set as current " << std::endl;

    if(cur.first > target.first)
    {
      return outcome;
    }

    if(cur.second >= target.second)
    {
      outcome.push_back(cur);
      return outcome;
    }

    const size_t count = ranges.size();
    int start = target.first;

    for(size_t i = 1; i < count; ++i)
    {
      const Range& r = ranges[i];

    std::cerr << " Processing " << r.first << " - " << r.second << std::endl;

      if( r.first <= start && r.second > cur.second )
      {

std::cerr << " Set current 1 " << std::endl;

        cur = r;
      }
      else if( r.first > start )
      {
        
    std::cerr << " adding  " << cur.first << " - " << cur.second << std::endl;
        outcome.push_back(cur);
        start = cur.second;

        if(r.first > start)
        {
          // Found a gap;
          outcome.clear();
std::cerr << " found gap " << std::endl;
          break;
        }
        else
        {
std::cerr << " Set current 2 " << std::endl;
          cur = r;
        }
      }

      if(cur.second >= target.second)
      {
        // Done
        outcome.push_back(cur);
        break;
      }
    }

    return outcome;
  }
}

int main(int argc, char* argv[])
{
  std::cout << "Enter ranges ('\\n' separated and '.' terminated)" << std::endl;

  RangeSet ranges;

  std::string buf;

  while(getline(std::cin, buf))
  {
    if(buf[0] == '.')
    {
      break;
    }

    int x,y;
    std::istringstream iss(buf);
    iss >> x;
    iss >> y;
    ranges.push_back(std::make_pair(x,y));
  }

  std::cout << "Enter target range: ";
  int x,y;
  std::cin >> x;
  std::cin >> y;
  Range target{x,y};

  std::cerr << "Ranges are: " << std::endl;
  std::for_each(
    ranges.begin(),
    ranges.end(),
    [] (const Range& r) {std::cout << "[" << r.first << "," << r.second << "]" << std::endl;}
  );
  std::cerr << std::endl;

  RangeSet outcome = getSubset(ranges, target);

  std::cerr << "Smallest set is: ";
  std::for_each(
    outcome.begin(),
    outcome.end(),
    [] (const Range& r) {std::cout << "[" << r.first << "," << r.second << "]" << std::endl;}
  );
  std::cerr << std::endl;

  return 0;
}

