/**
 * Algorithms 53 Maximum Subarray                                        Medium
 * 
 * Find the contiguous subarray within an array (containing at least one number)
 * which has the largest sum.
 * 
 * For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
 * the contiguous subarray [4,−1,2,1] has the largest sum = 6.
 * 
 * click to show more practice.
 * 
 * More practice:
 * If you have figured out the O(n) solution, try coding another solution using
 * the divide and conquer approach, which is more subtle.
 *
 * Tags: Divide and Conquer, Array, Dynamic Programming
 * Similar Problems: (M) Maximum Product Subarray
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int maxSubArray( const std::vector< int > & nums ) {
        return max_subarray_DP( nums );
    }
private:
    /**
     * O(n) runtime, O(1) space
     * DP maintain the local and global
     *
     * This problem is a classic DP problem.
     * The paradigm is very widely recognized.
     * In each step, we maintain one global optimal value and one
     * local optimal value which involves the current element.
     * Now the DP recursive equation:
     * local[ i + 1 ] = max( A[ i ], local[ i ] + A[ i ] )
     * global[ i + 1 ] = max( global[ i ], local[ i  + 1 ] )
     */
    int max_subarray_DP( const std::vector< int > & nums ) {
        //assume nums is not empty otherwise the problem is not well defined
        int global = nums[ 0 ];//the max subarray sum we are looking for
        int local  = nums[ 0 ];//the max subarray sum ending at index i
        for ( int i = 1; i < nums.size(); ++i ) {
            if ( local > 0 )
                local = local + nums[ i ];
            else
                local = nums[ i ];
            global = std::max( global, local );
        }
        return global;
    }
    /**
     * O(n lg n) runtime, O(lg n) stack space
     * Divide and Conquer Approach
     */
    int max_subarray_DnC( const std::vector< int > & nums ) {
        return max_subarray_DnC_impl( nums, 0, nums.size() - 1 );
    }
    
    int max_subarray_DnC_impl( const std::vector< int > & nums,
                               int start, int end ) {
        if ( start >  end ) return 0;
        if ( start == end ) return nums[ start ];
        
        int mid = ( start + end ) / 2;
        
        int max_left  = max_subarray_DnC_impl( nums, start,   mid - 1 );
        int max_right = max_subarray_DnC_impl( nums, mid + 1, end );
        int max_cross = nums[ mid ];
        int max_cross_left = 0;
        int tmp = 0;
        for ( int j = mid - 1; j >= start; --j ) {
            tmp += nums[ j ];
            max_cross_left = std::max( max_cross_left, tmp );
        }
        int max_cross_right = 0;
        tmp = 0;
        for ( int j = mid + 1; j <= end; ++j ) {
            tmp += nums[ j ];
            max_cross_right = std::max( max_cross_right, tmp );
        }
        max_cross += ( max_cross_left + max_cross_right );
        
        int result = max_cross;
        if ( start <= mid - 1 )
            result = std::max( result, max_left );
        if ( mid + 1 <= end )
            result = std::max( result, max_right );
        
        return result;
    }
};
