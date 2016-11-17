// Pb:
// ---
//
// Write a function to check if a string matches a regex patter. Note that
// you only have to deal with patterns containing "*". Also, note that the
// pattern can't start with "*". 
// 
// Some examples: 
// 
// isMatch(“aa”,”a”) → false 
// isMatch(“aa”,”aa”) → true 
// isMatch(“aaa”,”aa”) → false 
// isMatch(“aa”, “a*”) → true 
// isMatch(“aa”, “*”) → true 
// isMatch(“ab”, “*”) → true 
// isMatch(“ab”, “*”) → true 
// isMatch(“b*a”, “a”) → true 
// isMatch(“a*a”, “a”) → true 
// isMatch(“aab”, “c*a*b”) → true
//
// Sol1:
// -----
// 
// Thomson algorithm
//
// Sol2:
// -----
//
// Simplified automaton

#include <string>
#include <vector>
#include <utility>
#include <stack>
#include <iostream>
#include <assert.h>
#include <array>

using std::vector;
using std::string;
using std::stack;
using std::pair;
using std::make_pair;
using std::array;

#define CONCAT '.'
#define FINAL  255
#define ALT    254

namespace
{
  // Thompson

#if 0

  struct State
  {
    unsigned char             c_; // = 255: finall;
                                  // = 254: alternation;
                                  // < 128: char;
    std::pair<State*, State*> out_;
    size_t                    listId_;

    State(char c, State* out1, State* out2) :
      c_(c),
      out_(make_pair(out1, out2)),
      listId_{0} {}
  };

  void connect(const vector<State**>& out, State* s)
  {
    for(auto o : out)
    {
      *o = s;
    }
  }

  string reg2Post(const string& regex)
  {
    struct Frame
    {
      size_t atomCount_;
      size_t altCount_;

      Frame() : atomCount_{0}, altCount_{0} {}
      Frame(size_t atomCount, size_t altCount)
       : atomCount_{atomCount},
         altCount_{altCount} {}
    };

    stack<Frame> s;
    size_t atomCount{0}, altCount{0};

    const size_t count = regex.size();
    string postFix;

    for(size_t i = 0; i < count; ++i)
    {
      switch(regex[i])
      {
        case '|':
        {
          while(--atomCount > 0)
          {
            postFix += CONCAT;
          }

          ++altCount;
          break;
        }
        case '*':
        case '+':
        case '?':
        {
          postFix += regex[i];
          break;
        }
        case '(':
        {
          if(atomCount > 1)
          {
            postFix += CONCAT;
            --atomCount;
          }

          s.push(Frame(atomCount, altCount));
          atomCount = 0;
          altCount = 0;
          break;
        }
        case ')':
        {
          while(--atomCount > 0)
          {
            postFix += CONCAT;
          }

          for(size_t i = 0; i < altCount; ++i)
          {
            postFix += '|';
          }

          atomCount = s.top().atomCount_;
          altCount = s.top().altCount_;
          s.pop();
          break;
        }
        default:
        {
          if(atomCount > 1)
          {
            postFix += CONCAT;
            --atomCount;
          }

          postFix += regex[i];
          ++atomCount;
        }
      }
    }

    while(--atomCount > 0)
    {
      postFix += CONCAT;
    }

    for(size_t i = 0; i < altCount; ++i)
    {
      postFix += '|';
    }

    return postFix;
  }

  State* post2Aut(const std::string& str)
  {
    struct Frag
    {
      State*          start_;
      vector<State**> out_;

      Frag(State* s, vector<State**>& out) : start_(s), out_(out) {}
    };

    stack<Frag*> s;
    const size_t count = str.size();

    for(size_t i = 0; i < count; ++i)
    {
      switch(str[i])
      {
        case '|':
        {
          assert(s.size() >= 2);
          Frag* f2 = s.top();
          s.pop();
          Frag* f1 = s.top();
          s.pop();

          State* st = new State(ALT, f1->start_, f2->start_);

          vector<State**> out(f1->out_);
          out.insert(out.end(), f2->out_.begin(), f2->out_.end());
          Frag* f = new Frag(st, out);
          s.push(f);

          break;
        }
        case '*':
        {
          Frag* f = s.top();
          s.pop();

          State* st = new State(ALT, f->start_, nullptr);
          connect(f->out_, st);
          
          vector<State**> out;
          out.push_back(&st->out_.second);
          f = new Frag(st, out);
          s.push(f);

          break;
        }
        case '+':
        {
          Frag* f = s.top();
          s.pop();

          State* st = new State(ALT, f->start_, nullptr);
          connect(f->out_, st);

          vector<State**> out;
          out.push_back(&st->out_.second);
          f->out_ = out;
          s.push(f);

          break;
        }
        case '?':
        {
          Frag* f = s.top();
          s.pop();

          State* st = new State(ALT, f->start_, nullptr);

          vector<State**> out(f->out_);
          out.push_back(&st->out_.second);
          f = new Frag(st, out);
          s.push(f);

          break;
        }
        case '.':
        {
          // Concatenation
          assert(s.size() >= 2);

          Frag* f2 = s.top();
          s.pop();
          Frag* f1 = s.top();
          s.pop();

          connect(f1->out_, f2->start_);
          f1->out_ = f2->out_;
          s.push(f1);

          break;
        }
        default:
        {
          // Literal
          State* st = new State(str[i], nullptr, nullptr);
          vector<State**> out;
          out.push_back(&(st->out_.first));
          Frag* f = new Frag(st, out);
          s.push(f);
        }
      }
    }

    assert(s.size() == 1);

    State* accepting = new State(FINAL, nullptr, nullptr);

    Frag* f = s.top();
    s.pop();
    connect(f->out_, accepting);

    return f->start_;
  }

