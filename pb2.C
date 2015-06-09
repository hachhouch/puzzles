#include <string>
#include <iostream>

// FIXME: not optimal. Need to come up with a better solution.

class ABC
{
  public:

    std::string createString( int N, int K )
    {
      std::string outcome;
      int a = 0, b = 0, c = 0;
      bool foundOne = false;

      for( a = 1; !foundOne && a <= N; ++a )
      {
        for( b = 0; !foundOne && b <= N-a; ++b )
        {
          for( c = 0; !foundOne && c <= N - (a+b); ++c )
          {
            if( (a*b + a*c + b*c) == K )
            {
              foundOne = true;
            }
          }
        }
      }
      
      if( foundOne )
      {
         --a; --b; --c;

        for( int i = 1; i <= a; ++i )
        {
          outcome += 'A';
        }

        for( int i = 1; i <= b; ++i )
        {
          outcome += 'B';
        }

        for( int i = 1; i <= c; ++i )
        {
          outcome += 'C';
        }
      
        for( int i = 1; i <= (N-(a+b+c)); ++i )
        {
          outcome += 'A';
        }
      }  
      
      return outcome;
    }
};

