#include <string>

class AB
{
  public:
    
    std::string createString( int N, int K )
    {
      std::string outcome;

      if( N > 0 && K > 0 )
      {
        bool foundOne = false;
        size_t aCount = 0, bCount = 0;
      
        for( int i = 1; i <= K/2; ++i )
        {
          if( K%i == 0 )
          {
            aCount = i;
            bCount = K/i;
            size_t len = aCount+bCount;
              
            if( len <= N )
            {
              foundOne = true;
              break;
            }
          }
        }
          
        if( foundOne )
        {
          for( int i=0; i<aCount; ++i )
          {
            outcome += 'A';
          }

          for( int i=0; i<bCount; ++i )
          {
            outcome += 'B';
          }
            
          size_t padding = (N-(aCount+bCount));
            
          for( int i=0; i<padding; ++i )
          {
            outcome += 'A';
          }
        }
      }
      else
      {
        for( int i=0; i<N; ++i )
        {
          outcome += 'A';
        }
      }
      
      return outcome;
    }
};

