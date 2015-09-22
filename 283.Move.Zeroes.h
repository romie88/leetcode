/**
 * Algorithms 283 Move Zeroes                                              Easy
 * 
 * Given an array nums, write a function to move all 0's to the end of it while
 * maintaining the relative order of the non-zero elements.
 * 
 * For example, given nums = [0, 1, 0, 3, 12], after calling your function,
 * nums should be [1, 3, 12, 0, 0].
 * 
 * Note:
 * 
 * 1. You must do this in-place without making a copy of the array.
 * 2. Minimize the total number of operations.
 * 
 * Credits:
 * Special thanks to @jianchao.li.fighter for adding this problem and creating
 * all test cases.
 * 
 * Tags: Array, Two Pointers
 * Similar Problems: (E) Remove Element
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    void moveZeroes( std::vector< int > & nums ) {
#if 0
        int j = 0;
        for ( int i = 0; i < nums.size(); ++i ) {
            if ( nums[ i ] != 0 )
                nums[ j++ ] = nums[ i ];
        }
        for ( ; j < nums.size(); ++j )
            nums[ j ] = 0;
#endif
#if 0
        int j = 0;
        for ( int i = 0; i < nums.size(); ++i )
            if ( nums[ i ] != 0 )
                std::swap( nums[ i ], nums[ j++ ] );
#endif
        //optimized
        int j = 0;
        for ( ; j < nums.size() && nums[ j ] != 0; ++j )
            ;
        //now j points to the first zero
        int i = j + 1;
        for ( ; i < nums.size() && nums[ i ] == 0; ++i )
            ;
        //now i points to the first non-zero number after j
        for ( ; i < nums.size(); ++i )
            if ( nums[ i ] != 0 )
                std::swap( nums[ i ], nums[ j++ ] );
    }
};
