/**
 * Algorithms 59 Spiral Matrix II                                        Medium
 *
 * Given an integer n, generate a square matrix filled with elements from 1 to
 * n2 in spiral order.
 * 
 * For example,
 * Given n = 3,
 * 
 * You should return the following matrix:
 * [
 *  [ 1, 2, 3 ],
 *  [ 8, 9, 4 ],
 *  [ 7, 6, 5 ]
 * ]
 *
 * Tags: Array
 * Similar Problems: (M) Spiral Matrix
 */

#include <vector>

class Solution {
public:
    std::vector< std::vector< int > > generateMatrix( const int n ) {
        return generate_matrix_impl_2( n );
    }
private:
    std::vector< std::vector< int > > generate_matrix_impl_1( int n ) {
        std::vector< std::vector< int > >
                matrix( n, std::vector< int >( n, 0 ) );
        int k = 1;
        const int max_i = ( n + 1 ) / 2;
        for ( int i = 0; i < max_i; ++i ) {
            if ( n == 1 ) matrix[ i ][ i ] = k++;
            else {
                for ( int j = i; j < i + n; ++j )
                    matrix[ i ][ j ] = k++;
                for ( int j = i + 1; j < i + n - 1; ++j )
                    matrix[ j ][ i + n - 1 ] = k++;
                for ( int j = i + n - 1; j >= i; --j )
                    matrix[ i + n - 1 ][ j ] = k++;
                for ( int j = i + n - 2; j > i; --j )
                    matrix[ j ][ i ] = k++;
            }
            n -= 2;
        }
        return matrix;
    }
    std::vector< std::vector< int > > generate_matrix_impl_2( int n ) {
        std::vector< std::vector< int > >
                matrix( n, std::vector< int >( n, 0 ) );
        int row = 0;
        int col = -1;
        int k   = 1;
        while ( true ) {
            if ( n == 0 ) break;
            for ( int i = 0; i < n; ++i )
                matrix[ row ][ ++col ] = k++;
            if ( --n == 0 ) break;
            for ( int i = 0; i < n; ++i )
                matrix[ ++row ][ col ] = k++;
            for ( int i = 0; i < n; ++i )
                matrix[ row ][ --col ] = k++;
            if ( --n == 0 ) break;
            for ( int i = 0; i < n; ++i )
                matrix[ --row ][ col ] = k++;
        }
        return matrix;
    }
};
