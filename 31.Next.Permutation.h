/**
 * Algorithms 31 Next Permutation                                       Medium
 *
 * Implement next permutation, which rearranges numbers into the
 * lexicographically next greater permutation of numbers.
 *
 * If such arrangement is not possible, it must rearrange it as the lowest
 * possible order (ie, sorted in ascending order).
 * 
 * The replacement must be in-place, do not allocate extra memory.
 * 
 * Here are some examples. Inputs are in the left-hand column and its
 * corresponding outputs are in the right-hand column.
 * 1,2,3 -> 1,3,2
 * 3,2,1 -> 1,2,3
 * 1,1,5 -> 1,5,1
 *
 * Tags: Array
 */

#include <vector>

class Solution {
public:
    /**
     * Let's observe the hidden rules of the permutations:
     *
     * 1 2 3 4
     * 1 2 4 3
     * 1 3 2 4
     * 1 3 4 2
     * 1 4 2 3
     * 1 4 3 2
     * 2 1 3 4
     * 
     * For example, how 1 4 3 2 is followed by 2 1 3 4.
     * And 4 3 2 1 is followed by 1 2 3 4.
     * Notice that 1 4 3 2 has the first 1 < 4 when we
     * scan from the right to the left. And 4 3 2 is already
     * completely reversed like 4 3 2 1. The next permutation
     * will have to involve 1. Hence we need to look for the
     * next number to replace 1. In this case it is 2. When
     * we find the position of 2 we can swap 1 and 2. And we
     * have 2 4 3 1. Here we know 4 3 2 is in descending order.
     * We can binary search the position of 2. And after the
     * swap we have 4 3 1. We just need to reverse 4 3 1. And
     * we got 2 1 3 4.
     *
     * If we cannot find any situation like 1 < 4 when we scan
     * from the right to the left we know this permutation is
     * in completely descending order. All we need to do is
     * reverse them.
     */
    void nextPermutation( std::vector< int > & nums ) {
        int i = nums.size() - 1;
        for ( ; i >= 1; --i )
            if ( nums[ i ] > nums[ i - 1 ] )
                break;
        if ( i == 0 ) {
            reverse( nums, i, nums.size() - 1 );
        } else {
            int j = i - 1;
            int k = find_position( nums, i, nums.size() - 1, nums[ j ] );
            std::swap( nums[ k ], nums[ j ] );
            reverse( nums, i, nums.size() - 1 );
        }
    }
private:
    void reverse( std::vector< int > & nums, int s, int e ) {
        while ( s < e )
            std::swap( nums[ s++ ], nums[ e-- ] );
    }
    int find_position( const std::vector< int > & nums, int s, int e,
                       const int target ) {
        while ( s <= e ) {
            int m = ( s + e ) / 2;
            if ( nums[ m ] > target )
                s = m + 1;
            else
                e = m - 1;
        }
        return s - 1;
    }
};
