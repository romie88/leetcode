/**
 * Algorithms 16 3Sum Closest                                            Medium
 * 
 * Given an array S of n integers, find three integers in S such that the sum
 * is closest to a given number, target. Return the sum of the three integers.
 * You may assume that each input would have exactly one solution.
 * 
 * For example, given array S = {-1 2 1 -4}, and target = 1.
 * 
 * The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 * 
 * Tags: Array, Two Pointers
 */

#include <vector>
#include <limits>
#include <algorithm>

class Solution {
public:
    int threeSumClosest( std::vector< int > & nums, int target ) {
        return three_sum_closest( nums, target );
    }
private:
    /**
     * O( n^2 ) runtime
     */
    int three_sum_closest( std::vector< int > & nums, int target ) {
        std::sort( nums.begin(), nums.end() );
        int dist = std::numeric_limits< int >::max();
        int closest = 0;
        const int n = nums.size();
        for ( int i = 0; i < n - 2; ++i ) {
            //skip duplicates
            if ( i > 0 && nums[ i - 1 ] == nums[ i ] )
                continue;
            int rest = target - nums[ i ];
            int start = i + 1;
            int end   = n - 1;
            while ( start < end ) {
                int two_sum = nums[ start ] + nums[ end ];
                if ( two_sum < rest ) {
                    ++start;
                    if ( dist > rest - two_sum ) {
                        dist = rest - two_sum;
                        closest = two_sum + nums[ i ];
                    }
                    //skip duplicates
                    while ( start < end && nums[ start - 1 ] == nums[ start ] )
                        ++start;
                } else if ( two_sum > rest ) {
                    --end;
                    if ( dist > two_sum - rest ) {
                        dist = two_sum - rest;
                        closest = two_sum + nums[ i ];
                    }
                    //skip duplicates
                    while ( start < end && nums[ end ] == nums[ end + 1 ] )
                        --end;
                } else {
                    return target;
                }
            }
        }
        return closest;
    }
};
