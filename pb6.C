#include <string>

using namespace std;

class ABBA
{
  public:
    
    string canObtain(string initial, string target)
    {
      return canBeObtained(target, initial, false);
    }
    
  private:

    string canBeObtained(string& target, const string& initial, bool goingLeft) const
    {
      if(target.size() == initial.size())
      {
        return areEquals(target, initial, goingLeft) ? "Possible" : "Impossible";
      }
      else if(target.size() > initial.size())
      {
        char c = goingLeft ? target.front() : target.back();

        if(goingLeft)
        {
          c = target.front();
          target.erase(0, 1);
        }
        else
        {
          c = target.back();
          target.pop_back();
        }
          
        if(c == 'B')
        {
          goingLeft = (!goingLeft);
        }

        return canBeObtained(target, initial, goingLeft);
      }
      else
      {
        return "Impossible";
      }
    }
    bool areEquals(const string& target, const string& initial, bool goingLeft) const
    {
      const size_t count = target.size();

      for(int i = 0; i < count; ++i)
      {
        size_t j = goingLeft ? (count - 1) - i : i;

        if( target[j] != initial[i] )
        {
          return false;
        }
      }

      return true;
    }
};

