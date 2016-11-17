// You are given a string "abc" which is encoded like "123" where alphabets are mapped like a => 1 
// to z => 26. Now find out how many string can be formed by reverse engineering encode string "123". 
// 
// For ex. given string "123" we can form 3 string "abc"(1,2,3), "lc" (i.e 12,3), "aw"(1,23). 
// 
// for string "1234" we have following possible combinations, I might be missing some of them but you get the idea 
// 
// {12, 3, 4} 
// {1, 23, 4} 
// {1, 2, 3, 4}

#include <string>
#include <iostream>

namespace
{
  size_t getCount(const std::string& encoded)
  {
    if(encoded.empty())
    {
      return 0;
    }

    const auto n = encoded.size();

    if(n == 1)
    {
      return 1;
    }

    size_t* cache = new size_t[n];
    memset(cache, 0, n*sizeof(size_t));
    cache[n-1] = 1;

    for(auto i = n-1; i > 0; )
    {
      --i;

      if(encoded[i] != '0')
      {
        cache[i] += cache[i+1];

        char tmp[3];
        strncpy(tmp, encoded.c_str()+i, 2);
        int value = atoi(tmp);

        if(value <= 26)
        {
          if(i < n-2)
          {
            cache[i] += cache[i+2];
          }
          else
          {
            cache[i] += 1;
          }
        }
      }
    }

    delete [] cache;
    return cache[0];
  }
}

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    std::cerr << "Missing arg." << std::endl;
  }
  for(int i = 1; i < argc; ++i)
  {
    std::cerr << argv[i] << ": " << getCount(argv[i]) << std::endl;
  }
}
