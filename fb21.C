// Given two sorted linked lists of integers write an algorithm to merge the two
// linked lists such that the resulting linked list is in sorted order. You are
// expected to define the data structure for linked list as well. Analyze the
// time and space complexity of the merge algorithm.

#include <iostream>

namespace
{
  struct Node
  {
    int value_;
    Node* next_;
  };

  Node* merge(Node* l1, Node* l2)
  {
    if(l1 == nullptr)
    {
      return l2;
    }
    else if(l2 == nullptr)
    {
      return l1;
    }

    Node* l = nullptr;

    if(l1->value_ < l2->value_)
    {
      l = l1;
      l1 = l1->next_;
    }
    else
    {
      l = l2;
      l2 = l2->next_;
    }

    Node* tmp = l;

    while(l1 && l2)
    {
      std::cerr << l1->value_ << " vs " << l2->value_ << std::endl;

      if(l1->value_ < l2->value_)
      {
        l->next_ = l1;
        l1 = l1->next_;
      }
      else
      {
        l->next_ = l2;
        l2 = l2->next_;
      }

      l = l->next_;
    }

    if(l1 != nullptr)
    {
      l->next_ = l1;
    }
    else if(l2 != nullptr)
    {
      l->next_ = l2;
    }
    else
    {
      l->next_ = nullptr;
    }

    return tmp;
  }

  void insertNode(Node*& l, int v)
  {
    Node* n = new Node();
    n->value_ = v;
    n->next_ = nullptr;

    if(l == nullptr)
    {
      l = n;
    }
    else
    {
      Node* tmp = l;
      while(tmp->next_ != nullptr) tmp = tmp->next_;
      tmp->next_ = n;
    }
  }

  void printList(Node* l)
  {
    while(l)
    { 
      std::cerr << l->value_ << std::endl;
      l = l->next_;
    }
  }
}

int main(int argc, char* argv[])
{
  Node* l1 = nullptr;
  Node* l2 = nullptr;

  insertNode(l1, 1);
  insertNode(l1, 4);
  insertNode(l1, 7);

  printList(l1);

  insertNode(l2, 2);
  insertNode(l2, 5);
  insertNode(l2, 9);

  printList(l2);

  Node* l = merge(l1, l2);

  printList(l);

  return 0;
}

