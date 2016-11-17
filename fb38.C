// Search in a sorted rotated array.

#include <iostream>

namespace
{
  void binarySearch(int* a, size_t size, size_t start, int value)
  {
    size_t l = start;
    size_t r = size-1+start;

    while(l<=r)
    {

      size_t mid = l + ((r-l)/2);

      if(a[mid%size] == value)
      {
        std::cerr << "Found it." << std::endl;
        return;
      }
      else if(a[mid%size] < value)
      {
        l = mid+1;
      }
      else
      {
        r = mid-1;
      }
    }

    std::cerr << "NOT FOOUND !!!!" << std::endl;
  }
}

int main(int argc, char* argv[])
{
  int a[] = {7, 9, 12, 23, 2, 5, 6};
  const size_t size = sizeof(a)/sizeof(int);

  binarySearch(a, size, 4, 8);
  return 0;
}


