// We have an array of objects A and an array of indexes B. Reorder objects in array A with given
// indexes in array B. Do not change array A's length. 
// 
// example:
// 
// var A = [C, D, E, F, G];
// var B = [3, 0, 4, 1, 2];
// 
// sort(A, B);
// // A is now [D, F, G, C, E];

#include <vector>
#include <iostream>

namespace
{
  template <class T>
  using ObjectArray = std::vector<T>;
  using IndexArray = std::vector<size_t>;

  template<class T>
  void swap(ObjectArray<T>& A, IndexArray& B, size_t i, size_t j)
  {
    if(i == j)
    {
      return;
    }

    T tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;

    size_t tmp2 = B[i];
    B[i] = B[j];
    B[j] = tmp2; 
  }

  template<class T>
  size_t partition(ObjectArray<T>& A, IndexArray& B, size_t start, size_t end)
  {
    if(A.empty())
    {
      return 0;
    }

    size_t p = start,
           i = start+1,
           j = end;


    while(true)
    {
      while(i < j && B[i] < B[p])
      {
        ++i;
      }

      while(i < j && B[j] > B[p])
      {
        --j;
      }

      if(i < j)
      {
        swap(A, B, i, j);
      }
      else
      {
        break;
      }
    }

    swap(A, B, p, i-1);
    return i-1;
  }

  template<class T>
  void doSort(ObjectArray<T>& A, IndexArray& B, size_t start, size_t end)
  {
    if(start >= end)
    {
      return;
    }

    size_t p = partition(A, B, start, end);

    doSort(A, B, start, p-1);
    doSort(A, B, p+1, end);
  }

  template<class T>
  void sort(ObjectArray<T>& A, IndexArray& B)
  {
    doSort(A, B, 0, A.size()-1);
    return;
  }

  template<class T>
  void reorder(ObjectArray<T>& A, IndexArray& B)
  {
    const size_t count = A.size();
    size_t placed = 0, i = 0;

    while(placed < count)
    {
      if(i != B[i])
      {
        // Swap values
        T tmp = A[i];
        A[i] = A[B[i]];
        A[B[i]] = tmp;

        // Swap indices
        size_t tmp2 = B[B[i]];
        B[B[i]] = B[i];
        B[i] = tmp2;
      }
      else
      {
        ++i;
      }

      ++placed;
    }

    return;
  }
}

int main(int argc, char* argv[])
{
  ObjectArray<char> A = {'C', 'D', 'E', 'F', 'G'};
  IndexArray B = {3, 0, 4, 1, 2};

  std::cerr << "Before" << std::endl;
  std::copy(A.begin(), A.end(), std::ostream_iterator<char>(std::cerr, " "));
  std::cerr << std::endl;

  // Bad solution O(nlogn)
  //sort(A, B);

  // O(n)
  reorder(A, B);

  std::cerr << "After" << std::endl;
  std::copy(A.begin(), A.end(), std::ostream_iterator<char>(std::cerr, " "));
  std::cerr << std::endl;
}

