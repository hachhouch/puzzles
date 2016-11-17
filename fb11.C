// Problem:
//
// Given a string where in each word letters were randomly shuffled and after that words were
// written without spaces (lets call it X). Also you have a dictionary. The task is to return
// all possible strings S that can be transformed into the string X and all words in S are from
// dictionary.
//
// Solution:
//
// actually just string segmentation with the added wrinkle of shuffled words:
// geeksforgeeks.org/dynamic-programming-set-32-word-break-proble

#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

using std::map;
using std::vector;
using std::string;

namespace
{
  using WordList = vector<string>;
  using WordMap = map<string,WordList>;
  using Dictionary = WordList;
  using SubSplits = vector<WordList>;

  void preProcessDict(const Dictionary& dict, WordMap& wm)
  {
    for(auto word : dict)
    {
      string tmp{word};
      std::sort(tmp.begin(), tmp.end());
      wm[tmp].push_back(word);
    }
  }

  void dfs(const SubSplits& dp, size_t index, const std::string& current, WordList& splits)
  {
    string tmp;

    for(const auto& word : dp[index])
    {
      tmp = word + " " + current;

      if(index < word.size())
      {
        // Found one
        splits.push_back(tmp);
      }
      else
      {
        dfs(dp, index - word.size(), tmp, splits);
      }
    }
  } 

  void buildAllSplits(const SubSplits& dp, WordList& splits)
  {
    dfs(dp, dp.size()-1, "", splits);
  }

  void findAll(const string& str, const Dictionary& dict, WordList& splits)
  {
    // Check the degenrate case

    if(str.empty())
    {
      return;
    }

    // Preprocess the dictionary

    WordMap wm;
    preProcessDict(dict, wm);

    // Now find the valid splits

    const size_t count = str.size();
    SubSplits dp{count};
    
    for(size_t i = 0; i < count; ++i)
    {
      if(dp[i].empty())
      {
        string sub = str.substr(0, i+1);

        sort(sub.begin(), sub.end());
        const auto& pos = wm.find(sub);

        if(pos != wm.end())
        {
          std::copy(pos->second.begin(), pos->second.end(), std::back_inserter(dp[i]));
        }
      }

      if(!dp[i].empty())
      {
        for(size_t j = i+1; j < count; ++j)
        {
          string sub = str.substr(i+1, j-i);
          sort(sub.begin(), sub.end());
          auto pos = wm.find(sub);
          
          if(pos != wm.end())
          {
            std::copy(pos->second.begin(), pos->second.end(), std::back_inserter(dp[j]));
          }
        }
      }
    }

    buildAllSplits(dp, splits);
  }
}

int main(int argc, char* argv[])
{
  //string str{"ilikesamsung"};
  string str{"ajavdoeceehr"};

  Dictionary dict{
    "i",
    "like",
    "sam",
    "sung",
    "samsung",
    "mobile",
    "ice", 
    "cream",
    "icecream",
    "man",
    "go",
    "mango",
    "java",
    "code",
    "here"
  };

  WordList outcome;
  findAll(str, dict, outcome);

  std::cerr << "All splits for '" << str << "' are: " << std::endl;

  for(const auto& split : outcome)
  {
    std::cerr << split << std::endl;
  }

  return 0;
}

