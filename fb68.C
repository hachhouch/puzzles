// Pb:
// ---
// 
// Given a Tree:
//    A
//    /\
//   B  C
//  /\  /\
//  D E F G
// Write a function that prints: 
// A 
// BC 
// DEFG
// 

#include <queue>
#include <utility>
#include <iostream>

using std::pair;
using std::make_pair;
using std::queue;

namespace
{
  struct Node
  {
    char  value_;
    Node* left_;
    Node* right_;

    Node(char v, Node* l, Node* r) : value_{v}, left_{l}, right_{r} {}
  };

  using Item = pair<Node*, size_t>;

  void print(Node* root)
  {
    queue<Item> q;

    q.push(make_pair(root, 0));
    size_t d = 0;

    while(!q.empty())
    {
      auto i = q.front();
      q.pop();

      if(i.second > d)
      {
        std::cerr << std::endl;
        d = i.second;
      }

      std::cerr << i.first->value_;
     
      if(i.first->left_)
      {
        q.push(make_pair(i.first->left_, i.second+1));
      }

      if(i.first->right_)
      {
        q.push(make_pair(i.first->right_, i.second+1));
      }
    }

    std::cerr << std::endl;
  }
}

int main(int argc, char* argv[])
{
  Node* d = new Node('D', nullptr, nullptr);
  Node* e = new Node('E', nullptr, nullptr);
  Node* f = new Node('F', nullptr, nullptr);
  Node* g = new Node('G', nullptr, nullptr);
  Node* b = new Node('B', d, e);
  Node* c = new Node('C', f, g);
  Node* a = new Node('A', b, c);

  print(a);
  return 0;
}

