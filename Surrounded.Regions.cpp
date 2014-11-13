//Surrounded Regions
//
//Given a 2D board containing 'X' and 'O', capture all regions
//surrounded by 'X'.
//
//A region is captured by flipping all 'O's into 'X's in that
//surrounded region.
//
//For example,
//
//X X X X
//X O O X
//X X O X
//X O X X
//
//After running your function, the board should be:
//
//X X X X
//X X X X
//X X X X
//X O X X

//Tags: Breadth-first Search

#include <vector>
#include <queue>
#include <utility>

class Solution {
public:
    void solve( std::vector< std::vector< char > > & board ) {
        
		if ( board.size() == 0 )
			return;
		
        const int ROWS = board.size();
        const int COLS = board[ 0 ].size();
        
        //status[ i ][ j ] == true if it is an 'O' node and need no flipping
		std::vector< std::vector< bool > >
			status( board.size(),
					std::vector< bool >( board[ 0 ].size(), false ) );
		
		std::queue< std::pair< int, int > > o_queue;
		//put all 'O' nodes on four borders into the queue
		for ( int j = 0; j < board[ 0 ].size(); ++j )
		{
			if ( board[ 0 ][ j ] == 'O' )
            {
                status[ 0 ][ j ] = true;
				o_queue.push( std::make_pair( 0, j ) );
            }

			if ( board[ ROWS - 1 ][ j ] == 'O' )
            {
                status[ ROWS - 1 ][ j ] = true;
				o_queue.push( std::make_pair( ROWS - 1, j ) );
            }
		}
		for ( int i = 0; i < board.size(); ++i )
		{
            if ( board[ i ][ 0 ] == 'O' )
            {
                status[ i ][ 0 ] = true;
				o_queue.push( std::make_pair( i, 0 ) );
            }

			if ( board[ i ][ COLS - 1 ] == 'O' )
            {
                status[ i ][ COLS - 1 ] = true;
				o_queue.push( std::make_pair( i, COLS - 1 ) );
            }
		}
		
		//loop through all O's from borders
		while ( ! o_queue.empty() )
		{
			//BFS starts from o
			const auto o = o_queue.front();
		    o_queue.pop();

			int x = o.first;
			int y = o.second;

			//left
			if ( y - 1 > 0 //no need to check the border so > rather than >=
              && board[ x ][ y - 1 ] == 'O'
		      && status[ x ][ y - 1 ] == false )
			{
				status[ x ][ y - 1 ] = true;
				o_queue.push( std::make_pair( x, y - 1 ) );
			}
			//up
			if ( x - 1 > 0
              && board[ x - 1 ][ y ] == 'O'
			  && status[ x - 1 ][ y ] == false )
			{
				status[ x - 1 ][ y ] = true;
				o_queue.push( std::make_pair( x - 1, y ) );
			}
			//right
			if ( y + 1 < COLS - 1
              && board[ x ][ y + 1 ] == 'O'
			  && status[ x ][ y + 1 ] == false )
			{
				status[ x ][ y + 1 ] = true;
				o_queue.push( std::make_pair( x, y + 1 ) );
			}
			//down
			if ( x + 1 < ROWS - 1
              && board[ x + 1 ][ y ] == 'O'
			  && status[ x + 1 ][ y ] == false )
			{
				status[ x + 1 ][ y ] = true;
				o_queue.push( std::make_pair( x + 1, y ) );
			}
		}
        
		//flip all the nodes whose status is NOT_DECIDED
		for ( int i = 1; i < ROWS - 1; ++i )
		{
			for ( int j = 1; j < COLS - 1; ++j )
			{
				if ( status[ i ][ j ] == false
                  && board[ i ][ j ] == 'O' )
				{
					board[ i ][ j ] = 'X';
				}
			}
		}
    }
};
