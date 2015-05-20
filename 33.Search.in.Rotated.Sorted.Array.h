/**
 * Algorithms 33 Search in Rotated Sorted Array                            Hard
 * 
 * Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 * 
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 * 
 * You are given a target value to search. If found in the array return its
 * index, otherwise return -1.
 * 
 * You may assume no duplicate exists in the array.
 * 
 * Tags: Array, Binary Search
 */

#include <vector>

class Solution {
public:
    int search( const std::vector< int > & nums, const int target ) {
        return search_iterative( nums, target );
    }
 private:
    /**
     * The key observation is that by comparing nums[ M ] with nums[ R ]
     * we know half of the array is sorted and we do not need to check
     * if the array is rotated or not at all.
     * When we know which half is sorted, we just need to check if target
     * is within the range of the sorted half or not and discard half of
     * the array.
     * And the base case input like [ 4, 2 ] or [ 4 ] need to be verified.
     */
    int search_iterative( const std::vector< int > & nums, const int target ) {
        int L = 0;
        int R = nums.size() - 1;
        while ( L <= R ) {
            int M = ( L + R ) / 2;
            if ( target == nums[ M ] )
                return M;
            if ( nums[ M ] < nums[ R ] ) {
                if ( target > nums[ M ] && target <= nums[ R ] )
                    L = M + 1;
                else
                    R = M - 1;
            } else {
                if ( target < nums[ M ] && target >= nums[ L ] )
                    R = M - 1;
                else
                    L = M + 1;
            }
        }
        return -1;
    }
};
