/**
 * Algorithms 64 Minimum Path Sum                                        Medium
 * 
 * Given a m x n grid filled with non-negative numbers, find a path from top
 * left to bottom right which minimizes the sum of all numbers along its path.
 * 
 * Note: You can only move either down or right at any point in time.
 * 
 * Tags: Array, Dynamic Programming
 * Similar Problems: (M) Unique Paths, (H) Dungeon Game
 */

#include <vector>
#include <algorithm>
#include <limits>

class Solution {
public:
    int minPathSum( const std::vector< std::vector< int > > & grid ) {
        return min_path_sum_DP2( grid );
    }
private:
    /**
     * O(m * n) runtime, O(m * n) space
     */
    int min_path_sum_DP( const std::vector< std::vector< int > > & grid ) {
        std::vector< std::vector< int > >
            P( grid.size(), std::vector< int >( grid[ 0 ].size(), 0 ) );
        const int M = grid.size();
        const int N = grid[ 0 ].size();
        //initialize boundary conditions
        P[ M - 1 ][ N - 1 ] = grid[ M - 1 ][ N - 1 ];
        for ( int i = M - 2; i >= 0; --i )
            P[ i ][ N - 1 ] = P[ i + 1 ][ N - 1 ] + grid[ i ][ N - 1 ];
        for ( int j = N - 2; j >= 0; --j )
            P[ M - 1 ][ j ] = P[ M - 1 ][ j + 1 ] + grid[ M - 1 ][ j ];
        //calculate the rest
        for ( int i = M - 2; i >= 0; --i ) {
            for ( int j = N - 2; j >= 0; --j ) {
                P[ i ][ j ] = grid[ i ][ j ]
                            + std::min( P[ i ][ j + 1 ],
                                        P[ i + 1 ][ j ] );
            }
        }
        
        return P[ 0 ][ 0 ];
    }
    
    /**
     * O(m * n) runtime, O(n) space
     * start from DP from (0,0)
     */
    int min_path_sum_DP2( const std::vector< std::vector< int > > & grid ) {
        const int M = grid.size();
        const int N = grid[ 0 ].size();
        std::vector< int > P( N, std::numeric_limits< int >::max() );
        P[ 0 ] = 0;
        for ( int i = 0; i < M; ++i ) {
            P[ 0 ] = P[ 0 ] + grid[ i ][ 0 ];
            for ( int j = 1; j < N; ++j ) {
                P[ j ] = grid[ i ][ j ]
                       + std::min( P[ j - 1 ], P[ j ] );
            }
        }
        
        return P[ N - 1 ];
    }
};
