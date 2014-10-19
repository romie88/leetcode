//Maximum Product Subarray
//
//Find the contiguous subarray within an array (containing at least one number)
//which has the largest product.
//
//For example, given the array [2,3,-2,4],
//the contiguous subarray [2,3] has the largest product = 6.

#include <algorithm>

class Solution {
public:
    int maxProduct( int A[], int n ) {
		
        int max_positive_p_ending_here = A[ 0 ] > 0 ? A[ 0 ] : 0;
        int min_negative_p_ending_here = A[ 0 ] < 0 ? A[ 0 ] : 0;
        int max_p                      = A[ 0 ];
		
        for ( int i = 1; i < n; ++i )
        {
			if ( A[ i ] > 0 )
            {
                max_positive_p_ending_here
					= std::max( A[ i ], max_positive_p_ending_here * A[ i ] );
                min_negative_p_ending_here
					= min_negative_p_ending_here * A[ i ];
                max_p = std::max( max_p, max_positive_p_ending_here );
            }
            else if ( A[ i ] == 0 )
            {
				max_p = std::max( max_p, 0 );

				//skip following duplicated zeroes
				while ( i < n && A[ i ] == 0 )
					++i;

				if ( i < n )
				{
                	max_positive_p_ending_here = A[ i ] > 0 ? A[ i ] : 0;
                	min_negative_p_ending_here = A[ i ] < 0 ? A[ i ] : 0;
					max_p = std::max( max_p, A[ i ] );
				}
            }
            else
            {
				int temp = max_positive_p_ending_here;
                max_positive_p_ending_here
					= min_negative_p_ending_here * A[ i ];
                min_negative_p_ending_here
					= std::min( A[ i ], temp * A[ i ] );
                max_p = std::max( max_p, max_positive_p_ending_here );
			}
        }
        
        return max_p;
    }
};
