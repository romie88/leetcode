//Palindrome Partitioning
//
//Given a string s, partition s such that every substring of the
//partition is a palindrome.
//
//Return all possible palindrome partitioning of s.
//
//For example, given s = "aab",
//Return
//
//  [
//    ["aa","b"],
//    ["a","a","b"]
//  ]

//Tags: Dynamic Programming

#include <string>
#include <vector>

class Solution {
public:
	std::vector< std::vector< std::string > > partition( std::string s ) {
        
		std::vector< std::vector< bool > >
			is_p_flag( s.length(), std::vector< bool >( s.length(), false ) );
		for ( int i = 0; i < s.length(); ++i )
			for ( int j = i; j < s.length(); ++j )
				is_p_flag[ i ][ j ] = is_palindrome( s, i, j );
		
		std::vector< std::string > p;
		std::vector< std::vector< std::string > > pp;
		partition_impl( s, 0, is_p_flag, p, pp );

		return pp;
    }
private:
	bool is_palindrome( const std::string & s, int i, int j )
	{
		for ( ; i <= j; ++i, --j )
			if ( s[ i ] != s[ j ] )
				return false;
		return true;
	}

	void partition_impl( const std::string & s, int i,
			             const std::vector< std::vector< bool > > & is_p_flag,
						 std::vector< std::string > & p,
						 std::vector< std::vector< std::string > > & pp )
	{
		if ( i == s.length() )
		{
			p.push_back( "" );
			return;
		}

		for ( int k = i; k < s.length(); ++k )
		{
			if ( is_p_flag[ i ][ k ] )	
			{
				p.push_back( s.substr( i, k - i + 1 ) );
				partition_impl( s, k + 1, is_p_flag, p, pp );
				if ( p.back() == "" )
				{
					p.pop_back();
					pp.push_back( p );
				}
				p.pop_back();
			}
		}
	}
};
