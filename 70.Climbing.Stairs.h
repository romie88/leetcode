/**
 * Algorithms 70 Climbing Stairs                                           Easy
 * 
 * You are climbing a stair case. It takes n steps to reach to the top.
 * 
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can
 * you climb to the top?
 * 
 * Tags: Dynamic Programming
 */

#include <stdexcept>

class Solution {
public:
    int climbStairs( int n ) {
        if ( n < 0 ) throw std::invalid_argument( "n < 0" );
        if ( n == 0 ) return 0;
        int i1 = 1;
        int i2 = 1;
        for ( int i = 1; i < n; ++i ) {
            int tmp = i1 + i2;
            i1 = i2;
            i2 = tmp;
        }
        return i2;
    }
};
