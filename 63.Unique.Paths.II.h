/**
 * Algorithms 63 Unique Paths II                                         Medium
 * 
 * Follow up for "Unique Paths":
 * 
 * Now consider if some obstacles are added to the grids. How many unique paths
 * would there be?
 * 
 * An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 * 
 * For example,
 * There is one obstacle in the middle of a 3x3 grid as illustrated below.
 * 
 * [
 *   [0,0,0],
 *   [0,1,0],
 *   [0,0,0]
 * ]
 * 
 * The total number of unique paths is 2.
 * 
 * Note: m and n will be at most 100.
 * 
 * Tags: Array, Dynamic Programming
 * Similar Problems: (M) Unique Paths
 */

#include <vector>

class Solution {
public:
    int uniquePathsWithObstacles(
            std::vector< std::vector< int > > & obstacleGrid ) {
        return unique_paths_with_obstacles_DP( obstacleGrid );
    }
private:
    int unique_paths_with_obstacles_DP(
            std::vector< std::vector< int > > & obstacleGrid ) {
        int m = obstacleGrid.size();
        if ( m == 0 ) return 0;
        int n = obstacleGrid[ 0 ].size();
        if ( n == 0 ) return 0;
        
        std::vector< int > P( n, 0 );
        P[ n - 1 ] = obstacleGrid[ m - 1 ][ n - 1 ] == 1 ? 0 : 1;
        for ( int i = m - 1; i >= 0; --i ) {
            P[ n - 1 ] = obstacleGrid[ i ][ n - 1 ] == 1 ? 0 : P[ n - 1 ];
            for ( int j = n - 2; j >= 0; --j ) {
                P[ j ] = obstacleGrid[ i ][ j ] == 1
                       ? 0
                       : P[ j + 1 ] + P[ j ];
            }
        }
        return P[ 0 ];
    }
};

