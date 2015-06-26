/**
 * 198 House Robber                                                        Easy
 * 
 * You are a professional robber planning to rob houses along a street. Each
 * house has a certain amount of money stashed, the only constraint stopping
 * you from robbing each of them is that adjacent houses have security system
 * connected and it will automatically contact the police if two adjacent
 * houses were broken into on the same night.
 * 
 * Given a list of non-negative integers representing the amount of money of
 * each house, determine the maximum amount of money you can rob tonight
 * without alerting the police.
 * 
 * Credits:
 * 
 * Special thanks to @ifanchu for adding this problem and creating all test
 * cases. Also thanks to @ts for adding additional test cases.
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
        
        //Let M[ i ] be the max money we can get by robbing from house 0 to house i
        //M[ i ] = max{ M[ i - 1 ], M[ i - 2 ] + nums[ i ] }
        //Note that M[ i - 1 ] is the max money by robbing house[ 0 ... i - 1 ]
        //If by achieving M[ i - 1 ] we robbed house i - 1, then we cannot
        //rob house i. If not, M[ i - 1 ] == M[ i ]
        int m1 = nums[ 0 ];
        int m2 = std::max( nums[ 0 ], nums[ 1 ] );
        for ( int i = 2; i < nums.size(); ++i ) {
            int m = std::max( m2, m1 + nums[ i ] );
            m1 = m2;
            m2 = m;
        }
        return m2;
    }
};

