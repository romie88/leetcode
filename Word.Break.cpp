//Word Break
//
//Given a string s and a dictionary of words dict, determine if s can be
//segmented into a space-separated sequence of one or more dictionary words.
//
//For example, given
//s = "leetcode",
//dict = ["leet", "code"].
//
//Return true because "leetcode" can be segmented as "leet code".

//Tags: Dynamic Programming

#include <string>
#include <unordered_set>
#include <vector>

class Solution {
public:
    bool wordBreak( std::string s, std::unordered_set< std::string > & dict ) {
		
		if ( s.empty() )
			return false;
		
		//p[ i ] is true if substring s[ 0, i ] can be segmented by dict
		std::vector< bool > p( s.size(), false );
		
		for ( std::string::size_type i = 0; i < s.length(); ++i )
		{
			if ( dict.find( s.substr( 0, i + 1 ) ) != dict.end() )
			{
				p[ i ] = true;
			}
			else
			{
				for ( std::string::size_type k = 0; k < i; ++k )
				{
					p[ i ] = p[ k ]
						     && ( dict.find( s.substr( k + 1, i - k ) ) != dict.end() );
					if ( p[ i ] )
						break;
				}
			}
		}

		return p[ s.length() - 1 ];
    }
};
