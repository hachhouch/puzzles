// Question:
// ---------
// 
// There are N coins with coordinates (x, y) where x >0 and y >0 
// You start at (0, 0) and you can only do steps of form (dx, dy) where dx >0 and dy > 0 
// Print the maximum number of coins that you can collect. 
// 
// Wrong Answer:
// -------------
// 
// LIS.(Longest increasing subsequence , in this case strictly increasing).
// Sort/order points in x dimension. Find LIS wrt to "y" dimension.
// Similarly sort/order points in Y dimension. Find LIS wrt to x "dimension"
// Pick max LIS out of the two.
// Time complexity ~ O(nlgn) ... That is nlgn for sorting. nlgn for LIS
// 
// ==> Suppose there are points (5, 7), (5, 8), (5, 9) for y coordinates LIS will output 7, 8, 9,
//     however since these points are on the same x axis, you can choose only one of them.
// 
// Good answer:
// ------------
// 
// I can't believe i didn't realize it when posting my solution or reading the other comments, but this
// problem (and my previous solution) is essentially the LIS problem. Basically you can just sort all the
// locations of the coins primarily according to y-axis in ascending order and secondarily according to x-axis
// in descending order, and run the nlogn LIS algorithm. The secondary sorting by x-axis into a descending
// order guarantees that the ties you mentioned will be taken into account properly.

#include <vector>
#include <stack>
#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <functional>

namespace
{
  using Coin = std::pair<int,int>;

  struct CoinHasher
  {
    std::size_t operator()(const Coin& p) const
    {
      return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
  };

  using Coins = std::vector<Coin>;
  using Dict = std::map<int, std::set<int,std::greater<int>, std::allocator<int> > >;
  using CoinStack = std::stack<Coin>;
  using CoinHash = std::unordered_map<Coin, Coin, CoinHasher>;

  size_t binarySearch(Coins& m, int y, int end)
  {
    size_t lo = 1, hi = end;

    while(lo <= hi)
    {
      size_t mid = (hi+lo)/2;

      if(m[mid].second < y)
      {
        lo = mid+1;
      }
      else
      {
        hi = mid-1;
      }
    }

    return lo;
  }

  void solve(const Coins& l)
  {
    // S1: construct the x-based map

    Dict d;

    for(const auto& c : l)
    {
      d[c.first].insert(c.second);
    }

    // S2: find y-based LIS

    std::vector<Coin> m;
    m.resize(l.size()+1);

    CoinHash pred;

    size_t lis = 0;

    for(const auto& p : d)
    {
      for(const auto& y : p.second)
      {
        size_t i = binarySearch(m, y, lis);
        Coin c = std::make_pair(p.first, y);
       
        //std::cerr << "m[" << i <<  "] = (" << c.first << "," << c.second  <<  ")" << std::endl;  
        m[i] = c;

        if(i > 1)
        {
          pred[c] = m[i-1];
          //std::cerr << "p[(" << c.first << "," << c.second << ")] = "
          //          << "(" << pred[c].first << "," << pred[c].second << ")" << std::endl;
        }

        if(i > lis)
        {
          lis = i;
        }
      }
    }

    // S3: output the solution

    CoinStack s;
    s.push(m[lis]);
    CoinHash::iterator p = pred.find(m[lis]);

    while(p != pred.end())
    {
      s.push(p->second);
      p = pred.find(p->second);
    }

    std::cerr << "Solution is: ";

    while(!s.empty())
    {
      auto& c = s.top();
      std::cerr << "(" << c.first << "," << c.second << ") ";
      s.pop();
    }

    std::cerr << std::endl;
  }
}

int main(int argc, char* argv[])
{
  //Coins c = { {5,7}, {5,8}, {5,9} };

  Coins c = { {1,10}, {2,2}, {3,8}, {3,3}, {10,4}, {20,6}, {30, 1}};

  solve(c);
  return 0;
}

