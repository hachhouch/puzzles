// Given an array of integers. Modify the array by moving all the zeros to the
// end (right side). The order of the other elements doesn't matter.

#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;

namespace
{
  void shiftRight(vector<int>& arr, const int val)
  {
    const size_t count = arr.size();

    // find the end of the trailing consecutive 0s.

    size_t pos = count;

    while(pos > 0 && arr[pos-1] == val)
    {
      --pos;
    }

    for(size_t i = pos; i > 0; --i)
    {
      if(arr[i-1] == val)
      {
        int tmp = arr[pos-1];
        arr[pos-1] = arr[i-1];
        arr[i-1] = tmp;
        --pos;
      }
    }
  }
}

int main(int argc, char* argv[])
{
  std::cout << "Enter numbers: ";
  vector<int> arr;
  int val;

  while(std::cin >> val)
  {
    arr.push_back(val);
  }

  shiftRight(arr, 0);

  std::cout << "Shifted: ";
  std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout));
  std::cout << std::endl;
}

