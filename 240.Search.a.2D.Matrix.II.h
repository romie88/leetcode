/**
 * Algoritms 240 Search a 2D Matrix II                                   Medium
 * 
 * Write an efficient algorithm that searches for a value in an m x n matrix.
 * This matrix has the following properties:
 * 
 * * Integers in each row are sorted in ascending from left to right.
 * * Integers in each column are sorted in ascending from top to bottom.
 * 
 * For example,
 * 
 * Consider the following matrix:
 * 
 * [
 *  [1,   4,  7, 11, 15],
 *  [2,   5,  8, 12, 19],
 *  [3,   6,  9, 16, 22],
 *  [10, 13, 14, 17, 24],
 *  [18, 21, 23, 26, 30]
 * ]
 * 
 * Given target = 5, return true.
 * 
 * Given target = 20, return false.
 * 
 * Tags: Divide and Conquer, Binary Search
 * Similar Problems: (M) Search a 2D Matrix
 */

class Solution {
public:
    bool searchMatrix( const std::vector< std::vector< int > > & matrix,
                       const int                                 target ) {
        return search_matrix_impl_DaC( matrix, target );
    }
private:
    /**
     * O( m + n ) runtime
     */
    bool search_matrix_impl_1(
            const std::vector< std::vector< int > > & matrix,
            const int                                 target ) {
        const int m = matrix.size();
        if ( m == 0 ) return false;
        const int n = matrix[ 0 ].size();
        if ( target < matrix[ 0 ][ 0 ] || target > matrix[ m - 1 ][ n - 1 ] )
            return false;
        
        int i = 0;
        int j = n - 1;
        while ( i < m && j >= 0 ) {
            if ( target == matrix[ i ][ j ] ) return true;
            else if ( target < matrix[ i ][ j ] ) --j;
            else ++i;
        }
        return false;
    }
    /**
     * O( ( mn ) ^ log_4( 3 ) ) ) runtime - divide and conquer
     */
    bool search_matrix_impl_DaC(
            const std::vector< std::vector< int > > & matrix,
            const int                                 target ) {
        const int m = matrix.size();
        if ( m == 0 ) return false;
        const int n = matrix[ 0 ].size();
        return search_matrix_impl_DaC_helper( matrix, target, 0, 0, m - 1, n - 1 );
    }
    bool search_matrix_impl_DaC_helper(
            const std::vector< std::vector< int > > & matrix,
            const int                                 target,
            const int                                 r1,
            const int                                 c1,
            const int                                 r2,
            const int                                 c2 ) {
        
        if ( r1 > r2 || c1 > c2 ) return false;
        
        if ( target < matrix[ r1 ][ c1 ] || target > matrix[ r2 ][ c2 ] )
            return false;
        
        if ( r2 - r1 <= 1 && c2 - c1 <= 1 ) {
            for ( int r = r1; r <= r2; ++r )
                for ( int c = c1; c <= c2; ++c )
                    if ( target == matrix[ r ][ c ] ) return true;
            return false;
        }
        
        int mid_r = ( r1 + r2 ) / 2;
        int mid_c = ( c1 + c2 ) / 2;
        if ( target == matrix[ mid_r ][ mid_c ] ) return true;
        else if ( target < matrix[ mid_r ][ mid_c ] )
            return search_matrix_impl_DaC_helper( matrix, target, r1, c1, mid_r, mid_c )
                || search_matrix_impl_DaC_helper( matrix, target, mid_r + 1, c1, r2, mid_c )
                || search_matrix_impl_DaC_helper( matrix, target, r1, mid_c + 1, mid_r, c2 );
        else
            return search_matrix_impl_DaC_helper( matrix, target, mid_r, mid_c, r2, c2 )
                || search_matrix_impl_DaC_helper( matrix, target, mid_r, c1, r2, mid_c - 1 )
                || search_matrix_impl_DaC_helper( matrix, target, r1, mid_c, mid_r - 1, c2 );
    }
};
