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

#include <vector>

class Solution {
public:
    int singleNumber( int A[], int n ) {
		
		return generalSolution( A, n, 3, 1 );
    }
private:
/**
 * Given an array of integers, every element appears k times except for one.
 * Find that single one who appears l times.
 * Here assume l < k
 *
 * Using "sum per bit"
 * Case 1: l % k != 0 then ( sum_per_bit % k ) / ( l % k )
 * Case 2: l % k == 0 then ( sum_per_bit - sum_per_bit % l ) / l ???
 */
	int generalSolution( int A[], int n, int k, int l ) {

		int t;
		std::vector< int > x( k, 0 );
		//for 0 <= i < k
		//x[ i ]: each bit of x[ i ] is the boolean value of
		//the bit appears i times
		x[ 0 ] = ~0;
		for ( int i = 0; i < n; ++i )
		{
			t = x[ k - 1 ];
			for ( int j = k - 1; j > 0; --j )
			{
				x[ j ] = x[ j - 1 ] & A[ i ] | x[ j ] & ~A[ i ];
			}
			x[ 0 ] = t & A[ i ] | x[ 0 ] & ~A[ i ];
		}

		return x[ l ];
	}
};
