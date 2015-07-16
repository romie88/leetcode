/**
 * Algorithms 238 Production of Array Except Self                        Medium
 * 
 * Given an array of n integers where n > 1, nums, return an array output such
 * that output[i] is equal to the product of all the elements of nums except
 * nums[i].
 * 
 * Solve it without division and in O(n).
 * 
 * For example, given [1,2,3,4], return [24,12,8,6].
 * 
 * Follow up:
 * Could you solve it with constant space complexity? (Note: The output array
 * does not count as extra space for the purpose of space complexity analysis.)
 * 
 * Tags: Array
 * Similar Problems: (H) Trapping Rain Water, (M) Maximum Product Subarray
 */

#include <vector>
#include <stdexcept>

class Solution {
public:
    std::vector< int > productExceptSelf( const vector< int > & nums ) {
        const int n = nums.size();
        if ( n <= 1 ) throw std::invalid_argument( "nums.size() <= 1" );
        
        std::vector< int > result( n, 1 );
        for ( int i = 1; i < n; ++i )
            result[ i ] = result[ i - 1 ] * nums[ i - 1 ];
        
        int tmp = 1;
        for ( int i = n - 1; i >= 0; --i ) {
            result[ i ] *= tmp;
            tmp *= nums[ i ];
        }
        
        return result;
    }
};
