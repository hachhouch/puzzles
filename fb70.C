// Print a BST such that it looks like a tree (with new lines and indentation, the
// way we see it in algorithms books).

#include <queue>
#include <utility>
#include <unordered_map>
#include <iostream>

using std::queue;
using std::pair;
using std::make_pair;
using std::unordered_map;

namespace
{
  struct Node
  {
    char value_;
    Node* left_;
    Node* right_;

    Node(char v, Node* l, Node* r) : value_{v}, left_{l}, right_{r} {}
  };

  using IndexMap = unordered_map<Node*, size_t>; 
  using NodePos = pair<Node*, size_t>;

  void inorder(Node* n, IndexMap& map, size_t& counter)
  {
    if(n->left_)
    {
      inorder(n->left_, map, counter);
    }

    //std::cerr << n->value_ << " -> " << counter << std::endl;

    map[n] = counter++;

    if(n->right_)
    {
      inorder(n->right_, map, counter);
    }
  }

  void print(Node* n)
  {
    IndexMap index;
    size_t counter = 0;
    inorder(n, index, counter);

    queue<NodePos> q;

    q.push(make_pair(n, index[n]));
    q.push(make_pair(nullptr, 0));

    size_t pos = 0;

    while(!q.empty())
    {
      NodePos p = q.front();
      q.pop();

      if(p.first == nullptr)
      {
        //std::cerr << " Poped null " << std::endl;
        std::cerr << std::endl;

        if(!q.empty())
        {
          q.push(make_pair(nullptr, 0));
        }

        pos = 0;
      }
      else
      {
        //std::cerr << " Poped " << p.first->value_  << std::endl;
        for(size_t i = pos; i < p.second; ++i)
        {
          std::cerr << " ";
        }

        pos = p.second;

        std::cerr << p.first->value_;

        pos += 1;

        if(p.first->left_)
        { 
          q.push(make_pair(p.first->left_, index[p.first->left_]));
        }

        if(p.first->right_)
        { 
          q.push(make_pair(p.first->right_, index[p.first->right_]));
        }
      }
    }
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

