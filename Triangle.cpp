//Triangle 2012-10-29
//
//Given a triangle, find the minimum path sum from top to bottom.
//Each step you may move to adjacent numbers on the row below.
//
//For example, given the following triangle
//[
//     [2],
//    [3,4],
//   [6,5,7],
//  [4,1,8,3]
//]
//The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
//
//Note:
//Bonus point if you are able to do this using only O(n) extra space,
//where n is the total number of rows in the triangle.

//Tags: Array, Dynamic Programming

#include <vector>
#include <algorithm>

class Solution {
public:
    int minimumTotal( std::vector< std::vector< int > > & triangle ) {
        
        if ( triangle.size() == 1 )
            return triangle[ 0 ][ 0 ];

        const int MAX_ROW = triangle.size() - 1;
        const int MAX_COL = triangle[ MAX_ROW ].size() - 1;

        std::vector< int > lower_level( triangle[ MAX_ROW ] );
        for ( int i = MAX_ROW; i > 0; --i )
        {
            std::vector< int > upper_level( triangle[ i - 1 ] );
            
            for ( int j = 0; j < lower_level.size() - 1; ++j )
                upper_level[ j ] += std::min( lower_level[ j ],
                                              lower_level[ j + 1 ] );

            lower_level.swap( upper_level );
        }

        return lower_level[ 0 ];
    }
};
