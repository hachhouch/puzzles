// §Having a home-defined linked list with the following structure, where
// the next will point to the next node in the list and the random will
// point to a random node in the list (not null). 
// Create a copy of the structure (the data field in each node is not
// unique for different nodes): 
// 
// /* 
// Example: 
// Having the list: 
// 1 -> 2 -> 3 -> X 
// With random pointers to: 
// 1: 3 
// 2: 2 
// 3: 1 
// 
// Create the list: 
// 1' -> 2' -> 3' -> X 
// 1': 3' 
// 2': 2' 
// 3': 1' 
// */ 
// 
// class Node { 
//   int data; 
//   Node next; 
//   Node random; 
// }
// 

#include <iostream>

namespace
{
  struct Node
  { 
    int data;
    Node* next;
    Node* random;

    Node(int d, Node* n, Node* r) : data{d}, next{n}, random{r} {}
  };

  Node* clone(Node* n)
  {
    if(!n)
    {
      return nullptr;
    }

    Node* current = n;

    while(current)
    {
      std::cerr << "a) Processing " << current->data << std::endl;

      Node* next = current->next;
      current->next = new Node(current->data*2, next, nullptr);
      current = next; 
    }

    current = n;

    Node* dup = n->next;

    while(current)
    {
      std::cerr << "b) Processing " << current->data << std::endl;
      current->next->random = current->random->next;
      Node* tmp = current->next;
      current->next = current->next->next;
      tmp->next = tmp->next ? tmp->next->next : nullptr;;
      current = current->next;
    }

    return dup;
  }
}

int main(int argc, char* argv[])
{
  Node* three = new Node(3, nullptr, nullptr);
  Node* two = new Node(2, three, nullptr);
  Node* one = new Node(1, two, nullptr);

  one->random = three;
  three->random = one;
  two->random = two;

  Node* d = clone(one);

  while(d)
  {
    std::cerr << d->data 
              << " n: " << (d->next ? d->next->data : 0) << " r: " << d->random->data << std::endl;
    d = d->next;
  }

  return 0;
}

