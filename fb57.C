// Pb:
// ---
// 
// Write a program that reverses a linked list without using more than O(1) storage.
//

#include <iostream>

namespace
{
  struct Node
  {
    char  value_;
    Node* next_;

    Node(char v, Node* n) : value_(v), next_(n) {}
  };

  Node* reverse(Node* head)
  {
    if(!head)
    {
      return nullptr;
    }

    Node* current = head;
    Node* prev = nullptr;

    while(current && current->next_)
    {
      Node* tmp = current;
      Node* next = current->next_;
      current = next->next_;

      next->next_ = tmp;

      tmp->next_ = prev;

      prev = next;
    }

    if(current)
    {
      current->next_ = prev;
      return current;
    }
    else
    {
      return prev;
    }
  }
}

int main(int argc, char* argv[])
{
  Node* d = new Node('D', nullptr);
  Node* c = new Node('C', d);
  Node* b = new Node('B', c);
  Node* a = new Node('A', b);

  Node* r = reverse(a);

  while(r)
  {
    std::cerr << r->value_ << " -> ";
    r = r->next_;
  }

  std::cerr << "|||" << std::endl;
  return 0;
}


