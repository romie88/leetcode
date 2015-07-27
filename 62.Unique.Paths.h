/**
 * Algorithms 62 Unique Paths                                            Medium
 * 
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in
 * the diagram below).
 * 
 * The robot can only move either down or right at any point in time. The robot
 * is trying to reach the bottom-right corner of the grid (marked 'Finish' in
 * the diagram below).
 * 
 * How many possible unique paths are there?
 * 
 * |S| | | | | | |
 * ---------------
 * | | | | | | | |
 * ---------------
 * | | | | | | |F|
 * 
 * Above is a 3 x 7 grid. How many possible unique paths are there?
 *
 * Note: m and n will be at most 100.
 * 
 * Tags: Array, Dynamic Programming
 * Similar Problems: (M) Unique Paths II, (M) Minimum Path Sum, (H) Dungeon Game
 */

#include <vector>

class Solution {
public:
    int uniquePaths(int m, int n) {
        return unique_paths_by_combination( m, n );
    }
private:
    /**
     * O( C( m + n, m ) ) runtime, O( m + n ) space - Backtracking
     * 
     * The backtracking algorithm explores all the possible paths.
     * 
     * The total unique paths at grid ( r, c ) to the finish grid are
     * equal to the sum of total unique paths from the grid to the right
     * and the grid below.
     * 
     * Since the backtracking algorithm explores all possibilities, its
     * runtime complexity is equivalent to the total number of paths
     * C( m + n, m ).
     *
     * The space complexity is O( m + n ) due to the recursion that goes at
     * most m + n level deep.
     */
    int unique_paths_backtracking_impl( int r, int c, int m, int n ) {
        if ( r == m - 1 && c == n - 1 ) return 1;
        if ( r >= m || c >= n ) return 0;
        return unique_paths_backtracking_impl( r + 1, c, m, n )
             + unique_paths_backtracking_impl( r, c + 1, m, n );
    }
    int unique_paths_backtracking( int m, int n ) {
        return unique_paths_backtracking_impl( 0, 0, m, n );
    }
    
    /**
     * Improved backtracking using memoization
     */
    int unique_paths_backtracking_memo_impl( int r, int c, int m, int n,
                                        std::vector< std::vector< int > > & P ) {
        if ( r == m - 1 && c == n - 1 ) return 1;
        if ( r >= m || c >= n ) return 0;
        if ( P[ r + 1 ][ c ] == -1 )
            P[ r + 1 ][ c ] = unique_paths_backtracking_memo_impl( r + 1, c, m, n, P );
        if ( P[ r ][ c + 1 ] == -1 )
            P[ r ][ c + 1 ] = unique_paths_backtracking_memo_impl( r, c + 1, m, n, P );
        return P[ r + 1 ][ c ] + P[ r ][ c + 1 ];
    }
    int unique_paths_backtracking_memo( int m, int n ) {
        //note the dimension is m + 1 by n + 1
        std::vector< std::vector< int > >
            P( m + 1, std::vector< int >( n + 1, -1 ) );
        return unique_paths_backtracking_memo_impl( 0, 0, m, n, P );
    }
    
    /**
     * O( m * n ) runtime, O( m * n ) space - Bottom-up dynamic programming
     */
    int unique_paths_DP( int m, int n ) {
        std::vector< std::vector< int > >
            P( m + 1, std::vector< int >( n + 1, 0 ) );
        P[ m ][ n - 1 ] = 1;
        for ( int i = m - 1; i >= 0; --i ) {
            for ( int j = n - 1; j >= 0; --j ) {
                P[ i ][ j ] = P[ i + 1 ][ j ] + P[ i ][ j + 1 ];
            }
        }
        return P[ 0 ][ 0 ];
    }
    
    int unique_paths_DP2( int m, int n ) {
        std::vector< int > P( n, 0 );
        P[ n - 1 ] = 1;
        for ( int i = m - 1; i >= 0; --i ) {
            for ( int j = n - 2; j >= 0; --j ) {
                P[ j ] = P[ j ] + P[ j + 1 ];
            }
        }
        return P[ 0 ];
    }

    /**
     * O( m ) runtime, O( 1 ) space
     * 
     * Totally the robot needs to move m - 1 steps down and n - 1 steps right.
     * Thus the number of unique paths is C( m + n - 2, m - 1 ).
     */
    int unique_paths_by_combination( int m, int n ) {
        int i = 1;
        int j = n;
        long long result = 1;
        while ( i < m ) {
            result *= j;
            result /= i;
            ++j; ++i;
        }
        return result;
    }
};
