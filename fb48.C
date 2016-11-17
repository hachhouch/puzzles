// Pb:
// ---
// 
// Sort an integer array with three functions: findMin(), findMedium(), findMax().
// 
// Sol:
// ----
// 
// QuickSort with findMedium to find the pivot. Use findMax on left side of pivot
// and findMin on right side of pivot until findMax > pivot and findMin < pivot
// 

#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;

namespace
{
  size_t findMin(const vector<int>& v, size_t start, size_t end)
  {
    size_t min = start;

    for(size_t i = start+1; i <= end; ++i)
    {
      if(v[i] < v[min])
      {
        min = i;
      }
    }

    return min;
  }

  size_t findMax(const vector<int>& v, size_t start, size_t end)
  {
    size_t max = start;

    for(size_t i = start+1; i <= end; ++i)
    {
      if(v[i] > v[max])
      {
        max = i;
      }
    }

    return max;
  }

  size_t findMid(const vector<int> v, size_t start, size_t end)
  {
    vector<int> tmp;

    for(size_t i = start; i <= end; ++i)
    {
      tmp.push_back(v[i]);
    }

    std::sort(tmp.begin(), tmp.end());
    size_t mid = start + (end - start)/2;

    int m = tmp[mid];

    for(size_t i = start; i <= end; ++i)
    {
      if(v[i] == m)
      {
        return i;
      }
    }

    return mid;
  }

  void swap(vector<int>& v, size_t i, size_t j)
  {
    if(i < j)
    {
      int tmp = v[i];
      v[i] = v[j];
      v[j] = tmp;
    }
  }

  void quickSort(vector<int>& v, size_t i, size_t j)
  {
    if(i >= j)
    {
      return;
    }

    size_t mid = findMid(v, i, j);

    int pivot = v[mid];
    int leftSwap = -1, rightSwap = -1;

    while(true)
    {
      if(mid > i)
      {
        size_t max = findMax(v, i, mid-1);

        if(v[max] > pivot)
        {
          leftSwap = max;
        }
      }

      if(mid < j)
      {
        size_t min = findMin(v, mid+1, j);

        if(v[min] < pivot)
        {
          rightSwap = min;
        }
      }

      if(leftSwap == -1)
      {
        if(rightSwap == -1)
        {
          break;
        }
        else
        {
          if(rightSwap > mid+1)
          {
            swap(v, mid, mid+1);
            ++mid;
            swap(v, mid-1, rightSwap);
          }
          else
          {
            swap(v, mid, rightSwap);
            ++mid;
          }
        }
      }
      else if(rightSwap != -1)
      {
        swap(v, leftSwap, rightSwap);
      }
      else
      {
        if(leftSwap < mid-1)
        {
          swap(v, mid, mid-1);
          --mid;
          swap(v, leftSwap, mid+1);
        }
        else
        {
          swap(v, leftSwap, mid);
          --mid;
        }
      }

      leftSwap = -1;
      rightSwap = -1;
    }

    quickSort(v, mid+1, j);
    quickSort(v, i, mid-1);
  }

  void fbSort(vector<int>& v)
  {
    quickSort(v, 0, v.size()-1);
  }
}

int main(int argc, char* argv[])
{
  vector<int> v = { 14, 1, 2, 2015, 1937, 16, 11, 73};

  fbSort(v);

  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cerr, ","));
  std::cerr << std::endl;

  return 0;
}

