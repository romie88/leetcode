/**
 * Algorithms 81 Search in Rotated Sorted Array II                      Medium
 *
 * Follow up for "Search in Rotated Sorted Array":
 * What if duplicates are allowed?
 *
 * Would this affect the run-time complexity? How and why?
 * 
 * Write a function to determine if a given target is in the array.
 * 
 * Tags: Array, Binary Search
 * Similar Problems: (H) Search in Rotated Sorted Array
 */

#include <vector>

class Solution {
public:
    bool search( const std::vector< int > & nums, const int target ) {
        return search_iterative( nums, target );
    }
 private:
    /**
     * 1 2 3 3 3 3 3
     *
     * 3 3 3 3 1 2 3
     *       |
     * 3 1 2 3 3 3 3
     *
     * And note that 1 2 can be replaced with 4 5.
     *
     * When duplicates are allowed, nums[ M ] == nums[ R ] != target,
     * we don't know which half of the array to discard. All we can do is
     * to discard nums[ R ]. And discard nums[ R ] is not a problem because
     */
    bool search_iterative( const std::vector< int > & nums, const int target ) {
        int L = 0;
        int R = nums.size() - 1;
        while ( L <= R ) {
            int M = ( L + R ) / 2;
            if ( target == nums[ M ] )
                return true;
            if ( nums[ M ] < nums[ R ] ) {
                if ( target > nums[ M ] && target <= nums[ R ] )
                    L = M + 1;
                else
                    R = M - 1;
            } else if ( nums[ M ] > nums[ R ] ) {
                if ( target < nums[ M ] && target >= nums[ L ] )
                    R = M - 1;
                else
                    L = M + 1;
            } else
		        --R;
        }
        return false;
    }
};
