/**
 * Algorithms 85 Maximal Rectangle                                         Hard
 *
 * Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
 * containing all ones and return its area.
 *
 * Tags: Array, Hash Table, Stack, Dynamic Programming
 * Similar Problems: (H) Largest Rectangle in Histogram, (M) Maximal Square
 */

#include <vector>
#include <stack>
#include <algorithm>

class Solution {
public:
    int maximalRectangle( const std::vector< std::vector< char > > & matrix ) {
        return maximal_rectangle_impl_DP_1( matrix );
    }
private:
    /**
     * O( m * n * m * n * m * n ) runtime - naive brute force
     *
     * Enumerate both the upper left corner and lower right corner
     * then check the every potential rectangle.
     */

    /**
     * O( m * n * m * n ) runtime - improved brute force
     */
    int maximal_rectangle_impl_brute_force(
            const std::vector< std::vector< char > > & matrix ) {
        int max_area = 0;
        for ( int i = 0; i < matrix.size(); ++i ) {
            for ( int j = 0; j < matrix[ i ].size(); ++j ) {
                max_area = std::max(
                    max_area,
                    maximal_rectangle_impl_brute_force_helper(
                        matrix, i, j ) );
            }
        }
        return max_area;
    }
    /**
     * helper to search for the maximal rectangle with ( i, j ) as
     * the upper left corner.
     */
    int maximal_rectangle_impl_brute_force_helper(
            const std::vector< std::vector< char > > & matrix,
            int i,
            int j ) {
        const int M = matrix.size();
        const int N = matrix[ 0 ].size();
        int min_width = N + 1;
        int max_area = 0;
        for ( int k = i; k < M && matrix[ k ][ j ] == '1'; ++k ) {
            int z = j;
            while ( z < N && matrix[ k ][ z ] == '1' )
                ++z;
            min_width = std::min( min_width, z - j );
            max_area = std::max( max_area, min_width * ( k - i + 1 ) );
        }
        return max_area;
    }

    /**
     * O( m * n * m ) runtime - DP 1
     *
     * D[ i ][ j ] the maximal number of "1"s starting from ( i, j ) to
     * the left
     *
     * D[ i ][ j ] = k means there are k consecutive '1's from
     * dp[ i ][ j - k + 1 ] to dp[ i ][ j ].
     *
     * At each ( i, j ) check ( i, k ) upwards and downwards to find the
     * maximal height with width D[ i ][ j ].
     */
    int maximal_rectangle_impl_DP_1(
            const std::vector< std::vector< char > > & matrix ) {
        const int M = matrix.size();
        if ( M == 0 ) return 0;
        const int N = matrix[ 0 ].size();
        std::vector< std::vector< int > > D( M, std::vector< int >( N, 0 ) );
        for ( int i = 0; i < M; ++i ) {
            D[ i ][ 0 ] = matrix[ i ][ 0 ] == '1' ? 1 : 0;
            for ( int j = 1; j < N; ++j ) {
                D[ i ][ j ] = matrix[ i ][ j ] == '1'
                            ? ( D[ i ][ j - 1 ] + 1 ) : 0;
            }
        }

        int max_area = 0;
        for ( int i = 0; i < M; ++i ) {
            for ( int j = 0; j < N; ++j ) {
                if ( D[ i ][ j ] > 0 )
                    max_area = std::max( max_area, expand( D, i, j ) );
            }
        }
        return max_area;
    }
    int expand( const std::vector< std::vector< int > > & D,
                int i,
                int j ) {
        int height = 0;
        for ( int k = i - 1; k >= 0 && D[ k ][ j ] >= D[ i ][ j ]; --k )
            ++height;
        for ( int k = i; k < D.size() && D[ k ][ j ] >= D[ i ][ j ]; ++k )
            ++height;
        return D[ i ][ j ] * height;
    }

