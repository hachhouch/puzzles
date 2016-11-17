// Pb:
// ----
// 
// Find the in-order successor of a node in BST
// 

#include <iostream>

namespace
{
  struct Node
  {
    int   value_;
    Node* left_;
    Node* right_;
    Node* parent_;

    Node(int value, Node* l, Node* r, Node* p) :
     value_(value),
     left_(l),
     right_(r),
     parent_(p) {}
  };

  Node* getMin(Node* n)
  {
    while(n->left_)
    {
      n = n->left_;
    }

    return n;
  }

  Node* getSuccessor(Node* n)
  {
    if(n->right_ != nullptr)
    {
      return getMin(n->right_);
    }
    else
    {
      while(n->parent_ && n->parent_->right_ == n)
      {
        n = n->parent_;
      }

      if(n->parent_ == nullptr)
      {
        return nullptr;
      }
      else
      {
        return n->parent_;
      }
    }
  }
}

int main(int argc, char* argv[])
{
  Node* one = new Node(1, nullptr, nullptr, nullptr);   
  Node* three = new Node(3, nullptr, nullptr, nullptr);   
  Node* two = new Node(2, one, three, nullptr);
  one->parent_ = two;
  three->parent_ = two;

  Node* five = new Node(5, nullptr, nullptr, nullptr);   
  Node* seven = new Node(7, nullptr, nullptr, nullptr);   
  Node* six = new Node(6, five, seven, nullptr);   
  five->parent_ = six;
  seven->parent_ = six;

  Node* four = new Node(4, two, six, nullptr);   
  two->parent_ = four;
  six->parent_ = four;

  Node* nine = new Node(9, nullptr, nullptr, nullptr);   
  Node* eight = new Node(8, four, nine, nullptr);   
  nine->parent_ = eight;
  four->parent_ = eight;

  Node* n = seven;
  Node* tmp = getSuccessor(n);
  std::cerr << "Succ of " << n->value_ << " = " << (tmp ? tmp->value_ : 0) << std::endl; 
  return 0;
}

