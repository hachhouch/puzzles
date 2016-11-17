// Pb:
// ---
// 
// You are given a permutation arr[N]. E.g. arr[3] = {2, 1, 0} or arr[5] = {0,1,2,4,3}; 
// Then you can prepare somehow and then start serving requests: 
// request(a, b, k) = sorted(arr[a:b])[k], that is, k-th order statistic on slice [a:b]
// of arr. E.g. if arr is [3,4,5,0,1,2] and a = 2 and b = 5, then arr[a:b] = [5,0,1] and
// let k = 2, so we sort it - get [0,1,5] and take k-th element, that is - 5. 
// 
// Implement request(a, b, k) function. You can preprocess input data, that is, assume
// there will be only one array and many request() calls.
// 
// Sol 1 (fast but heavy memory footprint):
// ----------------------------------------
// 
// Matrix of sorted ranges.
// 
// Sol 2 (slower but less memory usage):
// -------------------------------------
// 
// Create an array indexArray that contains, for each index i, the position at which i 
// occurs. E.g. if our initial permutation is {3 4 2 5 1 0}, indexArray becomes 
// {5 4 2 0 1 3} (i.e., 0 is at position 5 thus indexArray[0] = 5, etcetera).
// 
// Now suppose we need the k-th order statistic of a range [begin, end]. We now iterate
// through indexArray, and each time we encounter a value within the range [begin, end],
// the index tells us which number is there. Moreover, the order in which we encounter 
// these numbers, is sorted! Thus, if we need the 2nd order statistic of the range [1,4]
// (i.e. the sub array {4 2 5 1} we go through indexArray. The first number that is
// within that range is 4, which is at position 2 (the 0th order statistic). The second
// we encounter is 2, which is at position 2 (the 1st order statistic). The third we 
// encounter is 1, which is at position 4 (the 2nd order statistic). 
// 
// Preprocessing time is N. Query time is also N. No need to sort, create trees, hash 
// maps or whatever else was suggested.
// 
// Crucial here is that the input array is a permutation, and not an array containing
// arbitrary values!
// 

#include <vector>
#include <iostream>

using std::vector;

namespace
{
  using Sorted = vector<int>;
  using Matrix = vector<vector<Sorted>>;
}

int main(int argc, char* argv[])
{
  vector<int> a{3, 4, 5, 0, 1, 2};

  const size_t n = a.size();

  Matrix m(n);

  for(size_t i = 0; i < n; ++i)
  {
    m[i].resize(n);

    for(size_t j = i; j < n; ++j)
    {
      m[i][j].resize(j-i);

      for(size_t k = 0; k < (j-i); ++k)
      {
        m[i][j][k] = a[i+k];
      }

      std::sort(m[i][j].begin(), m[i][j].end());
    }
  }

  std::cerr << m[2][5][2] << std::endl;
  return 0;
}


