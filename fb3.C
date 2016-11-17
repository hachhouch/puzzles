// Select Kth largest value in the array. Given an unsorted array of size n, and a value k. Select the kth largest value from the array. 
// 
// For example: 
// 
// Array is [5, 3, 9, 1], n is 4 
// k = 0 => 9 
// k = 1 => 5 
// k = 3 => 1
// 
// 
// public int kthLargest(int array[], int k) {
// // ..... 
// }

#include <vector>
#include <iostream>
#include <sstream>

namespace
{
  template<class T>
  void swap(std::vector<T>& arr, size_t i, size_t j)
  {
    T tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }

  size_t partition(std::vector<int>& arr, size_t start, size_t end)
  {
    size_t lo = start, hi = end+1;
    int p = arr[start];

    while(true)
    {
      while(lo < hi && arr[--hi] < p);
      while(lo < hi && arr[++lo] > p);

      if(lo >= hi)
      {
        break;  
      }

      swap(arr, lo, hi);
    }

    swap(arr, start, hi);
    return lo;
  }

  std::pair<bool, int> kthLargest(std::vector<int>& arr, size_t k)
  {
    size_t count = arr.size();

    if(count == 0 || count <= k)
    {
      return std::make_pair(false, -1);
    }

    size_t lo = 0, hi = arr.size()-1;

    while(lo < hi)
    {
      size_t p = partition(arr, lo, hi);

      if(p == k)
      {
        return std::make_pair(true, arr[p]);
      }
      else if(p < k)
      {
        lo = p+1;
      }
      else
      {
        hi = p-1;
      }
    }

    return std::make_pair(true, arr[lo]);
  }
}

int main(int argc, char* argv[])
{
  std::cerr << "Enter int array: ";
  std::string tmp;
  std::getline(std::cin, tmp);
  std::istringstream iss(tmp);

  int cur;
  std::vector<int> arr;

  while(iss >> cur)
  {
    arr.push_back(cur);
  }

  std::cerr << "Enter k: ";
  size_t k;
  std::cin >> k;

  std::pair<bool, int> p = kthLargest(arr, k);
  std::cerr << k << "th largest element ";

  if(p.first)
  {
    std::cerr << "is " << p.second << ".";
  }
  else
  {
    std::cerr << "not found."; 
  }

  std::cerr << std::endl;
  return 0;
}

