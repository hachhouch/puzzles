// Q:
// 
// You have an array of unique integer numbers and only one operation: 
// MoveToFront(x) that moves given number to the beginning of the array. 
// Write a program to sort the array using the minimum possible number
// of MoveToFront() calls.
// 
// S1:
// 
// Selection sort
//
// S2:
//
// 1. Find the largest number (I called it A) from the array and remember
//    its index.
// 2. Find the next largest number (I called it B) from the array. If B
//    comes before A, we're good, otherwise move B to the front,
//    MoveToFront(B). 
// 3. A = B, and repeat (2). it needs to loop n-2 times to check all 
//    other numbers.

#include <iostream>
#include <algorithm>

namespace
{
  size_t counter = 0;

  void moveToFront(int* arr, size_t i)
  {
    ++counter;

    int tmp = arr[i];

    for(size_t j = i; j > 0; --j)
    {
      arr[j] = arr[j-1];
    }

    arr[0] = tmp;
  }

  void selectionSort(int* arr, size_t count)
  {
    for(size_t i = 0; i < count; ++i)
    {
      size_t max = i;

      for(size_t j = i+1; j < count; ++j)
      {
        if(arr[j] > arr[max])
        {
          max = j;
        }
      }

      moveToFront(arr, max);
    }

    return;
  }

  size_t findMax(int* arr, size_t count, size_t limit)
  {
    size_t max = 0;

    while(arr[max] >= arr[limit])
    {
      ++max;
    }

    for(size_t i = 0; i < count; ++i)
    {
      if(arr[i] > arr[max] && (limit >= count || arr[i] < arr[limit]))
      {
        max = i;
      }
    }

    return max;
  }

  void sort2(int* arr, size_t count)
  {
    size_t A = findMax(arr, count, count);

    for(size_t i = 0; i < count-1; ++i)
    {
      size_t B = findMax(arr, count, A);

      if(A < B)
      {
        moveToFront(arr, B);
        A = 0;
      }
      else
      {
        A = B;
      }
    }
  }
}

int main(int argc, char* argv[])
{
  int arr[] = {9, 4, 1, 2, 14, 22, 3};
  const size_t count = sizeof(arr)/sizeof(int);

  //selectionSort(arr, count);
  sort2(arr, count);
  
  std::cerr << "MoveToFront called " << counter << std::endl;
  std::copy(arr, arr+count, std::ostream_iterator<int>(std::cout, ","));
  std::cerr << std::endl;

  return 0;
}


