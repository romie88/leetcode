/**
 * Algorithms 34 Search for a Range                                      Medium
 * 
 * Given a sorted array of integers, find the starting and ending position of a
 * given target value.
 * 
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * 
 * If the target is not found in the array, return [-1, -1].
 * 
 * For example,
 * 
 * Given [5, 7, 7, 8, 8, 10] and target value 8,
 * return [3, 4].
 * 
 * Tags: Array, Binary Search
 * Similar Problems: (M) Search Insert Position
 */

#include <vector>

class Solution {
public:
    /**
     * O( log n ) runtime, O( 1 ) space
     */
    std::vector< int > searchRange( const std::vector< int > & nums, int target ) {
        std::vector< int > result( 2, -1 );
        int left = search_left( nums, target );
        if ( left == nums.size() || nums[ left ] != target )
            return result;
        result[ 0 ] = left;
        int right = search_right( nums, target );
        result[ 1 ] = right - 1;
        return result;
#if 0
        std::vector< int > result{ -1, -1 };
        int left  = search_leftmost_insert_index( nums, target );
        int right = search_rightmost_insert_index( nums, target );
        if ( left != right ) {
            result[ 0 ] = left;
            result[ 1 ] = right - 1;
        }
        return result;
#endif
    }
private:
     /**
      * The key is to handle the case when target == nums[ M ].
      * 
      * To search the left most insert position, if target == nums[ M ],
      * we must keep looking toward the left and at the end L is the left-most
      * index to insert target before.
      * 
      * To search the right most insert position, if target == nums[ M ],
      * we must keep looking toward the right and at the end L is the right-most
      * index to insert target before ( L = R + 1 ).
      */
    int search_left( const std::vector< int > & nums, int target ) {
        int L = 0;
        int R = nums.size() - 1;
        while ( L <= R ) {
            int M = L + ( R - L ) / 2;
            if ( nums[ M ] >= target ) R = M - 1;
            else                       L = M + 1;
        }
        return L;
    }
    int search_right( const std::vector< int > & nums, int target ) {
        int L = 0;
        int R = nums.size() - 1;
        while ( L <= R ) {
            int M = L + ( R - L ) / 2;
            if ( nums[ M ] > target ) R = M - 1;
            else                      L = M + 1;
        }
        return L;
    }
};
