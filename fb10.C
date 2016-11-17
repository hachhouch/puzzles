// Pb:
// ---
//
// Given a forest of balanced binary trees and two nodes, n1 and n2, find the closest common parent of
// n1 and n2. Nodes have parameters "parent", "left" and "right", and you cannot access the values of 
// the nodes. If n1 and n2 are not on the same tree, return NULL. 
//
// Try to do this in O(log(n)) time and O(1) space.
//
// Solution:
// ---------
//
// 1. For both n1 and n2, count the number of nodes on their paths till the root. Let them be c1
//    and c2.
// 2. Suppose c1 > c2.
// 3. Traverse the parent/ancestor nodes of n1 for (c1-c2) steps till we reach some ancestor a1. 
// 4. Compare a1 and n2. If (a1 == n2) return n2; else go to step 5
// 5. Traverse the parents/ancestors of a1 and n2 till either you find same ancestors or reach the
//     roots (and beyond)

#include <iostream>

namespace
{
  struct Node
  {
    Node* parent;
    Node* left;
    Node* right;
  };

  Node* getRootAndHeight(Node* n, size_t& h)
  {
    Node* root = n;
    h = 0;

    while(root && root->parent)
    {
      root = root->parent;
      ++h;
    }

    return root;
  }

  Node* getAncestor(Node* n, size_t count)
  {
    for(size_t i = count; i > 0 && n; --i)
    {
      n = n->parent;
    }

    return n;
  }

  Node* getClosestCommon(Node* n1, Node* n2)
  {
    // Compute the root and height of node 1
    size_t h1 = 0;
    Node* root1 = getRootAndHeight(n1, h1);

    // Compute the root and height of node 2
    size_t h2 = 0;
    Node* root2 = getRootAndHeight(n2, h2);

    if(root1 != root2)
    {
      return nullptr;
    }

    if(h1 > h2)
    {
      n1 = getAncestor(n1, h1-h2);
    }
    else if(h2 > h1)
    {
      n2 = getAncestor(n2, h2-h1);
    }

    root1 = n1;
    root2 = n2;

    while(root1 && (root1 == root2))
    {
      root1 = root1->parent;
      root2 = root2->parent;
    }

    return root1;
  }
}

int main(int argc, char* argv[])
{

}

