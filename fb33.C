// Pb:
// 
// check a binary tree is a binary search tree
// 

#include <limits>
#include <iostream>

namespace
{
  struct Node
  {
    int   value_;
    Node* left_;
    Node* right_;
  
    Node(int value, Node* left, Node* right) :
      value_(value),
      left_(left),
      right_(right)
    {}
  };

  struct BSTDesc
  {
    bool isValid_;
    int  min_;
    int  max_;

    BSTDesc(bool valid, int min, int max) : isValid_(valid), min_(min), max_(max) {}
    
    BSTDesc() :
      isValid_(true),
      min_(std::numeric_limits<int>::max()),
      max_(std::numeric_limits<int>::min())
    {}
  };

  BSTDesc isValid(const Node* n)
  {
    BSTDesc d;

    if(!n)
    {
      return d;
    }

    if(n->left_)
    {
      BSTDesc l = isValid(n->left_);

      if(!l.isValid_ || l.max_ > n->value_)
      {
        d.isValid_ = false;
        return d;
      }

      d.min_ = l.min_;
    }
    else
    {
      d.min_ = n->value_;
    }

    if(n->right_)
    {
      BSTDesc r = isValid(n->right_);

      if(!r.isValid_ || r.min_ < n->value_)
      {
        d.isValid_ = false;
        return d;
      }

      d.max_ = r.max_;
    }
    else
    {
      d.max_ = n->value_;
    }

    return d;
  } 
}

int main(int argc, char* argv[])
{
  Node* l = new Node(3, nullptr, nullptr);
  Node* r = new Node(8, nullptr, nullptr);
  Node* root = new Node(5, l, r);

  BSTDesc d = isValid(root);
  std::cerr << "isValid() returned " << std::boolalpha << d.isValid_ << std::endl;
  return 0;
}
