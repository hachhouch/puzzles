// Pb:
// ---
// 
// An efficient way to sort patient files in an array of just 3 types
// 'High-importance', 'Mid-importance', 'Low-importance' which are in
// an arbitrary order (unsorted). 
// 
// The output preference should start with the highest. 
// 1. High-importance 
// 2. Mid-importance 
// 3. Low-importance 
// 
// [high,low,low,med,high,low] 
// 
// ps I was told to take advantage of the fact that they are just only 3 types.
// 
// Sol:
// ----
// 
// Partition with equal keys

#include <iostream>

namespace
{
  void swap(char* a, size_t i, size_t j)
  {
    char tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
  }

  void sort(char* a, size_t count)
  {
    size_t i = 0, gt = count+1, lt = 0;

    while(i < gt-1)
    {
      if(a[i] == 'L')
      {
        ++lt;
        swap(a, i, lt-1);
        ++i;
      }
      else if(a[i] == 'H')
      {
        --gt;
        swap(a, i, gt-1);
      }
      else
      {
        ++i;
      }
    } 
  }
}

int main(int argc, char* arv[])
{
  char a[] = {'H', 'L', 'L', 'M', 'H', 'L'};
  const size_t count = sizeof(a)/sizeof(char);
  sort(a, count);

  for(size_t i = 0; i < count; ++i)
  {
    std::cerr << a[i] << " ";
  }

  std::cerr << std::endl;
  return 0;
}

