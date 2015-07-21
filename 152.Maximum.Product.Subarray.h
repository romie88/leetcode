/**
 * Algorithms 152 Maximum Product Subarray                               Medium
 * 
 * Find the contiguous subarray within an array (containing at least one number)
 * which has the largest product.
 * 
 * For example, given the array [2,3,-2,4],
 * the contiguous subarray [2,3] has the largest product = 6.
 *
 * Tags: Array, Dynamic Programming
 * Similar Problems: (M) Maximum Subarray, (M) Product of Array Except Self
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProduct( const vector< int > & nums ) {
		
        if ( nums.size() == 0 ) throw std::invalid_argument( "empty input" );
        
        int max_prod_ending_at_i = nums[ 0 ];
        int min_prod_ending_at_i = nums[ 0 ];
        int max_prod = nums[ 0 ];
        for ( int i = 1; i < nums.size(); ++i ) {
            int mx = max_prod_ending_at_i;
            int mn = min_prod_ending_at_i;
            max_prod_ending_at_i = std::max( mx * nums[ i ],
                std::max( nums[ i ], mn * nums[ i ] ) );
            min_prod_ending_at_i = std::min( mx * nums[ i ],
                std::min( nums[ i ], mn * nums[ i ] ) );
            max_prod = std::max( max_prod, max_prod_ending_at_i );
        }
        
        return max_prod;
    }
};

/**
 * Solution
 * 
 * Besides keeping track of the largest product, we also need to keep track of
 * the smallest product. Why? The smallest product, which is the largest in the
 * negative sense could become the maximum when being multiplied by a negative
 * number.
 * 
 * Let us denote that:
 * 
 * f(k) = Largest product subarray, from index 0 up to k.
 * 
 * Similarly,
 * 
 * g(k) = Smallest product subarray, from index 0 up to k.
 * 
 * Then,
 * 
 * f(k) = max( f(k-1) * A[k], A[k], g(k-1) * A[k] )
 * g(k) = min( g(k-1) * A[k], A[k], f(k-1) * A[k] )
 * 
 * There we have a dynamic programming formula. Using two arrays of size n, we
 * could deduce the final answer as f(n-1). Since we only need to access its
 * previous elements at each step, two variables are sufficient.
 */
