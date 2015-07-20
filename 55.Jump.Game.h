/**
 * Algorithms 55 Jump Game                                               Medium 
 *
 * Given an array of non-negative integers, you are initially positioned at the
 * first index of the array.
 * 
 * Each element in the array represents your maximum jump length at that
 * position.
 * 
 * Determine if you are able to reach the last index.
 * 
 * For example:
 * A = [2,3,1,1,4], return true.
 * 
 * A = [3,2,1,0,4], return false.
 *
 * Tags: Array, Greedy
 */

#include <vector>

class Solution {
public:
    bool canJump( const std::vector< int > & nums ) {
        return can_jump( nums );
    }
private:
    bool can_jump( const std::vector< int > & nums ) {
        const int n = nums.size();
        int R = 0;//R is the right most index we can reach
        for ( int i = 0; i <= R && i < n; ++i ) {
            if ( R >= n - 1 ) break;
            if ( nums[ i ] + i > R )
                R = nums[ i ] + i;
        }
        return R >= n - 1;
    }
};
