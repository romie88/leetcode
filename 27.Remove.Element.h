/**
 * Algorithms 27 Remove Element                                           Easy
 *
 * Given an array and a value, remove all instances of that value in place and
 * return the new length.
 *
 * The order of elements can be changed. It doesn't matter what you leave
 * beyond the new length.
 *
 * Tags: Array, Two Pointers
 */

#include <vector>

class Solution {
public:
    int removeElement( std::vector< int > & nums, int val ) {
        int j = 0;
        for ( int i = 0; i < nums.size(); ++i ) {
            if ( nums[ i ] != val )
                nums[ j++ ] = nums[ i ];
        }
        return j;
    }
};
