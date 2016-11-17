// Given predicted stock prices for next n days for a stock e.g : 10, 30, 42, 15, 20, 50, 10, 25 find
// the maximum profit that can be made with a single buy-sell transaction. If no profit can be made
// return 0. In the example buying at 15 and selling at 50 gives maximum profit. Note that the two
// prices are neither minimum nor maximum in the array.

#include <vector>
#include <iostream>

using std::vector;

namespace
{
  int findMax(const vector<int>& prices)
  {
    if(prices.empty())
    {
      return 0;
    }

    int bestMin = prices[0],
        bestMax = prices[0],
        currentMin = prices[0],
        currentMax = prices[0];

    const size_t count = prices.size();

    for(size_t i = 1; i < count; ++i)
    {
      if(prices[i] < currentMin)
      {
        currentMin = prices[i];
        currentMax = prices[i];
      }

      if(prices[i] > currentMax)
      {
        currentMax = prices[i];

        if((currentMax - currentMin) > (bestMax - bestMin))
        {
          bestMin = currentMin;
          bestMax = currentMax;
        }

      }
    }

    return bestMax - bestMin;
  }
}

int main(int argc, char* argv[])
{
  vector<int> prices{100, 30, 42, 15, 20, 50, 10, 25};
  std::cerr << findMax(prices) << std::endl;
  return 0;
}


