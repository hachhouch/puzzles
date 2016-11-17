// Pb:
// ---
// 
// Merge K sorted singly linked list
// 
// Sol:
// ----
// 
// Merge them 2 at a time.
//

#include <vector>
#include <iostream>
#include <memory>

using std::vector;
using std::shared_ptr;

namespace
{
  struct Node
  {
    int              value_;
    shared_ptr<Node> next_;

    Node(int value, shared_ptr<Node> next) : value_(value), next_(next) {}
  };


  shared_ptr<Node> merge2(shared_ptr<Node> l1, shared_ptr<Node> l2)
  {
    if(l1 == nullptr)
    {
      return l2;
    }

    if(l2 == nullptr)
    {
      return l1;
    }

    shared_ptr<Node> h;

    if(l1->value_ < l2->value_)
    {
      h = l1;
      l1 = l1->next_;
    }
    else
    {
      h = l2;
      l2 = l2->next_;
    }

    shared_ptr<Node> cur(h);

    while(l1 && l2)
    {
      if(l1->value_ < l2->value_)
      {
        cur->next_ = l1;
        l1 = l1->next_;
      }
      else
      {
        cur->next_ = l2;
        l2 = l2->next_;
      }

      cur = cur->next_;
    }

    if(l1)
    {
      cur->next_ = l1;
    }
    else
    {
      cur->next_ = l2;
    }

    return h;
  }

  shared_ptr<Node> mergek(vector<shared_ptr<Node>>& lists)
  {
    const size_t k = lists.size();

    for(size_t step = 1; step < k; step *=2)
    {
      for(size_t i = 0; i < k; i+=2*step)
      {
        if(i + step < k)
        {
          //std::cerr << std::endl << "merging " << i << " and " << i+step << std::endl;
          lists[i] = merge2(lists[i], lists[i+step]);
          lists[i+step].reset();
        }
      }
    }

    return lists[0];   
  }
}

int main(int argc, char* argv[])
{
  vector<shared_ptr<Node>> v;

  auto nine = std::make_shared<Node>(9, nullptr);
  auto five = std::make_shared<Node>(5, nine);
  auto one = std::make_shared<Node>(1, five);

  v.push_back(one);

  auto six = std::make_shared<Node>(6, nullptr);
  auto four = std::make_shared<Node>(4, six);
  auto two = std::make_shared<Node>(2, four);

  v.push_back(two);

  auto seven = std::make_shared<Node>(7, nullptr);
  auto three = std::make_shared<Node>(3, seven);

  v.push_back(three);

  auto fifteen = std::make_shared<Node>(15, nullptr);
  auto eight = std::make_shared<Node>(8, fifteen);

  v.push_back(eight);

  auto fourteen = std::make_shared<Node>(14, nullptr);
  auto ten = std::make_shared<Node>(10, fourteen);

  v.push_back(ten);

  auto thirteen = std::make_shared<Node>(13, nullptr);
  auto twelve = std::make_shared<Node>(12, thirteen);
  auto eleven = std::make_shared<Node>(11, twelve);

  v.push_back(eleven);

  shared_ptr<Node> m = mergek(v);

  while(m)
  {
    std::cerr << m->value_ << ", ";
    m = m->next_;
  }

  std::cerr << std::endl;
  return 0;
}

