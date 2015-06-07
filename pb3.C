#include <vector>
#include <string>
#include <deque>
#include <assert.h>

class ABCPath
{
  public:

    int length( std::vector<std::string> grid )
    {
      Graph g = buildGraph( grid );
      SortedGraph sg = getTopologicalOrder( g );

      int maxLen = 0;
      bool foundOne = false;

      for( SortedGraph::reverse_iterator rIt = sg.rbegin(), rEnd = sg.rend(); rIt != rEnd; ++rIt)
      {
        Node& n = g[*rIt];

        for( auto c : n.adjacencyList_ )
        {
          if( g[c].maxPathLen_ + 1 > n.maxPathLen_ )
          {
            n.maxPathLen_ = g[c].maxPathLen_ + 1;
          }
        }

        if( n.label_ == 'A' )
        {
          if( n.maxPathLen_ > maxLen )
          {
            maxLen = n.maxPathLen_;
          }

          foundOne = true;
        }
      }

      return foundOne ? maxLen+1 : 0;
    }

  private:
 
    struct Node
    {
      enum Color
      {
        WHITE,
        GREY,
        BLACK
      };

      char                label_;
      std::vector<size_t> adjacencyList_;
      Color               color_;       // Needed to implement DFS.
      size_t              maxPathLen_;  // Used to store the length of the longest path leaving this node.

      Node() : label_( 0 ), color_( WHITE ), maxPathLen_( 0 ) {}
    };

    // Using the adjacency list implementation, the DAG is simply a list of nodes.
    typedef std::vector<Node> Graph;

    // A topologically-sorted graph is a list of node indices.
    typedef std::deque<size_t> SortedGraph;

    Graph buildGraph( const std::vector<std::string>& grid )
    {
      Graph g;
      const size_t height = grid.size();
      const size_t width = grid.empty() ? 0 : grid[0].size();

      for( size_t i = 0; i < height; ++i )
      {
        const std::string& row = grid[i];

        for( size_t j = 0; j < width; ++j )
        {
          char c = row[j];
          Node n;
          n.label_ = c;

          std::vector<size_t> nodesToCheck;
          nodesToCheck.reserve(4);

          const bool firstCol = ( j == 0 );

          if( !firstCol )
          {
            // Left
            nodesToCheck.push_back( (i*width) + (j-1) );
          }
            
          const bool firstRow = ( i == 0 );

          if( !firstRow )
          {
            // Top
            nodesToCheck.push_back( (i-1)*width + j ); 

            // Top-Left
            if( !firstCol )
            {
              nodesToCheck.push_back( (i-1)*width + (j-1) );
            }

            const bool lastCol = ( j == (width-1) );

            // Top-Right
            if( !lastCol )
            {
              nodesToCheck.push_back( (i-1)*width + (j+1) );
            }
          }

          for( auto index : nodesToCheck )
          {
            if( isConnected( c, g[index].label_ ) )
            {
              n.adjacencyList_.push_back(index);
            }
            else if( isConnected( g[index].label_, c ) )
            {
              g[index].adjacencyList_.push_back( (i*width) + j );
            }         
          }

          g.push_back( n );
        }
      }

      return g;
    }
    
    bool isConnected( char a, char b )
    {
      return a == ( b - 1 );
    }

    SortedGraph getTopologicalOrder( Graph& g )
    {
      SortedGraph s;

      // Use depth-first traversal to compute a toplogical sort of the DAG
      const size_t count = g.size();

      for( size_t i = 0; i < count; ++i )
      {
        Node& n = g[i];

        if( n.color_ == Node::WHITE )
        {
          DFS( i, g, s );
        }
      }

      return s;
    }

    void DFS( const size_t i, Graph& g, SortedGraph& s )
    {
      Node& n = g[i];
      assert( n.color_ == Node::WHITE );

      n.color_ = Node::GREY;

      for( auto idx : n.adjacencyList_ )
      {
        Node& child = g[idx];
        
        if( child.color_ == Node::WHITE )
        {
          DFS( idx, g, s );
        }
      }
 
      n.color_ = Node::BLACK;
      s.push_front( i );
    }
};
