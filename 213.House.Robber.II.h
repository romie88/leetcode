/**
 * 213 House Robber II                                                   Medium
 * 
 * Note: This is an extension of House Robber.
 * 
 * After robbing those houses on that street, the thief has found himself a new
 * place for his thievery so that he will not get too much attention. This time,
 * all houses at this place are arranged in a circle. That means the first house
 * is the neighbor of the last one. Meanwhile, the security system for these
 * houses remain the same as for those in the previous street.
 * 
 * Given a list of non-negative integers representing the amount of money of
 * each house, determine the maximum amount of money you can rob tonight
 * without alerting the police.
 * 
 * Credits:
 * 
 * Special thanks to @Freezen for adding this problem and creating all test
 * cases.
 * 
 * Tags: Dynamic Programming
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int rob( std::vector< int > & nums ) {
        if ( nums.size() == 0 ) return 0;
        if ( nums.size() == 1 ) return nums[ 0 ];
        if ( nums.size() == 2 ) return std::max( nums[ 0 ], nums[ 1 ] );
        
        //max money by robbing from house 0 to house n - 2
        int m1 = rob( nums, 0, nums.size() - 2 );
        //max money by robbing from house 1 to house n - 1
        int m2 = rob( nums, 1, nums.size() - 1 );
        return std::max( m1, m2 );
    }
private:
    int rob( const std::vector< int > & nums,
             const int                  start,
             const int                  end ) {
        const int n = end - start + 1;
        if ( n == 2 ) return std::max( nums[ start ], nums[ end ] );
        
        int m1 = nums[ start ];
        int m2 = std::max( nums[ start ], nums[ start + 1 ] );
        for ( int i = start + 2; i <= end; ++i ) {
            int m = std::max( m1 + nums[ i ], m2 );
            m1 = m2;
            m2 = m;
        }
        return m2;
    }
};
