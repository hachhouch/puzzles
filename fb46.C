// Pb:
// ---
// 
// Permutate a list of string 
// this question is supposed permutate the characters instead of who string, 
// 
// as input example {"red", "fox", "super" }, the expected output is 
// 
// rfs 
// rfu 
// rfp 
// rfe 
// rfr 
// ros 
// rou 
// rop 
// roe 
// ror 
// rxs 
// rxu 
// rxp 
// rxe 
// rxr 
// efs 
// efu 
// efp 
// efe 
// efr 
// eos 
// eou 
// eop 
// eoe 
// eor 
// exs 
// exu 
// exp 
// exe 
// exr 
// dfs 
// dfu 
// dfp 
// dfe 
// dfr 
// dos 
// dou 
// dop 
// doe 
// dor 
// dxs 
// dxu 
// dxp 
// dxe 
// dxr
//
// Sol:
//

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

namespace
{
  void printPermutations(const vector<string>& v, size_t start, string prefix)
  {
    if(start <= v.size()-1)
    {
      const string& s = v[start];
      const size_t count = s.size();

      for(size_t i = 0; i < count; ++i)
      {
        string tmp = prefix + s[i];
        printPermutations(v, start+1, tmp);

        if(start == v.size()-1)
        {
          std::cerr << prefix << s[i] << std::endl;
        }
      }
    }
  }
}

int main(int argc, char* argv[])
{
  vector<string> v{
    "red",
    "fox",
    "super"
  };

  printPermutations(v, 0, "");
  return 0;
}

