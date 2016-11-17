// Write a function that takes the following inputs and gives the following outputs. 
// 
// Input: A list of points in 2-dimensional space, and an integer k 
// Output: The k input points closest to (5, 5), using Euclidean distance 
// 
// 
// Example: 
// 
// Input: {(-2, -4), (0, 0), (10, 15), (5, 6), (7, 8), (-10, -30)}, k = 2 
// Output: {(5, 6), (7, 8)}
// 

#include <vector>
#include <utility>
#include <iostream>
#include <cmath>

using std::vector;
using std::pair;
using std::make_pair;

namespace
{
  using Point = pair<int, int>;
  using Points = vector<Point>;

  size_t calDistance(const Point& p1, const Point& p2)
  {
    return std::sqrt(std::pow(p1.first - p2.first, 2) +
                     std::pow(p1.second - p2.second, 2));
  }

  void swap(Points& pts, vector<int>& d, size_t i, size_t j)
  {
    int tmp = d[i];
    d[i] = d[j];
    d[j] = tmp;

    Point tmp2 = pts[i];
    pts[i] = pts[j];
    pts[j] = tmp2;
  }

#if 0
  size_t partition(Points& pts, vector<int>& d, size_t s, size_t e)
  {
    if(s == e)
    {
      return s;
    }

    size_t i = s+1;
    size_t j = e;

    while(true)
    {
      while((i < j) && (d[i] < d[s])) i++;
      while((i <= j) && (d[j] > d[s])) --j;

      if(i<j)
      {
        swap(pts, d, i, j);
      }
      else
      {
        break;
      }
    }

    swap(pts, d, s, j);
    return j;
  }
#endif
  size_t partition(Points& pts, vector<int>& d, size_t s, size_t e)
  {
    if(s == e)
    {
      return s;
    }

    size_t i = s;
    size_t j = e+1;

    while(true)
    {
      while(d[++i] < d[s])
      {
        if(i == e)
        {
          break;
        }
      }

      while(d[--j] > d[s])
      {
        if(j == s)
        {
          break;
        } 
      }

      if(i<j)
      {
        swap(pts, d, i, j);
      }
      else
      {
        break;
      }
    }

    swap(pts, d, s, j);
    return j;
  }
  void findElement(Points& pts, vector<int>& d, size_t k)
  {
    //std::cerr << "S2" << std::endl;

    const size_t count = d.size()-1;
    size_t start = 0, end = count;

    while(start <= end)
    {
      size_t p = partition(pts, d, start, end);

      if(p == k)
      {
        return; 
      }
      else if(p > k)
      {
        end = p-1;
      }
      else
      {
        start = p+1;
      }
    }
  }

  Points getClosest(Points& pts, const Point& target, size_t k)
  {
    //std::cerr << "S1" << std::endl;

    const size_t count = pts.size();
    vector<int> distance(count);

    for(size_t i = 0; i < count; ++i)
    {
      distance[i] = calDistance(pts[i], target);
      //std::cerr << pts[i].first << "," << pts[i].second << " -> " << distance[i] << std::endl;
    }

    findElement(pts, distance, k-1);

    Points sol;
    sol.reserve(k);

    for(size_t i = 0; i < k; ++i)
    {
      sol.push_back(pts[i]);
    }

    return sol;
  }
}

int main(int argc, char* argv[])
{
  Points pts = {
    {-2, -4},
    {0, 0},
    {10, 15},
    {5, 6},
    {7, 8},
    {-10, -30}
  };

  Point target = make_pair(5, 5);

  const size_t k = 2;

  Points sol = getClosest(pts, target, k);
  
  std::for_each(
    sol.begin(),
    sol.end(),
    [] (const Point& p) {std::cerr << p.first << "," << p.second << std::endl;}
  );

  return 0;
}

