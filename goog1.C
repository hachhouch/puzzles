// List of string that represent class names in CamelCaseNotation. 
// 
// Write a function that given a List and a pattern returns the matching elements. 
// 
// ['HelloMars', 'HelloWorld', 'HelloWorldMars', 'HiHo'] 
// 
// H -> [HelloMars, HelloWorld, HelloWorldMars, HiHo] 
// HW -> [HelloWorld, HelloWorldMars] 
// Ho -> [] 
// HeWorM -> [HelloWorldMars]

#include <vector>
#include <string>
#include <array>
#include <iostream>

namespace mhl
{
  class Automaton
  {
    public:

      explicit Automaton(const std::string& pattern)
      {
        const size_t count = pattern.size();
        transitions.resize(count+1);

        for(size_t i = 0; i < count; ++i)
        {
          transitions[i].fill(0);
          transitions[i][(int)pattern[i]] = i+1;

          if(pattern[i] >= 'A' && pattern[i] <= 'Z')
          {
            for(char c = 'a'; c <= 'z'; ++c)
            {
              transitions[i][(int)c] = i;
            }

            transitions[i][(int)'_'] = i;
          }
        }
      }

      size_t getNext(int state, char event) const
      {
        if(state >= transitions.size())
        {
          return 0;
        }

        return transitions[state][event];
      }

      bool isAccepting(size_t state) const {return state == (transitions.size()-1);}

    private:

      std::vector<std::array<int,127> > transitions;
  };
}

int main(int argc, char* argv[])
{
  const char* toValidate = argv[1], *pattern = argv[2];

  mhl::Automaton aut(pattern);
  const size_t count = strlen(toValidate);
  size_t currentState = 0;

  for(size_t i = 0; i < count; ++i)
  {
    size_t next = aut.getNext(currentState, toValidate[i]);

    if(next == 0)
    {
      std::cerr << "Rejected" << std::endl;
      return 0;
    }
    if(aut.isAccepting(next))
    {
      std::cerr << std::endl << "Accepted" << std::endl;
      return 0;
    }
    else
    {
      currentState = next;
    }
  }

  std::cerr << "Rejected" << std::endl;
  return 0;
}

