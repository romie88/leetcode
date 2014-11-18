//Pascal's Triangle II
//
//Given an index k, return the kth row of the Pascal's triangle.
//
//For example, given k = 3,
//Return [1,3,3,1].
//
//Note:
//Could you optimize your algorithm to use only O(k) extra space?

//Tags: Array

#include <vector>

class Solution {
public:
    std::vector< int > getRow( int rowIndex ) {
        
        std::vector< int > row( rowIndex + 1, 0 );
        row[ 0 ] = 1;
        for ( int i = 0; i < rowIndex; ++i )
        {
            for ( int j = i - 1; j >= 0; --j )
                row[ j + 1 ] = row[ j ] + row[ j + 1 ];
             
            row[ i + 1 ] = 1;
        }

        return row;
    }
};
