// Pb:
// ---
// 
// Assuming you're playing one game that you need guess a word from a dictionary.
// You're given a machine you can try to guess the word, the machine will return
// how many characters has been matched by your guess. Design a system to crack
// the word.
// 
// Sol:
// ----
// 
// Use a trie:
// * start with 1 char dict words until I find one where math(w) = len(w)
// * follow edge from that node that leads to 2-chars words until you find one that match
// * ...
// * stop when you reach a level that does not improve the match count.
// * Solution is the previous one.

#include <vector>
#include <string>
#include <memory>
#include <iostream>

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;

namespace
{
  vector<string> dict{
    "ate",
    "tea",
    "cat",
    "holiday",
    "found"
  };

  size_t guess(const string& word)
  {
    static string toGuess{"cat"};
    bool found{false};

    for(const auto& w : dict)
    {
      if(w == word)
      {
        found = true;
      }
    }

    if(!found)
    {
      return 0;
    }

    size_t count = std::min(toGuess.size(), word.size());

    size_t counter{0};

    for(size_t i = 0; i < count; ++i)
    {
      if(toGuess[i] == word[i])
      {
        ++counter;
      }
    }

    return counter;
  }

  class Node
  {
    public:

      explicit Node(char value) : value_(value), isWord_(false) {}

      void addChild(shared_ptr<Node> n) {children_.push_back(n);}
      const vector<shared_ptr<Node>>& getChildren() const {return children_;}

      shared_ptr<Node> findChild(char c) const
      {
        shared_ptr<Node> n;

        for(const auto& i : children_)
        {
          if(i->getValue() == c)
          {
            n = i;
            break;
          }
        }

        return n;
      }

      void mark() {isWord_ = true;}
      bool isMarked() const {return isWord_;}

      char getValue() const {return value_;}

    private:

      char                     value_;
      bool                     isWord_;
      vector<shared_ptr<Node>> children_;
  };

  class Trie
  {
    public:

      Trie();

      void addWord(const string& w);
      bool searchWord(const string& w);

      string guessWord();

    public:

      string guessFromPos(shared_ptr<Node> n, string& prefix);

      shared_ptr<Node> root_;
  };

  Trie::Trie() : root_(make_shared<Node>(0))
  {
  }

  void Trie::addWord(const string& w)
  {
    if(w.empty())
    {
      root_->mark();
      return;
    }

    shared_ptr<Node> cur = root_;
    size_t count = w.size();

    for(size_t i = 0; i < count; ++i)
    {
      shared_ptr<Node> c = cur->findChild(w[i]);

      if(!c)
      {
        c = make_shared<Node>(w[i]);
        cur->addChild(c);
      }

      cur = c;

      if(i == count-1)
      {
        cur->mark();
      }
    }
  }

  bool Trie::searchWord(const string& w)
  {
    size_t count = w.size();
    shared_ptr<Node> cur = root_;

    for(size_t i = 0; i < count; ++i)
    {
      shared_ptr<Node> c = cur->findChild(w[i]);

      if(!c)
      {
        return false;
      }

      cur = c;
    }

    return cur->isMarked();
  }

  string Trie::guessWord()
  {
    string prefix;
    return guessFromPos(root_, prefix);

  }

  string Trie::guessFromPos(shared_ptr<Node> n, string& prefix)
  {
    if(n->getChildren().empty())
    {
      return "";
    }

    for(const auto& c : n->getChildren())
    {
      if(c->isMarked())
      {
        string tmp  = prefix + c->getValue();

        if(guess(tmp) == tmp.size())
        {
          prefix += c->getValue();
          tmp = guessFromPos(c, prefix);

          if(tmp.empty())
          {
            return prefix;
          }
          else
          {
            return tmp;
          }
        }
      }
    }

    string bestFit;

    for(const auto& c : n->getChildren())
    {
      string tmp = prefix + c->getValue();
      string current = guessFromPos(c, tmp);

      if(current.size() > bestFit.size())
      {
        bestFit = current;
      }
    }

    return bestFit;
  }
}

int main(int argc, char* argv[])
{
  Trie trie;

  for(const auto& w : dict)
  {
    trie.addWord(w);
  }

  std::cerr << trie.guessWord() << std::endl;
  return 0;
}
