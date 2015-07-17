/**
 * Algorithms 41 First Missing Positive                                    Hard
 * 
 * Given an unsorted integer array, find the first missing positive integer.
 * 
 * For example,
 * Given [1,2,0] return 3,
 * and [3,4,-1,1] return 2.
 * 
 * Your algorithm should run in O(n) time and uses constant space.
 *
 * Tags: Array
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int firstMissingPositive( std::vector< int > & nums ) {
        return first_missing_positive_sort( nums );
    }
private:
    /**
     * O( n ) runtime, O( 1 ) space - bucket sort idea
     * Actually we used the input and modified it.
     * 
     * Let n = nums.size().
     * Then we can immediately know that the first missing positive
     * must be some number from 1 to n + 1. Because if the n slots in
     * nums are filled with number from 1 to n. Then the first missing
     * positive is n + 1. If any number from 1 to n is replace by other
     * numbers then the smallest missing number is the first missing
     * positive.
     * 
     * We try to move number i to nums[ i - 1 ] if 1 <= i <= n.
     * After sweeping through the whole nums, all the numbers satisfying
     * 1 <= i <= n are in their slots. The first mismatch implies the
     * first missing positive.
     */
    int first_missing_positive_bucket( std::vector< int > & nums ) {
        const int n = nums.size();
        for ( int i = 0; i < n; ++i ) {
            /**
             * Imaging nums[ 5 ] = 9 indicates that 9 should be put in
             * nums[ 8 ]. But what is nums[ 8 ] = 9 already!
             * Without nums[ i ] != nums[ nums[ i ] - 1 ] it will become
             * an infinite loop. This also demonstrates the duplicated
             * numbers.
             */
            if ( nums[ i ] != i + 1
              && nums[ i ] >= 1 && nums[ i ] <= n
              && nums[ i ] != nums[ nums[ i ] - 1 ] ) {
                std::swap( nums[ i ], nums[ nums[ i ] - 1 ] );
                --i;//to cancel out ++i in the for statement
            }
        }
        //scan for the first index i where nums[ i ] != i + 1
        for ( int i = 0; i < n; ++i ) {
            if ( nums[ i ] != i + 1 )
                return i + 1;
        }
        //if every number in nums satisfying nums[ i ] == i + 1
        //then n + 1 is the first missing positive
        return n + 1;
    }
    
    /**
     * O( n log n ) runtime, O( 1 ) space - sorting
     * We modified the input by sorting.
     */
    int first_missing_positive_sort( std::vector< int > & nums ) {
        const int n = nums.size();
        std::sort( nums.begin(), nums.end() );
        int target = 1;
        for ( int i = 0; i < n; ++i ) {
            if ( nums[ i ] < target ) continue;
            else if ( nums[ i ] != target ) return target;
            else ++target;
        }
        return target;
    }
};
