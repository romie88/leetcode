//Single Number II
//
//Given an array of integers, every element appears three times except for one.
//Find that single one.
//
//Note:
//
//Your algorithm should have a linear runtime complexity.
//Could you implement it without using extra memory?

//Tags: Bit Manipulation

class Solution {
public:
    int singleNumber( int A[], int n ) {
		
		//assume int is 32 bits
		//add up the kth bit of A[ i ]
		//since every element appears three times
		//except one
		//the summation mod by 3 is the result's kth bit
		int count[ 32 ] = { 0 };//actually a single variable is enough
		int result = 0;
		for ( int k = 0; k < 32; ++k )
		{
			for ( int i = 0; i < n; ++i )
			{
				count[ k ] += ( ( A[ i ] & ( 1 << k ) ) != 0 );
			}

			result |= ( ( count[ k ] % 3 ) << k );
		}
		
		return result;
    }
};
