//Palindrome Partitioning II
//
//Given a string s, partition s such that every substring of the
//partition is a palindrome.
//
//Return the minimum cuts needed for a palindrome partitioning of s.
//
//For example, given s = "aab",
//
//Return 1 since the palindrome partitioning ["aa","b"] could be produced
//using 1 cut.

//Tags: Dynamic Programming

#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
	int minCut( std::string s ) {
		
		//Define DP function P[ i ][ j ] == true if s[ i ... j ] is a Palindrome
		//P[ i ][ j ] == true if s[ i ] == s[ j ] && P[ i + 1 ][ j - 1 ] ( i + 1 <= j - 1 )
		//i.e. 2 <= j - i
		//
		//Define DP function D[ i ] = # of min cuts for s[ i ... n ]
		//where n is the s.length() - 1
		//D[ i ] = min( 1 + D[ j ] ) i < j <= n
		//Starting from i and search towards right, find a Palindrome
		
		//initialize D with the worst solution
		std::vector< int > D( s.length() );
		for ( int i = 0; i < s.length(); ++i )
			D[ i ] = s.length() - 1 - i;
		
		//initialize P to be false
		std::vector< std::vector< bool > >
			P( s.length(), std::vector< bool >( s.length(), false ) );
		
		//when i = s.length() - 1, j = s.length() - 1 and D[ i ] = 0
		//hence i can start from s.length() - 2
		for ( int i = s.length() - 2; i >= 0; --i )
		{
			for ( int j = i; j < s.length(); ++j )
			{
				//check s[ i ... j ] is a Palindrome
				if ( s[ i ] == s[ j ] && ( j - i < 2 || P[ i + 1 ][ j - 1 ] ) )
				{
					P[ i ][ j ] = true;
					D[ i ] = std::min( D[ i ], j == s.length() - 1 ? 0 : 1 + D[ j + 1 ] );
				}
			}
		}

		return D[ 0 ];
    }
};
