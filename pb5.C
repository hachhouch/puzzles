#include <vector>
#include <cstddef>

class ANDEquation
{
  public:
    
    int restoreY( const std::vector<int>& A )
    {
      const size_t count = A.size();
      
      // Find min
      size_t min = 0;        
      for( size_t i = 1; i < count; ++i )
      {
        if( A[i] < A[min] )
        {
          min = i;
        }
      }

      const size_t first = min > 0 ? 0 : 1;
      int y = A[first];

      for( size_t i = 0; i < count; ++i )
      {
        if( i != min && i != first )
        {
          y &= A[i];
        }
      }
        
      return y == A[min] ? y : -1;
    }
};

