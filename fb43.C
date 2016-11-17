// Pb:
// ---
// 
// Given a singly linked list, swap the list items in pairs (reconnect the
// pointers, not simply swap the values). For example: 
// 
// Before: A->B->C->D 
// After: B->A->D->C
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

  Node* swap(Node* head)
  {
    Node* cur = head;
    Node* prev = nullptr;

    while(cur && cur->next_)
    {
      Node* tmp = cur;
      cur = cur->next_->next_;
      Node* next = tmp->next_;

      tmp->next_ = next->next_;
      next->next_ = tmp;

      if(prev == nullptr)
      {
        head = next;
      }
      else
      {
        prev->next_ = next;
      }
     
      prev = tmp;
    }

    return head;
  }
}

int main(int argc, char* argv[])
{
  Node* d = new Node('D', nullptr);
  Node* c = new Node('C', d);
  Node* b = new Node('B', c);
  Node* a = new Node('A', b);

  Node* head = a;
  head = swap(head);

  while(head)
  {
    std::cerr << head->value_ << ",";
    head = head->next_;
  }

  return 0;
}

