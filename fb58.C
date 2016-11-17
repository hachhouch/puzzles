// Pb:
// ---
// 
// Write a program that answers YES/NO search queries containing * placeholders.
// Example: if the data you have is (hazem, ahmed, moustafa, fizo), then you should
// answer as follows for: 
//  ahmed: YES 
//  m**stafa: YES 
//  fizoo: NO 
//  fizd: NO 
//  *****: YES 
//  ****: YES  
//  **: NO 
// Your program should be able to answer each search query in O(1).
// 
// Sol:
// ----
// 
// If we assume we can't use regex. (Since that would somewhat trivialize this problem)
// 
// You could populate the hashtable by recursively running through all the strings and
// replacing * in the strings to make all combinations of letters and *.
// If the length of the longest string is k, then the population of the hashtable runs
// in O(n * 2 ^k), but then lookup is just O(1).
//

#include <vector>
#include <string>
#include <utility>
#include <unordered_set>
#include <iostream>

#include <assert.h>

using std::vector;
using std::string;
using std::pair;
using std::unordered_set;

namespace
{
  using Dict = vector<string>;
  using FastDict = unordered_set<string>;
  using TestData = vector<pair<string,bool>>;

  class SearchEngine
  {
    public:

      explicit SearchEngine(const Dict& d);
      bool search(const string& word);

    private:

      void populateWith(string word, size_t i);

      FastDict dict_;
  };

  SearchEngine::SearchEngine(const Dict& dic)
  {
    for(const auto& w : dic)
    {
      populateWith(w, 0);
    }
  }

  bool SearchEngine::search(const string& word)
  {
    return dict_.find(word) != dict_.end();
  }

  void SearchEngine::populateWith(string word, size_t i)
  {
    if(i == word.size())
    {
      std::cerr << "Adding " << word << std::endl;
      dict_.insert(word);
      return;
    }

    populateWith(word, i+1);
    word[i] = '*';
    populateWith(word, i+1);
  }
}

int main(int argc, char* arv[])
{
  Dict d = {
    "hazem",
    "ahmed",
    "moustafa",
    "fizo"
  };

  SearchEngine engine(d);

  TestData tests = {
    {"ahmed", true},
    {"m**stafa", true},
    {"fizoo", false},
    {"fizd", false},
    {"*****", true},
    {"****", true}, 
    {"**", false}
  };

  for(const auto& td : tests)
  {
    assert(engine.search(td.first) == td.second);
  }

  return 0;
}

