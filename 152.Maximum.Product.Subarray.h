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
