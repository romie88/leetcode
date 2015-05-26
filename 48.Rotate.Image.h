/**
 * Algorithms 48 Rotate Image                                            Medium
 * 
 * You are given an n x n 2D matrix representing an image.
 * 
 * Rotate the image by 90 degrees (clockwise).
 * 
 * Follow up:
 * Could you do this in-place?
 * 
 * Tags: Array
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    void rotate( std::vector< std::vector< int > > & matrix ) {
        rotate_layer_by_layer( matrix );
    }
private:
    /**
     * O(n^2) runtime, O(1) space - my naive pixel by pixel rotation 
     * implementation
     * Let's consider a small example.
     * 1 2 3     7 4 1
     * 4 5 6 --> 8 5 2
     * 7 8 9     9 6 3
     * Obviously the center of the rotation is 5 with coordinates ( 1, 1 )
     * Rotate 1 from ( 0, 0 ) to ( 0, 2 ).
     * First we need to convert coordinate ( i, j ) to be the coordinates
     * with ( 1, 1 ) as the origin.
     * Denoate ( i_m, j_m ) to be the coordinates. For example, n = 3,
     * ( i_m, j_m ) = ( 1, 1 ), n = 4, ( i_m, j_m ) = ( 1.5, 1.5 ).
     * Step 1. Convert ( i, j ) to be the coordinates with ( i_m, j_m ) as the
     *         origin. ( i, j ) --> ( j - j_m, i_m - i )
     *         This can be obtained by observe ( 0, 0 ) --> ( -1, 1 ).
     *         Note ( i, j ) where i is the actually value of y-axis in the new
     *         coordinate system.
     * Step 2. Rotate ( j - j_m, i_m - i ) 90 degrees clockwise
     *         Generally ( x, y ) in polar system, ( r cos v, r sin v )
     *         Rotate 90 degrees clockwise ( r cos v - 90, r sin v - 90 )
     *         ( x, y ) --> ( y, -x ).
     * Step 3. With Step 2, ( i, j ) --> ( j - j_m, i_m - i ) --> ( i_m - i, j_m - j )
     *         We need to convert the result so far back to the original coordinate
     *         system. From Step 1. (  x, y ) --> ( i_m - y, x + j_m )
     *         Thus ( i_m - i, j_m - j ) --> ( i_m - j_m + j, i_m - i + j_m )
     *         i.e. ( j, n - 1 - i ) where i_m == j_m and i_m + j_m = n - 1
     * Finally we know ( i, j ) --> ( j, n - 1 - i )
     */
    void rotate_pixel_by_pixel( std::vector< std::vector< int > > & m ) {
        const int n = m.size();
        int s = n;
        int tmp[ 4 ];
        for ( int i = 0; i < n / 2; ++i, s -= 2 ) {
            const int n2 = i + s - 1;
            for ( int j = i; j < n2; ++j ) {
                int x = i;
                int y = j;
                for ( int k = 0; k < 4; ++k ) {
                    tmp[ k ] = m[ x ][ y ];
                    int prev_x = x;
                    x = y;
                    y = n - 1 - prev_x;
                }
                x = j;
                y = n - 1 - i;
                for ( int k = 0; k < 4; ++k ) {
                    m[ x ][ y ] = tmp[ k ];
                    int prev_x = x;
                    x = y;
                    y = n - 1 - prev_x;
                }
            }
        }
    }
    /**
     * O(n^2) runtime, O(1) space - matrix operation
     * 
     * Step 1 flip matrix along the minor diagonal
     * Step 2 flip matrix along the middle x-axis
     *
     * 1 2 --> 4 2 --> 3 1
     * 3 4     3 1     4 2
     * 
     * Step 1 ( i, j ) <--> ( n - 1 - j, n - 1 - i )
     * Step 2 ( i, j ) <--> ( n - 1 - i, j )
     */
    void rotate_matrix_op( std::vector< std::vector< int > > & m ) {
        const int n = m.size();
        //step1 flip along the minor diagonal
        for ( int i = 0; i < n - 1; ++i ) {
            for ( int j = 0; j < n - 1 - i; ++j ) {
                std::swap( m[ i ][ j ], m[ n - 1 - j ][ n - 1 - i ] );
            }
        }
        //step 2 flip along the middle x-axis
        for ( int i = 0; i < n / 2; ++i ) {
            for ( int j = 0; j < n; ++j ) {
                std::swap( m[ i ][ j ], m[ n - 1 - i ][ j ] );
            }
        }
    }
    /**
     * O(n^2) runtime, O(1) space - matrix operation
     * 
     * The inner part of the two loops can be derived by drawing a picture
     * 
     * ( i, i ) ( i, j )                                         ( i, n - 1 - i )
     *
     *                                                           ( j, n - 1 - i )
     *
     *
     * ( n - 1 - j, i )
     *
     * ( n - 1 - i, i )         ( n - 1 - i, n - 1 - j ) ( n - 1 - i, n - 1 - i )
     */
    void rotate_layer_by_layer( std::vector< std::vector< int > > & m ) {
        const int n = m.size();
        for ( int i = 0; i < n / 2; ++i ) {
            for ( int j = i; j < n - i - 1; ++j ) {
                int tmp = m[ i ][ j ];
                m[ i ][ j ] = m[ n - 1 - j ][ i ];
                m[ n - 1 - j ][ i ] = m[ n - 1 - i ][ n - 1 - j ];
                m[ n - 1 - i ][ n - 1 - j ] = m[ j ][ n - 1 - i ];
                m[ j ][ n - 1 - i ] = tmp;
            }
        }
    }
};
