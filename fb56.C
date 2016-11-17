// Pb:
// ---
// 
// Given an m x n matrix where each row element is sorted, but the columns do not appear in
// sorted order, write a function to print each matrix element in sorted order. 
// 
// Example matrix: 
// matrix = [ 
// [20, 40, 80], 
// [5, 60, 90], 
// [45, 50, 55] 
// ] 
// 
// Your function should print 5, 20, 40, 45, 50, 55, 60, 80, 90. 
// 
// Add on: Assume that we are space-constrained such that we can only hold one row in memory
// at a time. Optimize your function to work under such constraints as efficiently as possible.
// 
// Sol:
// ----
// 
// Simple solution: Use MinHeap.
// 
// Add all the elements of first column to the heap and min heapify, print the root, remove and
// put the next from the same row. Repeat.

#include <vector>
#include <queue>
#include <iostream>

using std::vector;
using std::priority_queue;

namespace
{
  using Matrix = vector<vector<int>>;

  struct Item
  {
    int    value_;
    size_t row_;
    size_t col_;

    Item(int v, size_t r, size_t c) : value_(v), row_(r), col_(c) {}
  };

  struct ItemComparor
  {
    bool operator()(const Item& lhs, const Item& rhs)
    {
      return lhs.value_ > rhs.value_;
    }
  };

  bool getElement(const vector<int>& row, size_t col, int& value)
  {
    if(col < row.size())
    {
      value = row[col];
      return true;
    }

    return false;
  }

  using Heap = priority_queue<Item, vector<Item>, ItemComparor>;

  void printMatrix(const Matrix& mat)
  {
    const size_t m = mat.size();

    Heap h;

    for(size_t i = 0; i < m; ++i)
    {
      int e;
      getElement(mat[i], 0, e);
      h.emplace(e, i, 0);
    }

    while(!h.empty())
    {
      auto i = h.top();
      h.pop();

      std::cerr << i.value_ << " ";

      int e;
      
      if(getElement(mat[i.row_], i.col_+1, e))
      {
        h.emplace(e, i.row_, i.col_+1);
      }
    }
  }
}

int main(int argc, char* argv[])
{
  Matrix m = {
    {20, 40, 80}, 
    {5, 60, 90}, 
    {45, 50, 55}
  };

  printMatrix(m);
  return 0;
}

