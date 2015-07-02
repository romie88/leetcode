/**
 * Algorithms 15 3Sum                                                    Medium
 * 
 * Given an array S of n integers, are there elements a, b, c in S such that
 * a + b + c = 0? Find all unique triplets in the array which gives the sum of
 * zero.
 * 
 * Note:
 * * Elements in a triplet (a,b,c) must be in non-descending order.
 *   (ie, a <= b <= c)
 * * The solution set must not contain duplicate triplets.
 * 
 * For example, given array S = {-1 0 1 2 -1 -4},
 * 
 * A solution set is:
 * (-1, 0, 1)
 * (-1, -1, 2)
 * 
 * Tags: Array, Two Pointers
 */

#include <vector>

class Solution {
public:
    std::vector< std::vector< int > > threeSum( std::vector< int > & nums ) {
        return three_sum( nums );
    }
private:
    /**
     * O( n^2 ) runtime, O( n ) space
     * To handle the duplicate, hash table is not wieldy, thus we sort.
     * Then scan with two pointers.
     */
    std::vector< std::vector< int > > three_sum( std::vector< int > & nums ) {
        std::vector< std::vector< int > > results;
        std::sort( nums.begin(), nums.end() );
        
        int n = nums.size();
        for ( int i = 0; i < n - 2; ++i ) {
            //skip duplicates
            if ( i > 0 && nums[ i - 1 ] == nums[ i ] )
                continue;
            
            int minus_c = -nums[ i ];
            int start = i + 1;
            int end   = n - 1;
            while ( start < end ) {
                int sum = nums[ start ] + nums[ end ];
                if ( sum < minus_c )
                    ++start;
                else if ( sum > minus_c )
                    --end;
                else {
                    results.push_back( std::vector< int >{
                            nums[ i ], nums[ start ], nums[ end ] } );
                    ++start;
                    --end;
                    //avoid duplicates
                    while ( start < end && nums[ start ] == nums[ start - 1 ] )
                        ++start;
                    while ( start < end && nums[ end ] == nums[ end + 1 ] )
                        --end;
                }
            }
        }
        
        return results;
    }
};
