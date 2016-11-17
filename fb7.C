// Given an array and a number, add it in such a way where array is [0,0,1] and number is 4 output
// will be [0,0,5] 
// 
// Example 2 : 
// array is [1] and number is 9 output will be [1,0]
// 

#include <vector>
#include <iostream>

namespace
{
  void add(std::vector<int>& arr, int n)
  {
    int carry = n;

    const auto count = arr.size();

    for(size_t i = count; i > 0; --i)
    {
      if(carry == 0)
      {
        break;
      }

      size_t j = i-1;
      auto sum = arr[j] + carry;
      arr[j] = sum % 10;
      carry = sum/10;
    }

    while(carry > 0)
    {
      arr.insert(arr.begin(), carry%10);
      carry /= 10;
    }
  }
}

int main(int argc, char* argv[])
{
  std::vector<int> arr{0, 0, 1};
  add(arr, 4);

  for(auto e : arr)
  {
    std::cerr << e << " ";
  }

  std::cerr << std::endl;
}
