// Given two arrays/Lists (choose whatever you want to) with sorted and non intersecting intervals.
// Merge them to get a new sorted non intersecting array/list. 
// 
// Eg: 
// Given: 
// Arr1 = [3-11, 17-25, 58-73]; 
// Arr2 = [6-18, 40-47]; 
// 
// Wanted: 
// Arr3 = [3-25, 40-47, 58-73];

#include <vector>
#include <utility>
#include <iostream>

namespace
{
  using Interval = std::pair<int, int>;
  using IntervalList = std::vector<Interval>;

  IntervalList mergeIntervals(const IntervalList& list1, const IntervalList& list2)
  {
    const size_t count1 = list1.size(),
                 count2 = list2.size();

    size_t it1 = 0, it2 = 0;

    size_t* leftIt = nullptr;
    size_t* rightIt = nullptr;

    const IntervalList* leftList = nullptr;
    const IntervalList* rightList = nullptr;

    bool newInterval = true;
    int newLeft;

    IntervalList outcome;

    while(it1 < count1 && it2 < count2)
    {
      if(list1[it1].first <= list2[it2].first)
      {
        leftIt = &it1;
        leftList = &list1;

        rightIt = &it2;
        rightList = &list2;
      }
      else
      {
        leftIt = &it2;
        leftList = &list2;

        rightIt = &it1;
        rightList = &list1;
      }

      if(newInterval)
      {
        newLeft = (*leftList)[*leftIt].first;
        newInterval = false;
      }

      if((*leftList)[*leftIt].second < (*rightList)[*rightIt].first)
      {
        // No intersection
        outcome.push_back(std::make_pair(newLeft, (*leftList)[*leftIt].second));
        newInterval = true;
        ++(*leftIt);
      }
      else if((*leftList)[*leftIt].second >= (*rightList)[*rightIt].second)
      {
        ++(*rightIt);
      }
      else
      {
        ++(*leftIt);
      }
    }

    while(it1 < count1)
    {
      outcome.push_back(list1[it1]);
      ++it1;
    }

    while(it2 < count2)
    {
      outcome.push_back(list2[it2]);
      ++it2;
    }

    return outcome;
  }

}

int main(int argc, char* argv[])
{
  IntervalList list1 = {{3, 11}, {17, 25}, {58, 73}},
               list2 = {{6, 18}, {40, 47}};

  IntervalList list = mergeIntervals(list1, list2);

  for(const auto& i : list)
  {
    std::cerr << "[" << i.first << "-" << i.second << "] "; 
  }

  std::cerr << std::endl;
}