    /**
     * O( m * n * m ) runtime - DP 2
     *
     * D[ i ][ j ] the maximal number of "1"s starting from ( i, j ) to
     * the left
     *
     * At each ( i, j ) search upwards to find the maximal rectangle with
     * ( i, j ) as the lower right corner.
     */
    int maximal_rectangle_impl_DP_2(
            const std::vector< std::vector< char > > & matrix ) {
        const int M = matrix.size();
        if ( M == 0 ) return 0;
        const int N = matrix[ 0 ].size();
        std::vector< std::vector< int > > D( M, std::vector< int >( N, 0 ) );
        for ( int i = 0; i < M; ++i ) {
            D[ i ][ 0 ] = matrix[ i ][ 0 ] == '1' ? 1 : 0;
            for ( int j = 1; j < N; ++j ) {
                D[ i ][ j ] = matrix[ i ][ j ] == '1'
                            ? ( D[ i ][ j - 1 ] + 1 ) : 0;
            }
        }

        int max_area = 0;
        for ( int i = 0; i < M; ++i ) {
            for ( int j = 0; j < N; ++j ) {
                if ( D[ i ][ j ]  > 0 ) {
                    int min_width = D[ i ][ j ];
                    for ( int k = i; k >= 0; --k ) {
                        min_width = std::min( min_width, D[ k ][ j ] );
                        max_area = std::max( max_area, min_width * ( i - k + 1 ) );
                    }
                }
            }
        }
        return max_area;
    }

    /**
     * O( m * n ) runtime, O( n ) space - DP
     *
     * height[ i ][ j ] is the maximal height of "1"s at ( i, j )
     * left[ i ][ j ] is the left boundary of the rectangle with height[ i ][ j ]
     * right[ i ][ j ] is the right boundary of the rectangle with height[ i ][ j ]
     * the maximal rectangle area at ( i, j ) is
     * height[ i ][ j ] * ( right[ i ][ j ] - left[ i ][ j ] )
     *
     * left[ i ][ j ] = max( left[ i - 1 ][ j ], cur_left )
     * where cur_left points to the leftmost "1" to the left of the current
     * index j; if matrix[ i ][ j ] == '0' then cur_left = j + 1.
     *
     * right[ i ][ j ] = min( right[ i - 1 ][ j ], cur_right )
     * where cur_right points to the rightmost "1" to the right of the current
     * index j; if matrix[ i ][ j ] == '0' then cur_right = j.
     *
     * height[ i ][ j ] = height[ i - 1 ][ j ] + 1 if matrix[ i ][ j ] == '1'
     *                  = 0                        if matrix[ i ][ j ] == '0'
     *
     * Note in the following implementation the two dimension left, right,
     * height are reduced to one dimension.
     */
    int maximal_rectangle_impl_DP(
            const std::vector< std::vector< char > > & matrix ) {
        const int M = matrix.size();
        if ( M == 0 ) return 0;
        const int N = matrix[ 0 ].size();

        int max_area = 0;
        std::vector< int > left( N, 0 );
        std::vector< int > right( N, N );
        std::vector< int > height( N, 0 );
        for ( int i = 0; i < M; ++i ) {
            for ( int j = 0; j < N; ++j ) {
                if ( matrix[ i ][ j ] == '1' )
                    ++height[ j ];
                else
                    height[ j ] = 0;
            }

            int cur_left = 0;
            for ( int j = 0; j < N; ++j ) {
                if ( matrix[ i ][ j ] == '1' )
                    left[ j ] = std::max( left[ j ], cur_left );
                else {
                    left[ j ] = 0;
                    cur_left = j + 1;
                }
            }

            int cur_right = N;
            for ( int j = N - 1; j >= 0; --j ) {
                if ( matrix[ i ][ j ] == '1' )
                    right[ j ] = std::min( right[ j ], cur_right );
                else {
                    right[ j ] = N;
                    cur_right = j;
                }
            }

            for ( int j = 0; j < N; ++j )
               max_area = std::max( max_area,
                                    ( right[ j ] - left[ j ] ) * height[ j ] );
        }
        return max_area;
    }

    /**
     * O( m * n ) runtime, O( n ) space - maximal rectangle in histograms
     */
    int maximal_rectangle_impl_histograms(
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
                max_area, max_rectangle_from_histograms( heights ) );
        }
        return max_area;
    }
    int max_rectangle_from_histograms( const std::vector< int > & heights ) {
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
                max_area = std::max(
                    max_area,
                    heights[ j ] * ( i - ( s.empty() ? 0 : s.top() + 1 ) ) );
            }
        }
        while ( ! s.empty() ) {
            int j = s.top();
            s.pop();
            max_area = std::max(
                    max_area,
                    heights[ j ] * ( i - ( s.empty() ? 0 : s.top() + 1 ) ) );
        }
        return max_area;
    }
};