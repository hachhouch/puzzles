// Given a class Range
// 
// 
// class Range {
// 	public int begin;
// 	public int end;
// 	public Range(int begin, int end) {
// 		this.begin = begin;
// 		this.end = end;
// 	}
// }
// The problem: 
// Intput: 
// 1) list of Ranges that don't overlap (not sorted) 
// 2) newRange that might overlap. 
// Output: 
// list of merged Ranges 
// 
// For example: 
// Input: [1..5] [9..13] [17..22] 
// newRange: [4..10] 
// Output: [1..13] [17..22]

#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;

namespace
{
  struct Range
  {
    int begin_;
    int end_;

    Range(int b, int e) : begin_(b), end_(e) {}
  };

  using RangeList = vector<Range>;

  size_t binarySearch(const RangeList& ranges, int val)
  {
    size_t i = 0;
    size_t j = ranges.size()-1;

    while(i <= j)
    {
      size_t mid = i + (j-i)/2;

      if(ranges[mid].begin_ > val)
      {
        j = mid-1;
      }
      else
      {
        i = mid+1;
      }
    }

    return i;
  }

  void merge(RangeList& ranges, const Range&  range)
  {
    std::sort(
      ranges.begin(),
      ranges.end(),
      [] (const Range& lhs, const Range& rhs) -> bool {return lhs.begin_ < rhs.begin_;}
    );

    size_t i = binarySearch(ranges, range.begin_);

    ranges.insert(ranges.begin() + i, range);

    size_t j = binarySearch(ranges, range.end_);

    size_t start;

    if(i > 0 && ranges[i-1].end_ > range.begin_)
    {
      start = i-1;
    }
    else
    {
      start = i;
    }

    if(j > 0 && ranges[j-1].end_ > range.end_)
    {
      ranges[start].end_ = ranges[j-1].end_;
    }

    ranges.erase(ranges.begin()+start+1, ranges.begin() + j);
  }

  // Better solution (no sorting)

  void merge2(RangeList& ranges, Range range)
  {
    RangeList newList;

    for(const auto& r : ranges)
    {
      if(r.begin_ > range.end_ || r.end_ < range.begin_)
      {
        newList.push_back(r);
      }
      else
      {
        range.begin_ = std::min(range.begin_, r.begin_);
        range.end_ = std::max(range.end_, r.end_);
      }
    }

    newList.push_back(range);

    ranges = newList;
  }
}

int main(int argc, char* argv[])
{
  RangeList ranges = {
    {1, 5},
    {9, 13},
    {17, 22}
  };

  Range r = {4, 10};

  //merge(ranges, r);
  merge2(ranges, r);

  std::for_each(
    ranges.begin(),
    ranges.end(),
    [] (const Range& r) {std::cerr << r.begin_ << "," << r.end_ << std::endl;}
  );

  return 0;
}