  void addState(vector<State*>& v, State* s, size_t listId)
  {
    if(s != nullptr && s->listId_ != listId)
    {
      if(s->c_ == ALT)
      {
        addState(v, s->out_.first, listId);
        addState(v, s->out_.second, listId);
      }
      else
      {
        s->listId_ = listId;
        v.push_back(s);
      }
    }
  }

  bool isMatch(const string& str, State* s)
  {
    const size_t count = str.size();
    vector<State*> currentStates, nextStates;

    size_t listId = 1;
    addState(currentStates, s, listId);

    for(size_t i = 0; i < count; ++i)
    {
      ++listId;

      for(auto s : currentStates)
      {
        if(s->c_ == str[i])
        {
          addState(nextStates, s->out_.first, listId);
          addState(nextStates, s->out_.second, listId);
        }
      }

      if(nextStates.empty())
      {
        //std::cerr << "Can't advance" << std::endl;
        return false;
      }

      currentStates = nextStates;
      nextStates.clear();
    }

    for(auto s : currentStates)
    {
      if(s->c_ == FINAL)
      {
        return true;
      }
    }

    //std::cerr << "Did not reach a final state" << std::endl;
    return false;
  }

#endif

  // Simplified

  #define EMPTY 0

  struct Transition
  {
    char c_;
    int  state_;

    Transition() : c_{EMPTY}, state_{-1} {}
  };

  using State = pair<Transition, Transition>;
  using StateList = vector<size_t>;

  class NFA
  {
    public:

      explicit NFA(const string& pattern)
      {
        const size_t count = pattern.size();
        transitions_.resize(count);

        size_t state = 0;

        for(size_t i = 0; i < count; ++i)
        {
          if(pattern[i] != '*')
          {
            transitions_[state].first.c_ = pattern[i];
            transitions_[state].first.state_ = state+1;
            ++state;
          }
          else
          {
            --state;
            transitions_[state].first.state_ = state;
            transitions_[state].second.state_ = state+1;
            ++state;
          }
        }

        final_ = state;
      }

      StateList step(size_t st, char c)
      {
        //std::cerr << " B Step " << c << " on state " << st << std::endl;
        StateList l;

        if(st >= final_)
        {
          return l;
        }

        processTr(transitions_[st].first, c, l);
        processTr(transitions_[st].second, c, l);

        //std::cerr << " E Step " << c << " on state " << st << std::endl;
        return l;
      }

      bool isFinal(size_t st)
      {
        return st == final_ ||
               (transitions_[st].first.c_ == EMPTY && 
                transitions_[st].first.state_ == final_) ||
               (transitions_[st].second.c_ == EMPTY && 
                transitions_[st].second.state_ == final_);
      }

    private:

      void processTr(const Transition& tr, char c, StateList& l)
      {
        if(tr.state_ != -1 && tr.c_ == c)
        {
          //std::cerr << " first leg " << std::endl;
          l.push_back(tr.state_);
        }
        else if(tr.state_ != -1 && tr.c_ == EMPTY)
        {
          //std::cerr << " second leg " << std::endl;
          StateList tmp = step(tr.state_, c);
          l.insert(l.end(), tmp.begin(), tmp.end());
        }
     }
 
      vector<State> transitions_;
      size_t        final_;
  };
}

int main(int argc, char* argv[])
{
  struct TestCase
  {
    string str_;
    string pattern_;
    bool   outcome_;

    TestCase(const string& str, const string& pattern, bool outcome)
     : str_(str),
       pattern_(pattern),
       outcome_(outcome) {}
  };

  TestCase a[] = 
  {
    {"aa", "a", false},
    {"aa", "aa", true},
    {"aaa", "aa", false},
    {"aa", "a*", true},
    {"a", "b*a", true},
    {"a", "a*a", true},
    {"aab", "c*a*b*", true}
  };

#if 0
  string postfix = reg2Post(regex);
  State* aut = post2Aut(postfix);

  std::cerr << "Matching " << str << " against " << regex
            << " returned " << std::boolalpha << isMatch(str, aut)
            << std::endl;
#endif

  for(const auto& t : a)
  {
    string regex{t.pattern_};
    string str{t.str_};

  NFA aut(regex);

  const size_t count = str.size();
  bool match{true};

  vector<int> currentStates{0};

  for(size_t i = 0; i < count; ++i)
  {
    //std::cerr << " Processing " << str[i] << std::endl;

    vector<int> nextStates;

    for(auto s : currentStates)
    {
      //std::cerr << " From state " << s << std::endl;

      StateList l = aut.step(s, str[i]);
      nextStates.insert(nextStates.begin(), l.begin(), l.end());
    }

    if(nextStates.empty())
    {
      //std::cerr << " Exit 1 " << std::endl;
      match = false;
    }
    else
    {
      //std::cerr << " To states: ";
      //std::copy(nextStates.begin(), nextStates.end(), std::ostream_iterator<int>(std::cerr, ","));
      //std::cerr << std::endl;
    }

    currentStates = nextStates;
    nextStates.clear();
  }

  if(match)
  {
    for(auto s : currentStates)
    {
      match = aut.isFinal(s);

      if(match)
      {
        break;
      }
    }
  }
  
    if(match != t.outcome_)
    {
      std::cerr << "Matching " << str << " against " << regex
                << " returned " << std::boolalpha << match << std::endl;
    }
  }

  std::cerr << " Passed " << std::endl;
  return 0;
}

