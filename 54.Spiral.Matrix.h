/**
 * Algorithms 54 Spiral Matrix                                           Medium
 *
 * Given a matrix of m x n elements (m rows, n columns), return all elements of
 * the matrix in spiral order.
 * 
 * For example,
 * Given the following matrix:
 * 
 * [
 *  [ 1, 2, 3 ],
 *  [ 4, 5, 6 ],
 *  [ 7, 8, 9 ]
 * ]
 * You should return [1,2,3,6,9,8,7,4,5].
 *
 * Tags: Array
 * Similar Problems: (M) Spiral Matrix II
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector< int > spiralOrder(
            std::vector< std::vector< int > > & matrix ) {
        return spiral_order_impl_2( matrix );
    }
private:
    std::vector< int > spiral_order_impl_1(
            const std::vector< std::vector< int > > & matrix ) {
        std::vector< int > result;
        int m = matrix.size();
        if ( m == 0 ) return result;
        int n = matrix[ 0 ].size();
        const int max_i = ( std::min( m, n ) + 1 ) / 2;
        for ( int i = 0; i < max_i; ++i ) {
            if ( n == 1 ) {
                for ( int k = i; k < i + m; ++k )
                    result.push_back( matrix[ k ][ i ] );
            } else if ( m == 1 ) {
                for ( int k = i; k < i + n; ++k )
                    result.push_back( matrix[ i ][ k ] );
            } else {
                for ( int k = i; k < i + n; ++k )
                    result.push_back( matrix[ i ][ k ] );
                for ( int k = i + 1; k < i + m - 1; ++k )
                    result.push_back( matrix[ k ][ i + n - 1 ] );
                for ( int k = i + n - 1; k >= i; --k )
                    result.push_back( matrix[ i + m - 1 ][ k ] );
                for ( int k = i + m - 2; k > i; --k )
                    result.push_back( matrix[ k ][ i ] );
                m -= 2;
                n -= 2;
            }
        }
        return result;
    }
    std::vector< int > spiral_order_impl_2(
            const std::vector< std::vector< int > > & matrix ) {
        std::vector< int > result;
        int m = matrix.size();
        if ( m == 0 ) return result;
        int n = matrix[ 0 ].size();
        int row = 0;
        int col = -1;
        while ( true ) {
            for ( int i = 0; i < n; ++i )
                result.push_back( matrix[ row ][ ++col ] );
            if ( --m == 0 || n == 0 ) break;
            for ( int i = 0; i < m; ++i )
                result.push_back( matrix[ ++row ][ col ] );
            if ( --n == 0 ) break;
            for ( int i = 0; i < n; ++i )
                result.push_back( matrix[ row ][ --col ] );
            if ( --m == 0 ) break;
            for ( int i = 0; i < m; ++i )
                result.push_back( matrix[ --row ][ col ] );
            if ( --n == 0 ) break;
        }
        return result;
    }
};
