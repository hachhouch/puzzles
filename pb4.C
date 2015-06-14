#include <string>
#include <vector>

class ABoardGame
{
  public:
    
    std::string whoWins( const std::vector<std::string>& board ) const
    {
      const size_t N = board.size()/2;
        
      for( size_t k = 1; k <= N; ++k )
      {
        size_t aCount = 0;
        size_t bCount = 0;
        const size_t min = N-k;
        const size_t max = N-1+k;
          
        for( size_t i = min; i <= max; ++i )
        {
          for( size_t j = min; j <= max; ++j )
          {
            if( board[i][j] == 'A' )
            {
              ++aCount;
            }
            else if( board[i][j] == 'B' )
            {
              ++bCount;
            }
          }
        }
      
        if( aCount > bCount )
        {
          return "Alice";
        }
        else if( aCount < bCount )
        {
          return "Bob";
        }
      }
        
      return "Draw";
    }
};

