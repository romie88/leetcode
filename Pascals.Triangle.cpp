//Pascal's Triangle 2012-10-28
//
//Given numRows, generate the first numRows of Pascal's triangle.
//
//For example, given numRows = 5,
//Return
//
//[
//     [1],
//    [1,1],
//   [1,2,1],
//  [1,3,3,1],
// [1,4,6,4,1]
//]

//Tags: Array

#include <vector>

class Solution {
public:
    std::vector< std::vector< int > > generate( int numRows ) {
        
        std::vector< std::vector< int > > pt;
        
        if ( numRows == 0 )
            return pt;

        std::vector< int > row( 1, 1 );
        pt.push_back( row );
        
        std::vector< int > next_row;
        for ( int i = 1; i < numRows; ++i )
        {
            next_row.push_back( 1 );
            for ( int j = 0; j < row.size() - 1; ++j )
                next_row.push_back( row[ j ] + row[ j + 1 ] );
            next_row.push_back( 1 );
            
            row.swap( next_row );
            pt.push_back( row );
            next_row.clear();
        }
        
        return pt;
    }
};
