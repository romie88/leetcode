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
#include <algorithm>

class Solution {
public:
    bool canJump( const std::vector< int > & nums ) {
        return can_jump_greedy_reach( nums );
    }
private:
    /**
     * O(n) runtime, O(1) space
     * My implementation starting from the index n - 1
     * and going backwards
     */
    bool can_jump( const std::vector< int > & nums ) {
        const int n = nums.size();
        int k = n - 1;
        //k is the most left index from which we can reach index n - 1
        //k is initialized with n - 1 since index n - 1 can reach index n - 1
        //now we go backwards starting from n - 2
        for ( int i = n - 2; i >= 0; --i ) {
            if ( i + nums[ i ] >= k ) {
                //if index i can reach index k
                k = i;
            }
        }
        return k == 0;
    }
    /**
     * O(n) runtime, O(1) space
     * Similar to Algorithms 53 Maximum Subarray we maintain local and global
     * optimal values. The global one is the max index we can reach, the local
     * one is the max index we can reach from the current index i which is
     * nums[ i ] + i. Hence global = max( global, local ).
     * 
     * This is a DP problem and if we approach this problem from another angle
     * the runtime could be O(n^2). For example, if we maintain the information
     * about which index i can reach index n - 1.
     */
    bool can_jump_greedy_reach( const std::vector< int > & nums ) {
        const int n = nums.size();
        int reach = 0;
        //reach is the max index we can reach before we check index i
        //and we already checked index 0, ..., i - 1.
        for ( int i = 0; i <= reach && i < n; ++i ) {
            reach = std::max( reach, i + nums[ i ] );
            if ( reach >= n - 1 ) return true;
        }
        return false;
    }
};
