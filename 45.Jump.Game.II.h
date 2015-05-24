/**
 * Algorithms 45 Jump Game II                                              Hard
 *
 * Given an array of non-negative integers, you are initially positioned at the
 * first index of the array.
 *
 * Each element in the array represents your maximum jump length at that
 * position.
 * 
 * Your goal is to reach the last index in the minimum number of jumps.
 *
 * For example:
 * Given array A = [2,3,1,1,4]
 *
 * The minimum number of jumps to reach the last index is 2. (Jump 1 step from
 * index 0 to 1, then 3 steps to the last index.)
 *
 * Tags: Array, Greedy
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int jump( const std::vector< int > & nums ) {
        return jump_impl( nums );
    }
private:
    /**
     * DP will result in O(n^2) runtime
     * Greedy is O(n) runtime
     */
    int jump_impl( const std::vector< int > & nums ) {
        int n = nums.size();
        int reach = 0;
        int prev_reach = 0;
        int steps = 0;
        for ( int i = 0; i <= reach && i < n; ++i ) {
            if ( i > prev_reach ) {
                prev_reach = reach;
                ++steps;
            }
            reach = std::max( reach, i + nums[ i ] );
        }
        
        return  reach < n - 1 ? 0 : steps;
    }
};
