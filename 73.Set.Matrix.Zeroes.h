/**
 * Algorithms 73 Set Matrix Zeroes                                       Medium
 * 
 * Given a m x n matrix, if an element is 0, set its entire row and column to 0.
 * Do it in place.
 * 
 * click to show follow up.
 * 
 * Follow up:
 * Did you use extra space?
 * A straight forward solution using O(mn) space is probably a bad idea.
 * A simple improvement uses O(m + n) space, but still not the best solution.
 * Could you devise a constant space solution?
 *
 * Tags: Array
 */

#include <vector>

class Solution {
public:
    /**
     * The straightforward idea is to first copy the matrix.
     * Check the copied matrix for zero entries and set the corresponding
     * row and column zeroes. However this is O(m * n) space.
     *
     * An improvement is to have two vectors recording the rows and columns
     * which need to set zeroes. O(m + n) space.
     *
     * A further improvement is to use the first row and first column rather
     * than creating extra ones. O(1) space.
     */
    void setZeroes( std::vector< std::vector< int > > & matrix ) {
        bool first_row_has_zero = false;
        for ( int i = 0; i < matrix[ 0 ].size(); ++i )
            if ( matrix[ 0 ][ i ] == 0 ) {
                first_row_has_zero = true;
                break;
            }
        bool first_col_has_zero = false;
        for ( int i = 0; i < matrix.size(); ++i )
            if ( matrix[ i ][ 0 ] == 0 ) {
                first_col_has_zero = true;
                break;
            }
        
        for ( int i = 1; i < matrix.size(); ++i ) {
            for ( int j = 1; j < matrix[ i ].size(); ++j ) {
                if ( matrix[ i ][ j ] == 0 ) {
                    matrix[ i ][ 0 ] = 0;
                    matrix[ 0 ][ j ] = 0;
                }
            }
        }
        
        for ( int i = 1; i < matrix.size(); ++i ) {
            for ( int j = 1; j < matrix[ i ].size(); ++j ) {
                if ( matrix[ i ][ 0 ] == 0 || matrix[ 0 ][ j ] == 0 )
                    matrix[ i ][ j ] = 0;
            }
        }
        
        if ( first_row_has_zero )
            for ( int i = 0; i < matrix[ 0 ].size(); ++i )
                matrix[ 0 ][ i ] = 0;
        if ( first_col_has_zero )
            for ( int i = 0; i < matrix.size(); ++i )
                matrix[ i ][ 0 ] = 0;
    }
};
