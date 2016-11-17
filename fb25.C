// Given Nodes such as
// 
// 
// M->       N->       T->       D->       E
// |         |         |          |	
// C         X         Y          L
// |         |
// A         Z
//
// -> right pointer 
// | down pointer 
//
// Output should be 
// M->C->A->N->X->Z->T->Y->D-L>E 
// 
// Write this to flatten 
//
// flatten(Node head) { 
// 
// } 
// 
// Node { 
//   Node right; 
//   Node down; 
//   char a; 
// }

#include <iostream>
#include <assert.h>

namespace
{
  struct Node
  {
    char  a_;
    Node* down_;
    Node* right_;

    Node(char a, Node* down, Node* right) : a_(a), down_(down), right_(right) {} 
  };

  void flatten(Node* head)
  {
    Node* horIt = head;

    while(horIt != nullptr)
    {
      Node* vertIt = horIt;
      Node* preVert = nullptr;
      
      horIt = horIt->right_;

      while(vertIt)
      {
        preVert = vertIt;
        vertIt = vertIt->down_;
        preVert->right_ = preVert->down_;
        preVert->down_ = nullptr;
      }

      preVert->right_ = horIt;
    }
  }
}

int main(int argc, char* argv[])
{
  Node* e = new Node('E', nullptr, nullptr);
  Node* l = new Node('L', nullptr, nullptr);
  Node* d = new Node('D', l, e);
  Node* y = new Node('Y', nullptr, nullptr);
  Node* t = new Node('T', y, d);
  Node* z = new Node('Z', nullptr, nullptr);
  Node* x = new Node('X', z, nullptr);
  Node* n = new Node('N', x, t);
  Node* a = new Node('A', nullptr, nullptr);
  Node* c = new Node('C', a, nullptr);
  Node* head = new Node('M', c, n);

  flatten(head);

  while(head)
  {
    std::cerr << head->a_ << " -> ";
    assert(head->down_ == nullptr);
    head = head->right_;
  }

  std::cerr << std::endl;
  return 0;
}

