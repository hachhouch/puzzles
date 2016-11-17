// For each node in a binary tree find the next right node on the same depth.
// Write a function that takes root node and populates "next" with the answer
// for each node. 
// 
//       A 
//      / \
//     B -> C 
//    /    / \
//   D -> F-> G 
//  / \
// H -> I 
// 
// class Node { 
// Node left; 
// Node right; 
// Node next; // <-- answer should be stored here 
// }; 
// 
// B.next = C 
// D.next = F 
// F.next = G 
// H.next = I 
// {A, C, G, I}.next = null 

#include <iostream>

namespace
{
  struct Node
  { 
    Node* left; 
    Node* right; 
    Node* next;
    char  value;

    Node(char v, Node* l, Node* r) : left(l), right(r), next(nullptr), value(v) {}
  };
 
  void populateNext(Node* node, Node* parent)
  {
    if(node == nullptr)
    {
      return;
    }

    if(parent == nullptr)
    {
      node->next = nullptr;
    }
    else
    {
      if(parent->left == node && parent->right != nullptr)
      {
        node->next = parent->right;
      }
      else if(parent->next != nullptr)
      {
        node->next = parent->next->left ? parent->next->left : parent->next->right;
      }
      else
      {
        node ->next = nullptr;
      }
    }

    populateNext(node->left, node);
    populateNext(node->right, node);
  }

  void visit(Node* n)
  {
    if(n == nullptr)
    {
      return;
    }

    visit(n->left);
    std::cerr << n->value << "->" << (n->next ? n->next->value : ' ') << std::endl;
    visit(n->right);
  }
}

int main(int argc, char* argv[])
{
  Node* i = new Node('I', nullptr, nullptr);
  Node* h = new Node('H', nullptr, nullptr);
  Node* d = new Node('D', h, i);

  Node* f = new Node('F', nullptr, nullptr);
  Node* g = new Node('G', nullptr, nullptr);
  Node* c = new Node('C', f, g);

  Node* b = new Node('B', d, nullptr);
  Node* a = new Node('A', b, c);

  populateNext(a, nullptr);

  visit(a);

  return 0;
}


