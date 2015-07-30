/**
 * Algorithms 74 Search a 2D Matrix                                      Medium
 * 
 * Write an efficient algorithm that searches for a value in an m x n matrix.
 * This matrix has the following properties:
 * 
 * * Integers in each row are sorted from left to right.
 * * The first integer of each row is greater than the last integer of the
 *   previous row.
 * 
 * For example,
 * 
 * Consider the following matrix:
 *
 * [
 *   [1,   3,  5,  7],
 *   [10, 11, 16, 20],
 *   [23, 30, 34, 50]
 * ]
 * Given target = 3, return true.
 *
 * Tags: Array, Binary Search
 * Similar Problems: (M) Search a 2D Matrix II
 */

#include <vector>

class Solution {
public:
    bool searchMatrix( const std::vector< std::vector< int > > & matrix,
                       const int                                 target ) {
        return search_matrix( matrix, target );
    }
private:
    bool search_matrix( const std::vector< std::vector< int > > & matrix,
                        const int                                 target ) {
        const int m = matrix.size();
        const int n = matrix[ 0 ].size();
        int L = 0;
        int R = m - 1;
        while ( L <= R ) {
            int M = ( L + R ) / 2;
            if ( matrix[ M ][ n - 1 ] == target )
                return true;
            else if ( target < matrix[ M ][ n - 1 ] )
                R = M - 1;
            else
                L = M + 1;
        }
        if ( L == m ) return false;
        
        int r = L;
        L = 0;
        R = n - 1;
        while ( L <= R ) {
            int M = ( L + R ) / 2;
            if ( matrix[ r ][ M ] == target )
                return true;
            else if ( target < matrix[ r ][ M ] )
                R = M - 1;
            else
                L = M + 1;
        }
        return false;
    }
};
