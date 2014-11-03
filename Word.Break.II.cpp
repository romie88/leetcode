//Word Break II
//
//Given a string s and a dictionary of words dict, add spaces in s to
//construct a sentence where each word is a valid dictionary word.
//
//Return all such possible sentences.
//
//For example, given
//s = "catsanddog",
//dict = ["cat", "cats", "and", "sand", "dog"].
//
//A solution is ["cats and dog", "cat sand dog"].

//Tags: Dynamic Programming, Backtracking

#include <vector>
#include <string>
#include <unordered_set>
#include <set>

class Solution {
public:
	std::vector< std::string >
	wordBreak( std::string s, std::unordered_set< std::string > & dict ) {
    	
		std::vector< std::string > result;
		
		//p[ i ] is a set of ints
		//each int k means that s[ 0, k ] can be segmented by dict
		//and s[ k+1, i ] can be find in dict
		std::vector< std::set< int > > p( s.length(), std::set< int >() );
		
		//populate p
		for ( std::string::size_type i = 0; i < s.length(); ++i )
		{
			if ( dict.find( s.substr( 0, i + 1 ) ) != dict.end() )
			{
				p[ i ].insert( i );
			}

			for ( std::string::size_type k = 0; k < i; ++k )
			{
				if ( ! p[ k ].empty()
				  && dict.find( s.substr( k + 1, i - k ) ) != dict.end() )
					p[ i ].insert( k );
			}
		}
		
		backTrack( p, s, s.length() - 1, result );

		return result;
	}

private:
	void backTrack( const std::vector< std::set< int > > & p,
			        const std::string & s,
					const int i,
			        std::vector< std::string > & result )
	{
		const std::set< int > & si = p[ i ];
		for ( std::set< int >::const_iterator cit = si.begin(); cit != si.end(); ++cit )
		{
			if ( *cit == i )
			{
				result.push_back( s.substr( 0, i + 1 ) );
			}
			else
			{
				std::string second_part( s.substr( *cit + 1, i - *cit ) );
				std::vector< std::string > first_part_vec;
				backTrack( p, s, *cit, first_part_vec );
				for ( std::vector< std::string >::const_iterator cit2 = first_part_vec.begin();
					  cit2 != first_part_vec.end(); ++cit2 )
				{
					result.push_back( *cit2 + " " + second_part );
				}
			}
		}
	}
};
