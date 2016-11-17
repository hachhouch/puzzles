// Pb:
// ---
// 
// Given an array such that every next element differs from the previous by +/- 1.
// (i.e. a[i+1] = a[i] +/-1 ) Find the local max OR min in O(1) time.
// The interviewer mentioned one more condition that the min or max should be
// non-edge elements of the array 
// 
// Example: 1 2 3 4 5 4 3 2 1 -> Local max is 5 
// 1 2 3 4 5 -> No local max or min exists 
// 5 4 3 2 1 -> No local max or min exists
// 
// Sol:
// ----
// 
// A[0] +/- (A[ A.length -1 ] + A.length - A[0])/2
//

#include <iostream>

int main(int argc, char* argv[])
{
  //int a[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
  int a[] = {1, 0, -1, 0, 1, 2, 3, 4, 5};
  const size_t count = sizeof(a)/sizeof(int);

  size_t i = (a[count-1]-a[0])/2;
  bool isMin = a[0] > a[1];
  std::cerr << (isMin ? a[count/2 - i] : a[count/2 + i]) << std::endl;

  return 0;
}

