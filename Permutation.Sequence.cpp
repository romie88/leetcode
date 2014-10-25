//Permutation Sequence
//
//The set [1,2,3,…,n] contains a total of n! unique permutations.
//
//By listing and labeling all of the permutations in order,
//We get the following sequence (ie, for n = 3):
//
//"123"
//"132"
//"213"
//"231"
//"312"
//"321"
//Given n and k, return the kth permutation sequence.
//
//Note: Given n will be between 1 and 9 inclusive.

#include <string>
#include <vector>

class Solution {
public:
	std::string getPermutation( int n, int k ) {

		std::string result;
		if ( n <= 0 )
			return result;
		
		//vector
		std::vector< int > e( n );
		int n_factorial = 1;
		for ( int i = 1; i <= n; ++i ) 
		{
			n_factorial *= i;
			e[ i - 1 ] = i;
		}
		
		if ( k < 1 || k > n_factorial )
			return result;
		
		--k;
		for ( int i = n; i > 1; --i )
		{
			n_factorial /= i;
			int index = k / n_factorial;
			k %= n_factorial;
			std::vector< int >::iterator
				it = e.begin();
			it += index;
			result.append( 1, *it + '0' );
			e.erase( it );
		}
		result.append( 1, e[ 0 ] + '0' );
		
		return result;
    }
};
