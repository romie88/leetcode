/**
 * Algorithms 221 Maximal Square                                         Medium
 *
 * Given a 2D binary matrix filled with 0's and 1's, find the largest square
 * containing all 1's and return its area.
 *
 * For example, given the following matrix:
 *
 * 1 0 1 0 0
 * 1 0 1 1 1
 * 1 1 1 1 1
 * 1 0 0 1 0
 *
 * Return 4.
 *
 * Credits:
 * Special thanks to @Freezen for adding this problem and creating all test
 * cases.
 *
 * Tags: Dynamic Programming
 * Similar Problems: (H) Maximal Rectangle
 */

#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    int maximalSquare( const std::vector< std::vector< char > > & matrix ) {
        return maximal_square_impl_DP( matrix );
    }
private:
    /**
     * O( m * n ) runtime, O( n ) space - maximal rectangle in histograms
     */
    int maximal_square_impl_histogram(
            const std::vector< std::vector< char > > & matrix ) {
        const int M = matrix.size();
        if ( M == 0 ) return 0;

        const int N = matrix[ 0 ].size();
        std::vector< int > heights( N, 0 );
        int max_area = 0;
        for ( int i = 0; i < M; ++i ) {
            for ( int j = 0; j < N; ++j ) {
                if ( matrix[ i ][ j ] == '1' )
                    ++heights[ j ];
                else
                    heights[ j ] = 0;
            }
            max_area = std::max(
                max_area, max_square_from_histograms( heights ) );
        }
        return max_area;
    }
    int max_square_from_histograms( const std::vector< int > & heights ) {
        const int N = heights.size();
        int max_area = 0;
        std::stack< int > s;
        int i = 0;
        while ( i < N ) {
            if ( s.empty() || heights[ s.top() ] < heights[ i ] )
                s.push( i++ );
            else {
                int j = s.top();
                s.pop();
                int side_len = std::min(
                    heights[ j ], ( i - ( s.empty() ? 0 : s.top() + 1 ) ) );
                max_area = std::max( max_area, side_len * side_len );
            }
        }
        while ( ! s.empty() ) {
            int j = s.top();
            s.pop();
            int side_len = std::min(
                    heights[ j ], ( i - ( s.empty() ? 0 : s.top() + 1 ) ) );
            max_area = std::max( max_area, side_len * side_len );
        }
        return max_area;
    }

    /**
     * O( m * n ) runtime, O( n ) space - DP
     *
     * Exactly the same as Algorithms 85 Maximal Rectangle
     */
    int maximal_square_impl_DP(
            const std::vector< std::vector< char > > & matrix ) {
        const int M = matrix.size();
        if ( M == 0 ) return 0;

        const int N = matrix[ 0 ].size();
        std::vector< int > height( N, 0 );
        std::vector< int > left( N, 0 );
        std::vector< int > right( N, N );
        int max_len = 0;
        for ( int i = 0; i < M; ++i ) {
            int cur_right = N;
            for ( int j = N - 1; j >= 0; --j ) {
                if ( matrix[ i ][ j ] == '1' )
                    right[ j ] = std::min( right[ j ], cur_right );
                else {
                    right[ j ] = N;
                    cur_right = j;
                }
            }

            int cur_left = 0;
            for ( int j = 0; j < N; ++j ) {
                if ( matrix[ i ][ j ] == '1' ) {
                    left[ j ] = std::max( left[ j ], cur_left );
                    ++height[ j ];
                } else {
                    height[ j ] = 0;
                    left[ j ] = 0;
                    cur_left = j + 1;
                }
                max_len = std::max(
                        max_len,
                        std::min( height[ j ], right[ j ] - left[ j ] ) );
            }
        }
        return max_len * max_len;
    }

    /**
     * O( m * n ) runtime, O( m * n ) space - another DP
     *
     * P[ i ][ j ] the maximal size of the square which ( i, j ) as the lower
     * right corner.
     *
     * For the topmost row i = 0 and the leftmost column j = 0, P[ i ][ j ] =
     * matrix[ i ][ j ].
     *
     * Now check for P[ i ][ j ] for i > 0 and j > 0.
     *
     * If matrix[ i ][ j ] == '0' then P[ i ][ j ] = 0.
     *
     * If matrix[ i ][ j ] == '1' let's see an example,
     * matrix = [ [ 0, 1 ], [ 1, 1 ] ]. From above P[ 0 ][ 0 ] = 0,
     * P[ 0 ][ 1 ] = 1, P[ 1 ][ 0 ] = 1. To give a square of size larger
     * than 1 in P[ 1 ][ 1 ], all of its three neighbors should be non-zero.
     * In this case, the left-up neighbor P[ 0 ][ 0 ] = 0, so P[ 1 ][ 1 ] can
     * only be 1 which means that it contains the square of itself.
     *
     * P[ i ][ j ] = min( P[ i - 1 ][ j ], P[ i ][ j - 1 ], P[ i - 1 ][ j - 1 ] ) + 1
     *
     * Summarize as the following
     *
     * P[ 0 ][ j ] = matrix[ 0 ][ j ] (topmost row)
     * P[ i ][ 0 ] = matrix[ i ][ 0 ] (leftmost column)
     * For i > 0 and j > 0,
     * if matrix[ i ][ j ] == '0', then P[ i ][ j ] = 0
     * if matrix[ i ][ j ] == '1', then P[ i ][ j ] = min( P[ i - 1 ][ j ],
     * P[ i ][ j - 1 ], P[ i - 1 ][ j - 1 ] ) + 1
     */
    int maximal_square_impl_DP_1(
            const std::vector< std::vector< char > > & matrix ) {
        const int M = matrix.size();
        if ( M == 0 ) return 0;
        const int N = matrix[ 0 ].size();
        std::vector< std::vector< int > > P( M, std::vector< int >( N, 0 ) );
        int max_len = 0;
        for ( int j = 0; j < N; ++j ) {
            P[ 0 ][ j ] = matrix[ 0 ][ j ] - '0';
            max_len = std::max( max_len, P[ 0 ][ j ] );
        }
        for ( int i = 1; i < M; ++i ) {
            P[ i ][ 0 ] = matrix[ i ][ 0 ] - '0';
            max_len = std::max( max_len, P[ i ][ 0 ] );
        }
        for ( int i = 1; i < M; ++i ) {
            for ( int j = 1; j < N; ++j ) {
                if ( matrix[ i ][ j ] == '1' ) {
                    P[ i ][ j ] = std::min( P[ i - 1 ][ j - 1 ],
                                  std::min( P[ i - 1 ][ j ],
                                            P[ i ][ j - 1 ] ) ) + 1;
                    max_len = std::max( max_len, P[ i ][ j ] );
                }
            }
        }
        return max_len * max_len;
    }
    /**
     * O( m * n ) runtime, O( m ) space - space optimized DP
     */
    int maximal_square_impl_DP_2(
            const std::vector< std::vector< char > > & matrix ) {
        const int M = matrix.size();
        if ( M == 0 ) return 0;
        const int N = matrix[ 0 ].size();
        std::vector< int > pre( M, 0 );
        std::vector< int > cur( M, 0 );
        int max_len = 0;
        for ( int i = 0; i < M; ++i ) {
            pre[ i ][ 0 ] = matrix[ i ][ 0 ] - '0';
            max_len = std::max( max_len, pre[ i ][ 0 ] );
        }
        for ( int j = 1; j < N; ++j ) {
            cur[ 0 ] = matrix[ 0 ][ j ] - '0';
            max_len = std::max( max_len, cur[ 0 ] );
            for ( int i = 1; i < M; ++i ) {
                if ( matrix[ i ][ j ] == '1' ) {
                    cur[ i ] = std::min( cur[ i - 1 ],
                               std::min( pre[ i ], pre[ i - 1 ] ) ) + 1;
                    max_len = std::max( max_len, cur[ i ] );
                }
            }
            cur.swap( pre );
        }
        return max_len * max_len;
    }
    /**
     * O( m * n ) runtime, O( m ) space - an ultimate space optimized DP
     */
    int maximal_square_impl_DP_3(
            const std::vector< std::vector< char > > & matrix ) {
        const int M = matrix.size();
        if ( M == 0 ) return 0;
        const int N = matrix[ 0 ].size();

        int max_len = 0;
        int pre = 0;
        std::vector< int > dp( M + 1, 0 );
        for ( int j = 0; j < N; ++j ) {
            for ( int i = 1; i <= M; ++i ) {
                int temp = dp[ i ];
                if ( matrix[ i - 1 ][ j ] == '1' ) {
                    //dp[ i ]     --- pre[ i ]
                    //pre         --- pre[ i - 1 ]
                    //dp[ i - 1 ] --- cur[ i - 1 ]
                    dp[ i ] = std::min( dp[ i - 1 ], std::min( dp[ i ], pre ) ) + 1;
                    max_len = std::max( max_len, dp[ i ] );
                } else
                    dp[ i ] = 0;

                pre = temp;
            }
        }
        return max_len * max_len;
    }
};