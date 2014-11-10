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

class Solution {
public:
	int minCut( std::string s ) {
        
		//is_p_flag[ i ][ j ] == true means that s[ i ... j ] is a palindrome
		std::vector< std::vector< bool > >
			is_p_flag( s.length(), std::vector< bool >( s.length(), false ) );
		for ( int i = 0; i < s.length(); ++i )
			for ( int j = i; j < s.length(); ++j )
				is_p_flag[ i ][ j ] = is_palindrome( s, i, j );
		
		//min_cut[ i ][ j ] is the min cut of s[ i ... j ] to have palindrome partition
		std::vector< std::vector< int > >
			min_cut( s.length(), std::vector< int >( s.length(), -1 ) );
		
		return minCut_impl( s, 0, s.length() - 1, is_p_flag, min_cut );
    }
private:
	bool is_palindrome( const std::string & s, int i, int j )
	{
		for ( ; i <= j; ++i, --j )
			if ( s[ i ] != s[ j ] )
				return false;
		return true;
	}

	int minCut_impl( const std::string & s, int i, int j,
	                 std::vector< std::vector< bool > > & is_p_flag,
		             std::vector< std::vector< int > > & min_cut )
	{
		if ( is_p_flag[ i ][ j ] )
		{
			min_cut[ i ][ j ] = 0;
			return 0;
		}
		
		if ( i == j )
		{
			min_cut[ i ][ j ] = 0;
			return 0;
		}
		
		if ( min_cut[ i ][ j ] >= 0 )
			return min_cut[ i ][ j ];
		
		int this_min_cut = j - i;
		for ( int k = i; k < j; ++k )
		{
			if ( min_cut[ i ][ k ] < 0 )
			{
				min_cut[ i ][ k ] = minCut_impl( s, i, k, is_p_flag, min_cut );
			}
			
			if ( min_cut[ k + 1 ][ j ] < 0 )
			{
				min_cut[ k + 1 ][ j ] = minCut_impl( s, k + 1, j, is_p_flag, min_cut );
			}
			
			int cut = 1 + min_cut[ i ][ k ] + min_cut[ k + 1 ][ j ];
			if ( cut < this_min_cut )
				this_min_cut = cut;
		}
		min_cut[ i ][ j ] = this_min_cut;
		
		return min_cut[ i ][ j ];
	}
};
