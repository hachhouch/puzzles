// Given an array of positive integers and a target total of X, find if there exists a contiguous subarray with sum = X 
// 
// [1, 3, 5, 18] X = 8 Output: True 
// X = 9 Output: True 
// X = 10 Output: False 
// X = 40 Output :False

#include <vector>
#include <iostream>

namespace
{
  bool hasInterval(const std::vector<size_t>& arr, size_t target)
  {
    const auto count = arr.size();
    auto j = 0, sum = 0;

    for(auto i = 0; i < count; ++i)
    {
      sum += arr[i];

      if(sum == target)
      {
        return true;
      }

      while(sum > target && j <= i)
      {
        sum -= arr[j];
      
        if(sum == target)
        {
          return true;
        }

        ++j;
      }
    }

    return false;
  }
};

int main(int argc, char* argv[])
{
  std::vector<size_t> arr = {1, 3, 5, 18};
  
  std::cerr << hasInterval(arr, 8) << std::endl;
  std::cerr << hasInterval(arr, 9) << std::endl;
  std::cerr << hasInterval(arr, 10) << std::endl;
  std::cerr << hasInterval(arr, 40) << std::endl;
}


