// Pb:
// ---
// 
// You have a list of words with ranking. 
// Now you need to create a function that will take this list as input and provide
// a way so that a T9 keyboard can provide three top results of probable words based
// on rankings for the numbers punched in.
// 
// Sol:
// ----
//
// The implementation uses Trie and PriorityQueue.
//

#include <utility>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <sstream>

using std::pair;
using std::priority_queue;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

namespace
{
  using RankedWord = pair<string, size_t>;

  struct RankedWordCmp
  {
    bool operator()(const RankedWord& lhs, const RankedWord& rhs)
    {
      return lhs.second > rhs.second;
    }
  };

  using Result = priority_queue<RankedWord, vector<RankedWord>, RankedWordCmp>;
  using Dict = vector<RankedWord>;

  class Trie
  {
    public:

      Trie()
      {
        root_ = make_shared<Node>(0);
      }

      void addWord(const RankedWord& word)
      {
        static char a2n[] = {
          '2', '2', '2',
          '3', '3', '3',
          '4', '4', '4',
          '5', '5', '5',
          '6', '6', '6',
          '7', '7', '7', '7',
          '8', '8', '8',
          '9', '9', '9' ,'9'
        };

        if(word.first.empty())
        {
          root_->mark(word);
          return;
        }

        shared_ptr<Node> n = root_;
        const size_t count = word.first.size();

        for(size_t i = 0; i < count; ++i)
        {
          char c = a2n[word.first[i]-'a'];
 
          shared_ptr<Node> child = n->getChild(c);

          if(child)
          {
            n = child;
          }
          else
          {
            n = n->addChild(c);
          }
        }

        n->mark(word);
      }

      void search(const string& str, Result& words) const
      {
        const size_t count = str.size();
        shared_ptr<Node> n = root_;

        for(size_t i = 0; i < count; ++i)
        {
          char c = str[i];
          shared_ptr<Node> child = n->getChild(c);

          if(child)
          {
            n = child;
          }
          else
          {
            return;
          }
        }

        getWords(n, str, words);
      }

    private:

      class Node
      {
        public:

          explicit Node(char c) : value_{c} {}

          shared_ptr<Node> getChild(char c) const
          {
            for(const auto& n : children_)
            {
              if(n->getValue() == c)
              {
                return n;
              }
            }

            return nullptr;
          }

          shared_ptr<Node> addChild(char c)
          {
            shared_ptr<Node> n = make_shared<Node>(c);
            children_.push_back(n);
            return n;
          }

          void mark(const RankedWord& w)
          {
            words_.push_back(w);
          }

          bool isMarked() const
          {
            return !words_.empty();
          }

          char getValue() const
          {
            return value_;
          }

          const Dict& getWords() const
          {
            return words_;
          }

          const vector<shared_ptr<Node>>& getChildren() const
          {
            return children_;
          }

        private:

          char                     value_;
          Dict                     words_;
          vector<shared_ptr<Node>> children_;
      };

      void getWords(const shared_ptr<Node>& n, const string& str,  Result& words) const
      {
        if(n->isMarked())
        {
          for(const auto& w : n->getWords())
          {
            words.push(w);
          }

          while(words.size() > 1)
          {
            words.pop();
          }
        }

        const vector<shared_ptr<Node>>& children = n->getChildren();

        for(const auto& c : children)
        {
          std::ostringstream oss;
          oss << str;
          oss << c;
          getWords(c, oss.str(), words);
        }
      }

      shared_ptr<Node> root_;
  };
}

int main(int argc, char* argv[])
{
  Dict d = {
    {"abc", 100},
    {"aaa", 50},
    {"ate", 2}
  };

  Trie t;

  for(const auto p : d)
  {
    t.addWord(p);
  }

  Result r;
  t.search("2", r);

  while(!r.empty())
  {
    RankedWord w = r.top();
    r.pop();
    std::cerr << w.first << std::endl;
  }

  return 0;
}

