// Pb:
// ---
//
// Convert a binary tree into a In Order traversal circular list re-purposing
// the node's pointers Left & Right as Previous and Next respectively. 
// 
// Hint: A single node Left & Right points to itself. 
// 
// Note: This is not a binary search tree.
//

#include <utility>
#include <iostream>

using std::pair;
using std::make_pair;

namespace
{
  struct Node
  {
    char value_;
    Node* left_;
    Node* right_;

    Node(char v, Node* l, Node* r) : value_{v}, left_{l}, right_{r} {}
  };

  using NodePair = pair<Node*, Node*>;

  NodePair convert(Node* n)
  {
    std::cerr << "Processing " << n->value_ << std::endl;

    NodePair l = make_pair(nullptr, nullptr);

    Node* right = n->right_;

    if(n->left_)
    {
      l = convert(n->left_);

      // Connect l.second and n
      l.second->right_ = n;
      n->left_ = l.second;

      // Connect n and l.first
      n->right_ = l.first;
      l.first->left_ = n;

      // Extend the 'l' list
      l.second = n;
    }
    else
    {
      l.first = n;
      l.second = n;

      n->left_ = n->right_ = n;
    }

    NodePair r = make_pair(nullptr, nullptr);

    if(right)
    {
      r = convert(right);

      // connect l.second and r.first
      l.second->right_ = r.first;
      r.first->left_ = l.second->right_;

      // Connect r.second and l.first
      r.second->right_ = l.first;
      r.first->left_ = r.second;

      return make_pair(l.first, r.second);
    }
    else
    {
      return l;
    }
  }
}

int main(int argc, char* argv[])
{
  Node* d = new Node('D', nullptr, nullptr);
  Node* e = new Node('E', nullptr, nullptr);
  Node* b = new Node('B', e, d);
  Node* c = new Node('C', nullptr, nullptr);
  Node* a = new Node('A', b, c);

  Node* r = convert(a).first;

  Node* n = r;

  do
  {
    std::cerr << n->value_ << " -> ";
    n = n->right_;
  }
  while(n != r);

  std::cerr << std::endl;
  return 0;
}

