// The Problem:
// ------------
//
// Given the root of a binary tree containing integers, print the columns of the tree in order with
// the nodes in each column printed top-to-bottom.
// 
// 
// Input:
//       6
//      / \
//     3   4
//    / \   \
//   5   1   0
//  / \     /
// 9   2   8
//      \
//       7
// 
// Output:
// 9 5 3 2 6 1 7 4 8 0
// 
// Input:
//        1
//      /   \
//     2     3
//    / \   / \
//   4   5 6   7
// 
// When two nodes share the same position (e.g. 5 and 6), they may be printed in either order:
// 
// Output:
// 4 2 1 5 6 3 7
// or:
// 4 2 1 6 5 3 7
// 
// The Solution:
// -------------
//
// Traverse root, right, left the tree and each time you go left to hash current element with parent
// hash - 1, and when you go right to hash with parent hash + 1. Then sort the hash keys to get the
// cols in order from left to right.
//
// Complexity = O(nlogn)
//

#include <memory>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

namespace
{
  class Node
  {
    public:

      Node(int value = 0, Node* left = nullptr, Node* right = nullptr) :
       value_(value),
       left_(left),
       right_(right) {}

      void setLeft(Node* left) { left_.reset(left); }
      void setRight(Node* right) { right_.reset(right); }

      Node* getLeft() const { return left_.get(); }
      Node* getRight() const { return right_.get(); }
      int getValue() const { return value_; }

      Node(Node&& rhs) = delete;
      Node& operator=(Node&& rhs) = delete;

    private:

      int value_;
      std::shared_ptr<Node> left_;
      std::shared_ptr<Node> right_;
  };

  using Columns = std::unordered_map<int, std::vector<int> >;

  void printColumns(const Node* const root)
  {
    if(root == nullptr)
    {
      return;
    }

    Columns cols;
    std::queue<std::pair<const Node*, int> > toVisit{};
    toVisit.push(std::make_pair(root, 0));

    while(!toVisit.empty())
    {
      auto cur = toVisit.front();
      toVisit.pop();

      cols[cur.second].push_back(cur.first->getValue());

      if(cur.first->getLeft())
      {
        toVisit.push(std::make_pair(cur.first->getLeft(), cur.second-1));
      }

      if(cur.first->getRight())
      {
        toVisit.push(std::make_pair(cur.first->getRight(), cur.second+1));
      }
    }

    std::vector<int> keys;
    keys.reserve(cols.size());

    for(const auto& c : cols)
    {
      keys.push_back(c.first);
    }

    std::sort(keys.begin(), keys.end());

    for(const auto& k : keys)
    {
      //std::cerr << std::endl << "printing column " << k << std::endl;

      for(const auto& n : cols[k])
      {
        std::cout << " " << n;
      }
    }

    std::cerr << std::endl;
  }
}

int main(int argc, char* argv[])
{
  // Example 1:

  Node* right = new Node(7);
  right = new Node(2, nullptr, right);
  
  Node* left = new Node(9);
  left = new Node(5, left, right);

  right = new Node(1);
  left = new Node(3, left, right);

  std::shared_ptr<Node> root(new Node(6, left, nullptr));

  left = new Node(8);
  right = new Node(0, left);
  right = new Node(4, nullptr, right);

  root->setRight(right);

  std::cerr << "Example1:" << std::endl;
  printColumns(root.get());

  // Example 2:

  left = new Node(4);
  right = new Node(5);
  left = new Node(2, left, right);

  root.reset(new Node(1, left));

  left = new Node(6);
  right = new Node(7);
  right = new Node(3, left, right);

  root->setRight(right);

  std::cerr << "Example 2:" << std::endl;
  printColumns(root.get());

  return 0;
}

