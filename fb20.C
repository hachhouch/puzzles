// Task schedule: given a sequence of task like A B C(means 3 different tasks),
// and a coldtime, which means you need to wait for that much time to start 
// next [same] task. Now---- 
// 
// Input: string, n 
// Output: the best task-finishing sequence. 
// 
// eg. input: AAABBB, 2 
// Output: AB_AB_AB 
// ( "_" represents do nothing and wait)
// 
// Use a maxheap with the frequency of each task being the key, everytime pop n
// item from the heap, and put in the result and update the keys. if there is
// less than n item in the heap then we should fill the gap with '_'

#include <string>
#include <queue>
#include <utility>
#include <iostream>

using std::string;
using std::priority_queue;

namespace
{
  using Task = std::pair<char, size_t>;

  struct TaskCmp
  {
    bool operator() (const Task& lhs, const Task& rhs) const
    {
      return lhs.second < rhs.second;
    }
  };

  using MaxHeap = priority_queue<Task, std::vector<Task>, TaskCmp>;

  string getOptSequence(const string& str, int n)
  {
    size_t counter[256];
    memset(counter, 0, sizeof(size_t)*256); 

    for(char c : str)
    {
      ++counter[c];
    }

    MaxHeap heap;

    for(int i = 0; i < 256; ++i)
    {
      if(counter[i] > 0)
      {
        heap.push(std::make_pair(i, counter[i]));
      }
    }

    string seq;

    while(!heap.empty())
    {
      memset(counter, 0, 256*sizeof(size_t));
      size_t padCount = 0;

      for(int i = 0; i < n; ++i)
      {
        if(!heap.empty())
        {
          Task t = heap.top();

          if(counter[t.first] == 0)
          {
            heap.pop();

            seq.append(1, t.first);
            --t.second;

            if(t.second > 0)
            {
              heap.push(t);
            }

            ++(counter[t.first]);
          }
          else
          {
            padCount = n - i;
            break;
          }
        }
        else
        {
          break;
        }
      }

      if(padCount > 0)
      {
        seq.append(padCount, '_');
      }
      else if(heap.empty())
      {
        break;
      }
    }

    return seq;
  }
}

int main(int argc, char* argv[])
{
  std::cerr << "Enter string: ";
  string str;
  std::cin >> str;
  std::cerr << "Enter coldtime: ";
  int n{0};
  std::cin >> n;

  std::cerr << "Best seq: " << getOptSequence(str, n) << std::endl;
  return 0;
}

