// Pb:
// ---
// 
// Given an array of contacts with phone numbers/emails you should detect
// and union identical contacts. 
// 
// For example, given the following contacts array: 
// 
// [ [ "John", "john@gmail.com", "john@fb.com"], 
// [ "Dan", "dan@gmail.com", "+1234567"], 
// [ "john123", "+5412312", "john123@skype.com"], 
// [ "john1985", "+5412312", "john@fb.com"] ] 
// 
// We can see that john1985, John and john123 are the same person by their
// contact information. 
// 
// We should output 
// 
// [[ 0, 2, 3], [1]] (0,2,3 are the same person and 1 is another one)
// 
// Sol:
// ----
// 
// Connected components
//

#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <queue>
#include <iostream>

using std::vector;
using std::string;
using std::set;
using std::unordered_map;
using std::queue;

namespace
{
  struct Contact
  {
    string         name_;
    vector<string> phones_;
    vector<string> emails_;
  };

  using Contacts = vector<Contact>;
  using Graph = vector<set<size_t>>;
  using Hash = unordered_map<string, set<size_t>>;

  Graph scanContacts(const Contacts& contacts)
  {
    const size_t count = contacts.size();
    Graph g(count);
    Hash h;

    for(size_t i = 0; i < count; ++i)
    {
      const Contact& c = contacts[i];

      for(const auto& p : c.phones_)
      {
        Hash::const_iterator pos = h.find(p);

        if(pos != h.end())
        {
          for(auto n : pos->second)
          {
            g[i].insert(n);
            g[n].insert(i);
          }
        }

        h[p].insert(i);
      }

      for(const auto& e : c.emails_)
      {
        Hash::const_iterator pos = h.find(e);

        if(pos != h.end())
        {
          for(auto n : pos->second)
          {
            g[i].insert(n);
            g[n].insert(i);
          }
        }

        h[e].insert(i);
      }
    }

    return g;
  }

  void printComponents(const Graph& g)
  {
    const size_t count = g.size();
    vector<bool> visited(count);

    for(size_t i = 0; i < count; ++i)
    {
      if(!visited[i])
      {
        queue<size_t> q;
        q.push(i);
        visited[i] = true;

        std::cerr << "[";

        while(!q.empty())
        {
          size_t n = q.front();
          q.pop();
     
          std::cerr << n << ",";

          for(auto c : g[n])
          {
            if(!visited[c])
            {
              q.push(c);
              visited[c] = true;
            }
          }
        }

        std::cerr << "], ";
      }
    }

    std::cerr << std::endl;
  }
}

int main(int argc, char* argv[])
{
  Contacts c = {
    {"John",     {},           {"john@gmail.com", "john@fb.com"}}, 
    {"Dan",      {"+1234567"}, {"dan@gmail.com"}}, 
    {"john123",  {"+5412312"}, {"john123@skype.com"}}, 
    {"john1985", {"+5412312"}, {"john@fb.com"}} 
  };

  Graph g = scanContacts(c);
  printComponents(g);

  return 0;
}

